/*
 * main_sdk0428.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: craig
 */

#include <stdio.h>
#include <string.h>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <geometry_msgs/TransformStamped.h> //IMU
#include <geometry_msgs/Vector3Stamped.h> //velocity
#include <sensor_msgs/LaserScan.h> //obstacle distance && ultrasonic

ros::Subscriber left_image_sub;
ros::Subscriber right_image_sub;
ros::Subscriber depth_image_sub;
ros::Subscriber imu_sub;
ros::Subscriber velocity_sub;
ros::Subscriber obstacle_distance_sub;
ros::Subscriber ultrasonic_sub;
ros::Subscriber position_sub;

ros::Publisher distance_landing;
ros::Subscriber start_landing;

// Matching

#include <opencv2/features2d.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

//#include "sys/stats.h" // Stats structure definition
//#include "sys/utils.h" // Drawing and printing functions

const double ransac_thresh = 2.5f; // RANSAC inlier threshold
const double nn_match_ratio = 0.8f; // Nearest-neighbour matching ratio
const int bb_min_inliers = 100; // Minimal number of inliers to draw bounding box
const int stats_update_period = 10; // On-screen statistics are updated every 10 frames


using namespace cv_bridge;
#define WIDTH 320
#define HEIGHT 240

using namespace std;
using namespace cv;

cv::Mat imgCameraLeft;
cv::Mat imgCameraRight;

std_msgs::Float32MultiArray array;

double *landingXY = (double *) malloc(3*sizeof(double)); // saved home point

float start = 0;

void arrayCallback(const std_msgs::Float32MultiArray::ConstPtr& activation)
{

	int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = activation->data.begin(); it != activation->data.end(); ++it)
	{
		start = *it;
		i++;
		ROS_INFO("Guidance OFF/ON %f ....", start);
	}

	return;
}

/* left greyscale image */
void left_image_callback(const sensor_msgs::ImageConstPtr& left_img)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(left_img, sensor_msgs::image_encodings::MONO8);
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    imgCameraLeft = cv_ptr->image;
    cv::imshow("left_image", cv_ptr->image);
    cv::waitKey(1);
}

/* right greyscale image */
void right_image_callback(const sensor_msgs::ImageConstPtr& right_img)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(right_img, sensor_msgs::image_encodings::MONO8);
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    imgCameraRight = cv_ptr->image;
    cv::imshow("right_image", cv_ptr->image);
    cv::waitKey(1);
}

/* depth greyscale image */
void depth_image_callback(const sensor_msgs::ImageConstPtr& depth_img)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(depth_img, sensor_msgs::image_encodings::MONO16);
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat depth8(HEIGHT, WIDTH, CV_8UC1);
    cv_ptr->image.convertTo(depth8, CV_8UC1);
    //cv::imshow("depth_image", depth8);
    cv::waitKey(1);
}

/* imu */
void imu_callback(const geometry_msgs::TransformStamped& g_imu)
{
    //printf( "frame_id: %s stamp: %d\n", g_imu.header.frame_id.c_str(), g_imu.header.stamp.sec );
    //printf( "imu: [%f %f %f %f %f %f %f]\n", g_imu.transform.translation.x, g_imu.transform.translation.y, g_imu.transform.translation.z, g_imu.transform.rotation.x, g_imu.transform.rotation.y, g_imu.transform.rotation.z, g_imu.transform.rotation.w );
}

/* velocity */
void velocity_callback(const geometry_msgs::Vector3Stamped& g_vo)
{
    //printf( "frame_id: %s stamp: %d\n", g_vo.header.frame_id.c_str(), g_vo.header.stamp.sec );
    //printf( "velocity: [%f %f %f]\n", g_vo.vector.x, g_vo.vector.y, g_vo.vector.z );
}

/* obstacle distance */
void obstacle_distance_callback(const sensor_msgs::LaserScan& g_oa)
{
    //printf( "frame_id: %s stamp: %d\n", g_oa.header.frame_id.c_str(), g_oa.header.stamp.sec );
    //printf( "obstacle distance: [%f %f %f %f %f]\n", g_oa.ranges[0], g_oa.ranges[1], g_oa.ranges[2], g_oa.ranges[3], g_oa.ranges[4] );
}

/* ultrasonic */
void ultrasonic_callback(const sensor_msgs::LaserScan& g_ul)
{
    //printf( "frame_id: %s stamp: %d\n", g_ul.header.frame_id.c_str(), g_ul.header.stamp.sec );
    //for (int i = 0; i < 5; i++)
        //printf( "ultrasonic distance: [%f]  reliability: [%d]\n", g_ul.ranges[i], (int)g_ul.intensities[i] );
}

/* motion */
void position_callback(const geometry_msgs::Vector3Stamped& g_pos)
{
    //printf("frame_id: %s stamp: %d\n", g_pos.header.frame_id.c_str(), g_pos.header.stamp.sec);
    //for (int i = 0; i < 5; i++)
        //printf("global position: [%f %f %f]\n", g_pos.vector.x, g_pos.vector.y, g_pos.vector.z);
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "GuidanceNodeTest");
    ros::NodeHandle my_node;

    ros::Duration(15.0).sleep();

    left_image_sub        = my_node.subscribe("/guidance/left_image",  10, left_image_callback);
    right_image_sub       = my_node.subscribe("/guidance/right_image", 10, right_image_callback);
    depth_image_sub       = my_node.subscribe("/guidance/depth_image", 10, depth_image_callback);
    imu_sub               = my_node.subscribe("/guidance/imu", 1, imu_callback);
    velocity_sub          = my_node.subscribe("/guidance/velocity", 1, velocity_callback);
    obstacle_distance_sub = my_node.subscribe("/guidance/obstacle_distance", 1, obstacle_distance_callback);
    ultrasonic_sub 	  = my_node.subscribe("/guidance/ultrasonic", 1, ultrasonic_callback);
    position_sub 	  = my_node.subscribe("/guidance/position", 1, position_callback);

    Mat imgPattern = imread("/home/ivica/catkin_ws/src/Guidance-SDK-ROS-master/src/pattern0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //cv::imshow("pattern image", imgPattern);

    start_landing 	  = my_node.subscribe("/dji_sdk_demo/activation", 1, arrayCallback);	
    distance_landing 	  = my_node.advertise<std_msgs::Float32MultiArray>("array", 1);


    ros::spinOnce();

    int minMatches = 3;

    // Initiate ORB detector
	Ptr<FeatureDetector> detector = ORB::create();
	Ptr<DescriptorExtractor> extractor = ORB::create();

    // find the keypoints and descriptors with ORB

	vector<KeyPoint> keypointsPattern;
	Mat descriptorsPattern;
        detector->detect(imgPattern, keypointsPattern);
        
    // Compute keypoints and descriptor from the source image in advance

	extractor->compute(imgPattern, keypointsPattern, descriptorsPattern);
        descriptorsPattern.convertTo(descriptorsPattern, CV_32F);

	//if ( descriptorsPattern.empty() )
   		//cvError(0,"MatchFinder","0st descriptor empty",__FILE__,__LINE__); 

    //-- Draw keypoints
  
	Mat img_keypointsPattern;

  	drawKeypoints( imgPattern, keypointsPattern, img_keypointsPattern, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

    //-- Show detected (drawn) keypoints
  
	//imshow("Keypoints 0", img_keypointsPattern );

    while (ros::ok()) {

    array.data.clear();
	
    array.data.push_back(0);
    array.data.push_back(0);
    array.data.push_back(0);

    if(start == 1) {

    // Compute keypoints and descriptor from the left camera input

        vector<KeyPoint> keypointsCameraLeft;
	Mat descriptorsCameraLeft;

    // Compute keypoints and descriptor from the right camera input

	vector<KeyPoint> keypointsCameraRight;
	Mat descriptorsCameraRight;

    // Detect keypoints Left

        detector->detect(imgCameraLeft, keypointsCameraLeft);
	extractor->compute(imgCameraLeft, keypointsCameraLeft, descriptorsCameraLeft);	

        descriptorsCameraLeft.convertTo(descriptorsCameraLeft, CV_32F);

        //if ( descriptorsCameraLeft.empty() )
   		//cvError(0,"MatchFinder","1st descriptor empty",__FILE__,__LINE__);    

    // Matching descriptor vectors using FLANN matcher

	FlannBasedMatcher matcher;

	std::vector< DMatch > matchesLeft;
	matcher.match( descriptorsPattern, descriptorsCameraLeft, matchesLeft );

	//if(matchesLeft.size() < 1) cvError(0,"MatchFinder","No left matches",__FILE__,__LINE__);

    // Detect keypoints Right

	detector->detect(imgCameraRight, keypointsCameraRight);
	extractor->compute(imgCameraRight, keypointsCameraRight, descriptorsCameraRight);	
	
        descriptorsCameraRight.convertTo(descriptorsCameraRight, CV_32F);

 	//if ( descriptorsCameraRight.empty() )
   		//cvError(0,"MatchFinder","2nd descriptor empty",__FILE__,__LINE__);	

    //-- Draw keypoints
  	Mat img_keypointsLeft; Mat img_keypointsRight;

  	drawKeypoints( imgCameraLeft, keypointsCameraLeft, img_keypointsLeft, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  	drawKeypoints( imgCameraRight, keypointsCameraRight, img_keypointsRight, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

    //-- Show detected (drawn) keypoints
  
	//imshow("Keypoints 1", img_keypointsLeft );
	//imshow("Keypoints 2", img_keypointsRight );	

    
    // Matching descriptor vectors using FLANN matcher

	std::vector< DMatch > matchesRight;
	matcher.match( descriptorsPattern, descriptorsCameraRight, matchesRight );

	if(matchesRight.size() < 1) cvError(0,"MatchFinder","No right matches",__FILE__,__LINE__);

	double max_distLeft = 0; double min_distLeft = 100;
	double max_distRight = 0; double min_distRight = 100;

    // Quick calculation of max and min distances between keypoints
	for( int i = 0; i < descriptorsPattern.rows; i++ )
	  	{ 
			double distLeft = matchesLeft[i].distance;
		  		if( distLeft < min_distLeft ) min_distLeft = distLeft;
		    		if( distLeft > max_distLeft ) max_distLeft = distLeft;
			double distRight = matchesRight[i].distance;
		    		if( distRight < min_distRight ) min_distRight = distRight;
		    		if( distRight > max_distRight ) max_distRight = distRight;
	  	}

    // Find the "good" matches

	vector<cv::DMatch> good_matchesLeft;
	for (int i = 0; i < matchesLeft.size(); ++i)
		{
	    		const float ratio = 50.0; // As in Lowe's paper; can be tuned
	    		if (matchesLeft[i].distance < ratio*min_distLeft)
	    		{
				good_matchesLeft.push_back(matchesLeft[i]);
	    		}
		}

	vector<cv::DMatch> good_matchesRight;
	for (int i = 0; i < matchesRight.size(); ++i)
		{
	    		const float ratio = 50.0; // As in Lowe's paper; can be tuned
	    		if (matchesRight[i].distance < ratio*min_distRight)
	   		{
				good_matchesRight.push_back(matchesRight[i]);
	    		}
		}

	Mat img_matchesLeft;
	Mat img_matchesRight;
	drawMatches( imgPattern, keypointsPattern, imgCameraLeft, keypointsCameraLeft,
			       good_matchesLeft, img_matchesLeft, Scalar::all(-1), Scalar::all(-1),
			       vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
	drawMatches( imgPattern, keypointsPattern, imgCameraRight, keypointsCameraRight,
			       good_matchesRight, img_matchesRight, Scalar::all(-1), Scalar::all(-1),
			       vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	/* If enough matches are found, we extract the locations of matched keypoints in both the images. They are passed to find the perpective transformation. Once we get this 3x3 transformation matrix, we use it to transform the corners of queryImage to corresponding points in trainImage. */ 

	if(good_matchesLeft.size() > minMatches) 
		{

		// Localize the object

	  	std::vector<Point2f> patternLeft;
		std::vector<Point2f> patternRight;
	  	std::vector<Point2f> cameraLeft;
		std::vector<Point2f> cameraRight;

	  	for( int i = 0; i < good_matchesLeft.size(); i++ )
		  	{
	    		// Get the keypoints from the good matches
	    		patternLeft.push_back( keypointsPattern[ good_matchesLeft[i].queryIdx ].pt );
	    		cameraLeft.push_back( keypointsCameraLeft[ good_matchesLeft[i].trainIdx ].pt );
		  	}

		for( int i = 0; i < good_matchesRight.size(); i++ )
		  	{
	    		// Get the keypoints from the good matches
	    		patternRight.push_back( keypointsPattern[ good_matchesRight[i].queryIdx ].pt );
	    		cameraRight.push_back( keypointsCameraRight[ good_matchesRight[i].trainIdx ].pt );
		  	}

	  	Mat H_Left = findHomography( patternLeft, cameraLeft, CV_RANSAC );	
		Mat H_Right = findHomography( patternRight, cameraRight, CV_RANSAC );

		// Get the corners from the image_1 ( the object to be "detected" )

	  	std::vector<Point2f> pattern_corners(4);
	  	pattern_corners[0] = cvPoint(0,0); 
		pattern_corners[1] = cvPoint( imgPattern.cols, 0 );
	  	pattern_corners[2] = cvPoint( imgPattern.cols, imgPattern.rows ); 
		pattern_corners[3] = cvPoint( 0, imgPattern.rows );
	  	std::vector<Point2f> camera_cornersLeft(4);
		std::vector<Point2f> camera_cornersRight(4);

	  	perspectiveTransform( pattern_corners, camera_cornersLeft, H_Left);
		perspectiveTransform( pattern_corners, camera_cornersRight, H_Right);

		// Draw lines between the corners (the mapped object in the scene - image_2 )
	
	  	line( img_matchesLeft, camera_cornersLeft[0] + Point2f( imgPattern.cols, 0), camera_cornersLeft[1] + Point2f( imgPattern.cols, 0), Scalar(0, 255, 0), 4 );
	  	line( img_matchesLeft, camera_cornersLeft[1] + Point2f( imgPattern.cols, 0), camera_cornersLeft[2] + Point2f( imgPattern.cols, 0), Scalar( 0, 255, 0), 4 );
	  	line( img_matchesLeft, camera_cornersLeft[2] + Point2f( imgPattern.cols, 0), camera_cornersLeft[3] + Point2f( imgPattern.cols, 0), Scalar( 0, 255, 0), 4 );
	  	line( img_matchesLeft, camera_cornersLeft[3] + Point2f( imgPattern.cols, 0), camera_cornersLeft[0] + Point2f( imgPattern.cols, 0), Scalar( 0, 255, 0), 4 );

		// Show detected matches

	  	imshow( "Good Matches Left & Pattern detection", img_matchesLeft );

		// Draw lines between the corners (the mapped object in the scene - image_2 )

	  	line( img_matchesRight, camera_cornersRight[0] + Point2f( imgPattern.cols, 0), camera_cornersRight[1] + Point2f( imgPattern.cols, 0), Scalar(0, 255, 0), 4 );
	  	line( img_matchesRight, camera_cornersRight[1] + Point2f( imgPattern.cols, 0), camera_cornersRight[2] + Point2f( imgPattern.cols, 0), Scalar( 0, 255, 0), 4 );
	  	line( img_matchesRight, camera_cornersRight[2] + Point2f( imgPattern.cols, 0), camera_cornersRight[3] + Point2f( imgPattern.cols, 0), Scalar( 0, 255, 0), 4 );
	  	line( img_matchesRight, camera_cornersRight[3] + Point2f( imgPattern.cols, 0), camera_cornersRight[0] + Point2f( imgPattern.cols, 0), Scalar( 0, 255, 0), 4 );

		// Show detected matches
	  	imshow( "Good Matches Right & Pattern detection", img_matchesRight );

		int c = 0;
		float sumXLeft = 0;
		float sumYLeft = 0;

			for( int i = 0; i < good_matchesLeft.size(); i++ )
			{
			  	// Sum over all x and y
			   	sumXLeft = sumXLeft + keypointsCameraLeft[ good_matchesLeft[i].trainIdx ].pt.x;
				sumYLeft = sumYLeft + keypointsCameraLeft[ good_matchesLeft[i].trainIdx ].pt.y;
				c++;
			}

		float 	avgXLeft = sumXLeft/c;
		float 	avgYLeft = sumYLeft/c;

		c = 0;
		float sumXRight = 0;
		float sumYRight = 0;

			for( int i = 0; i < good_matchesRight.size(); i++ )
			{
			  	// Sum over all x and y
			   	sumXRight = sumXRight + keypointsCameraRight[ good_matchesRight[i].trainIdx ].pt.x;
				sumYRight = sumYRight + keypointsCameraRight[ good_matchesRight[i].trainIdx ].pt.y;
				c++;
			}

		float 	avgXRight = sumXRight/c;
		float 	avgYRight = sumYRight/c;

		// Dimnesions of the input image from the camera
			float dim_x = 320;
			float dim_y = 240;

		// Scaling factor
			float KNOWN_DISTANCE = 0.45;
			float KNOWN_PIXEL = 106.83;

		// Calculate the x and y distance of the drone from the target
			landingXY[0] = (avgXLeft + avgXRight - (dim_x))/KNOWN_PIXEL;
			landingXY[1] = ((dim_y) - avgYLeft - avgYRight)/KNOWN_PIXEL;

		ROS_INFO("##### Landing %f ....", landingXY[0]);
		ROS_INFO("##### Landing %f ....", landingXY[1]);

		//Clear array
		array.data.clear();
	
		array.data.push_back(landingXY[0]);
		array.data.push_back(landingXY[1]);
		array.data.push_back(1);
	
		//Publish array

		ros::Duration(5.0).sleep();
		start = 0;
		}

	distance_landing.publish(array);

		
	//else
		//{
		//cvError(0,"MatchFinder","Not enough keypoints",__FILE__,__LINE__);
		//}
	
	}
    
    ros::spinOnce();
       	
    }

    
    return 0;
}




