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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// See www.asciitable.com
#define ESCAPE_KEY (27)
#define SYSTEM_ERROR (-1)

int main()
{
   VideoCapture cam0(0);
   namedWindow("video_display");
    // Default resolution is 360p
    int hres = 640;
    int vres = 480;
   char winInput;

   if (!cam0.isOpened())
   {
       exit(SYSTEM_ERROR);
   }

   cam0.set(CAP_PROP_FRAME_WIDTH, 640);
   cam0.set(CAP_PROP_FRAME_HEIGHT, 480);

   while (1)
   {
      Mat frame;
      cam0.read(frame);
      


 // Draw a 4-pixel width border around the image
	//Mat frame(vres, hres, CV_8UC3)
    rectangle(frame, Point(0, 0), Point(hres-1, vres-1), Scalar(0, 255, 255), 4);

    // Draw a single pixel yellow cross-hairs down the middle column of the image and through the middle row of the image
    line(frame, Point(hres/2, 0), Point(hres/2, vres-1), Scalar(0, 255, 255), 1);
    line(frame, Point(0, vres/2), Point(hres-1, vres/2), Scalar(0, 255, 255), 1);

imshow("video_display", frame);

      if ((winInput = waitKey(10)) == ESCAPE_KEY)
      //if ((winInput = waitKey(0)) == ESCAPE_KEY)
      {
          break;


      }
      else if(winInput == 'n')
      {
	  cout << "input " << winInput << " ignored" << endl;
      }
      
   }

   destroyWindow("video_display"); 
};
