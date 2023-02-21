#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
 
using namespace cv;
using namespace std;
 
#define ESCAPE_KEY (27)
#define SYSTEM_ERROR (-1)
#define BILLION  1000000000L

 
int main()
{
    VideoCapture cam0(0);

    Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y, frame, dst, detected_edges, src, src_gray;
    
    struct timespec start, stop;
    double accum;
    
    unsigned frameCount=0;

    bool data = false;

    char winInput;
    
    namedWindow("video_display"); 
	
 
    if (!cam0.isOpened())
    {
       exit(SYSTEM_ERROR);
    }
 
    cam0.set(CAP_PROP_FRAME_WIDTH, 640);
    cam0.set(CAP_PROP_FRAME_HEIGHT, 480);
    cout<<endl;

    cout<<"Press 'n' or 'N' for Normal Video"<<endl;
    cout<<"Press 's' or 'S' for Sobel Edge Detection"<<endl;
    cout<<"Press 'c' or 'C' for Canny Edge Detection"<<endl;
    cout<<"Press ESC to quit"<<endl;
    

	winInput='n';

    while (1)
    {
        if(data == true)
            break;

        if(winInput=='s' || winInput=='S')
        {
	        clock_gettime( CLOCK_REALTIME, &start);

            while(1)
            {
		        cam0.read(frame);
		        frameCount++;
                
                GaussianBlur(frame, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
                // Convert the image to grayscale
                cvtColor(src, src_gray, COLOR_BGR2GRAY);
                
                Sobel(src_gray, grad_x, CV_16S, 1, 0, 1, 1, 0, BORDER_DEFAULT);
                Sobel(src_gray, grad_y, CV_16S, 0, 1, 1, 1, 0, BORDER_DEFAULT);
                // converting back to CV_8U
                convertScaleAbs(grad_x, abs_grad_x);
                convertScaleAbs(grad_y, abs_grad_y);
                addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
                imshow("video_display", grad);
                
                winInput = waitKey(10);
                
                if (winInput == ESCAPE_KEY)
                {	
                    data = true;
                    break;
                }

                if(winInput=='c' || winInput=='n' || winInput=='C' || winInput=='N')
                {   
                    clock_gettime( CLOCK_REALTIME, &stop);
                    accum = ( stop.tv_sec - start.tv_sec ) + (( stop.tv_nsec - start.tv_nsec )/BILLION);			
                    cout<<"Average frame rate for Sobel Edge Detection: "<<(double)frameCount/accum<<" Frames per second."<<endl;
                    frameCount=0;
                    break;
		        }
            }
        }
            
        if(winInput=='c' || winInput=='C')
        {
	        clock_gettime( CLOCK_REALTIME, &start);

            while(1)
            {
                cam0.read(frame);
                frameCount++;
                
                cvtColor( frame, src_gray, COLOR_BGR2GRAY );
                cvtColor( frame, src_gray, COLOR_BGR2GRAY );
                
                createTrackbar( "Min Threshold:", "video_display", 0, 100 );
                
                blur( src_gray, detected_edges, Size(3,3) );
                
                Canny( detected_edges, detected_edges, 0, 0, 3 );
                
                dst = Scalar::all(0);
            
                src_gray.copyTo( dst, detected_edges);
        
                imshow("video_display", dst);
                
                winInput = waitKey(10);
                
                if (winInput == ESCAPE_KEY)
                {
                    data =  true;
                    break;
                }
                
                if(winInput=='n' || winInput=='s' || winInput=='N' || winInput=='S')
                {   
                    clock_gettime( CLOCK_REALTIME, &stop);
                    accum = ( stop.tv_sec - start.tv_sec ) + (( stop.tv_nsec - start.tv_nsec )/BILLION);			
                    cout<<"Average frame rate for Canny Edge Detection: "<<(double)frameCount/accum<<" Frames per second."<<endl;
                    frameCount=0;
                    break;
		        }
            }
        }

        if(winInput == 'n' || winInput == 'N')
        {
	        clock_gettime( CLOCK_REALTIME, &start);
    
            while(1)
            {
                cam0.read(frame);
                frameCount++;
                
                imshow("video_display", frame);
                    
                winInput = waitKey(10);

                if (winInput == ESCAPE_KEY)
                {
                    data =  true;
                    break;
                }
                
                if(winInput=='c' || winInput=='s' || winInput=='C' || winInput=='S')
                {   
                    clock_gettime( CLOCK_REALTIME, &stop);
                    accum = ( stop.tv_sec - start.tv_sec ) + (( stop.tv_nsec - start.tv_nsec )/BILLION);			
                    cout<<"Average frame rate for Normal Video: "<<(double)frameCount/accum<<" Frames per second."<<endl;
                    frameCount=0;
                    break;
		        }
                
            }

        }
 
    }

    destroyWindow("video_display"); 
};
 


