/*
 *
 *  Example by Sam Siewert 
 *
 *  Created for OpenCV 4.x for Jetson Nano 2g, based upon
 *  https://docs.opencv.org/4.1.1
 *
 *  Tested with JetPack 4.6 which installs OpenCV 4.1.1
 *  (https://developer.nvidia.com/embedded/jetpack)
 *
 *  Based upon earlier simpler-capture examples created
 *  for OpenCV 2.x and 3.x (C and C++ mixed API) which show
 *  how to use OpenCV instead of lower level V4L2 API for the
 *  Linux UVC driver.
 *
 *  Verify your hardware and OS configuration with:
 *  1) lsusb
 *  2) ls -l /dev/video*
 *  3) dmesg | grep UVC
 *
 *  Note that OpenCV 4.x only supports the C++ API
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//#define SECS_IN_DAY (24 * 60 * 60)

using namespace cv;
using namespace std;

// See www.asciitable.com
#define ESCAPE_KEY (27)
#define SYSTEM_ERROR (-1)
#define BILLION  1000000000L

int main()
{
   VideoCapture cam0(0);
   namedWindow("video_display");
   char winInput;
   //clock_t start, end;
   //double time ;
   //start = clock();
   unsigned frameCount = 0;
   struct timespec start, stop;
   double accum,elapsedTime; 
   Mat frame;


   

   if (!cam0.isOpened())
   {
       exit(SYSTEM_ERROR);
   }

   cam0.set(CAP_PROP_FRAME_WIDTH, 640);
   cam0.set(CAP_PROP_FRAME_HEIGHT, 480);
   cout<<endl;
   cout<<"Calculating average frame rate over a period of 1 minute ..."<<endl;
   cout<<"Result will be printed after 1 minute and the program will terminate automatically."<<endl;
   cout<<endl;	
   clock_gettime( CLOCK_REALTIME, &start);
   while (1)
   {
      	
      
      cam0.read(frame);
      frameCount++;
      imshow("video_display", frame);
      //end = clock();

      
      //time = ((double)(end - start)) / CLOCKS_PER_SEC;
	//if(time >= 10){
		
		//break;
	//}
      winInput = waitKey(10);
      if (winInput == ESCAPE_KEY)
      //if ((winInput = waitKey(0)) == ESCAPE_KEY)
      {
          break;
      }
      else if(winInput == 'n')
      {
	  cout << "input " << winInput << " ignored" << endl;
      }
	clock_gettime( CLOCK_REALTIME, &stop);
	accum = ( stop.tv_sec - start.tv_sec ) + (( stop.tv_nsec - start.tv_nsec )/BILLION);
	clock_gettime( CLOCK_REALTIME, &start);
	elapsedTime+=accum;
	if(elapsedTime>=60)
	{
		cout<<"Average frame rate over a period of 1 minute: "<<(double)frameCount/elapsedTime<<" Frames per Second."<<endl;
		break;
	
		}
	
      //cout << "Frames" << count / 60.0 << endl;
   }

   destroyWindow("video_display"); 
};
