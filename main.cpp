/*
OBJECT DETECTION ALGORITHM
*/
/*#include<cv.h>
#include<highgui.h>
#include<iostream>
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
Mat aa = imread("CAR.jpg");
imshow(" INITIALLY ", aa);
cout<<aa.size().height<<" this is the height and "<<aa.size().width<<endl;
for(int y=0;y<aa.size().height;y++)
	{
		uchar *row = aa.ptr(y);
		int maxi=0;//Point maxpt;
		for(int x=0;x<aa.size().width;x++)
		{
			//if(row[x]>=0)
			{
                 row[x]=0;
				//int area = floodFill(aa, Point(x,y), CV_RGB(0,0,64));

				//if(area>maxi)
				{
					//maxPt = Point(x,y);
				//	maxi = area;
				}
			}
		}
	}
		imshow(" AFTERWARDS ",aa);
         while(1){waitKey(0)!=32;}
//imshow(" xyz ",img);
//for(int i=0; i<img.rows; i++)
  //  {for(int j=0; j<img.cols; j++)
    // {
//     You can now access the pixel value with cv::Vec3b
//cout << img.at<cv::Vec3b>(i,j)[0] << " " << img.at<cv::Vec3b>(i,j)[1] << " " << img.at<cv::Vec3b>(i,j)[2] << endl;}}

return 0;
}*/
/*#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
int threshval = 100;

static void on_trackbar(int, void*)
{
    Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);
     imshow(" bw ",bw);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE );

    Mat dst = Mat::zeros(img.size(), CV_8UC3);

    if( !contours.empty() && !hierarchy.empty() )
    {
        // iterate through all the top-level contours,
        // draw each connected component with its own random color
        int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( (rand()&255), (rand()&255), (rand()&255) );
            drawContours( dst, contours, idx, color, CV_FILLED, 8,  hierarchy);
        }
    }

    imshow( "Connected Components", dst );
}

static void help()
{
    cout << "\n This program demonstrates connected components and use of the trackbar\n"
             "Usage: \n"
             "  ./connected_components <image(stuff.jpg as default)>\n"
             "The image is converted to grayscale and displayed, another image has a trackbar\n"
             "that controls thresholding and thereby the extracted contours which are drawn in color\n";
}

const char* keys =
{
    "{1| |stuff.jpg|image for converting to a grayscale}"
};

int main( int argc, const char** argv )
{
    help();
   // CommandLineParser parser(argc, argv, keys);
   // string inputImage = parser.get<string>("1");
    img = imread("stuff.jpg", 0);

    if(img.empty())
    {
      //  cout << "Could not read input image file: " << inputImage << endl;
        return -1;
    }

    namedWindow( "Image", 1 );
    imshow( "Image", img );

    namedWindow( "Connected Components", 1 );
    createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );
    on_trackbar(threshval, 0);

    waitKey(0);
    return 0;
}
*/
/*#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
            "Usage:\n"
            "./houghlines <image_name>, Default is pic1.png\n" << endl;
}

int main(int argc, char** argv)
{
    const char* filename = "left06.jpg";

    Mat src = imread(filename, 0);
    if(src.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

#if 0
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }
#else
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }
#endif
    imshow("source", src);
    imshow("detected lines", cdst);

    waitKey();

    return 0;
}
*/
#include<cv.h>
#include<highgui.h>
#include<iostream>
#include<map>
#define forr(i,val) for(int i=0;i<val;i++)
using namespace std;
using namespace cv;

Mat img1;
int al,be;
Mat img2;

void mycall(int xx,void*)
{   return ;
    int rows=min(img1.size().height,img2.size().height);
    int cols=min(img1.size().width,img2.size().width);
    int ch=min(img1.channels(),img2.channels());
    //int cols=img.size().width;int ch=img.channels();
     //  int rows=img1.size().height;
       //int cols=img1.size().width;
     //  int ch=img1.channels();
    double alpha=(double)al/100;
    double beta = ( 1.0 - alpha );
    //double beta=(double)be/100;
//    int beta=0;
    Mat newimg = Mat::zeros( img1.size(), img1.type() );;
    char cc;
    forr(y,rows)
    {
       // printf("%d ",y);
        forr(x,cols)
        {
       //     uchar *pt;
//            pt=newimg.ptr<uchar>(i,j);
            forr(c,ch)
         //// imshow(" NEW WINDOW",newimg);
           {
       // newimg.at<Vec3b>(y,x)[c] = alpha*( img1.at<Vec3b>(y,x)[c] ) ;
       // newimg.at<Vec3b>(y,x)[c] += beta*( img2.at<Vec3b>(y,x)[c] ) ;
      Vec3b temp=img1.at<Vec3b>(y,x);
      newimg.at<Vec3b>(y,x).val[c]=al;
      //if(temp.val[c]>5)
      {
      //  newimg.at<Vec3b>(y,x).val[c] = 255 ;
      }
      //else
      {
        //newimg.at<Vec3b>(y,x).val[c]= 0;
      }
         // imshow(" NEW WINDOW",newimg);
          // waitKey(20);
         //// while(!waitKey()!=27){}
          //cout<<" Enter";
          //cin>>cc;
  //  newimg.ptr<Vec3b>(i,j)[k]=(img1.ptr<Vec3b>(i,j)[k])+(al-50);
           //     *pt++=(img1.ptr<uchar>(i,j)[k])+(al-50);
          /////    printf("%d ",ch);
      //  newimg.at<Vec3b>(y,x)[c] =( ( img1.at<Vec3b>(y,x)[c] ) + al-50 );

            }
        }
    }
    imshow(" Nejejehj ",newimg);
     ////BLEND THE IMAGES
     /*
     printf(" inside ");
     int avg;
     forr(i,rows)
    {
        forr(j,cols)
        {
          //  uchar *pt;
        //    pt=img.ptr<uchar>(i,j);
            avg=0;
            forr(k,c)
            {
              avg+= *reinterpret_cast<const uint16_t*>(&newimg.ptr<Vec3b>(i,j)[k]);
              //avg=<int>(newimg.ptr<Vec3b>(i,j)[k]);

              // if(rows>)
               {
                 //newimg.ptr<Vec3b>(i,j)[k]=0;
               }
             //  newimg.ptr<Vec3b>(i,j)[k]=(alpha* img1.ptr<Vec3b>(i,j)[k])+(beta* img2.ptr<Vec3b>(i,j)[k]);
            }
            avg=avg/3;
            forr(k,c)
            {

              // if(rows>)
               {
                 //newimg.ptr<Vec3b>(i,j)[k]=0;
               }
        newimg.ptr<Vec3b>(i,j)[k]=avg;
            }
        }
    }
    imshow("Linear Blend",newimg);*/
}

int max_(Vec3b v1,Vec3b v2)
{
    double avg1=v1.val[0]+v1.val[1]+v1.val[2];
    double avg2=v2.val[0]+v2.val[1]+v2.val[2];
    if(avg1>=avg2){return 1;}
    return 0;
}
void MyFilledCircle( Mat img, Point center )
{
 int thickness = -1;
 int lineType = 8;

 circle( img,
         center,
         20,
         Scalar( 0, 0, 255 ),
         thickness,
         lineType );
}
#define pi pair<int,int>
#define pii pair<pi,int>
#define ff first
#define ss second
map<pii,int >MP;//Mat ini;
void threshold(int,void*)
{
    int rows=img1.size().height;int cols=img1.size().width;
    int c=img1.channels();
     //imshow()
     Mat newimg=Mat::zeros(img1.size(),img1.type());
     int beta;
     double avg;Mat newimg2=Mat(img1.size(),0);
    // Vec3b maxi;maxi.val[0]=0;maxi.val[1]=0;maxi.val[2]=0;
      int maxi=0;
    /*forr(i,rows)
    {
        forr(j,cols)
        {
          Vec3b temp=img1.at<Vec3b>(i,j);
          pii temp2;temp2.ff.ff=temp.val[0];temp2.ff.ss=temp.val[1];
          temp2.ss=temp.val[2];
          MP[temp2]=MP[temp2]+1;;
          maxi=max(maxi,MP[temp2]);
        }
    }*/
    //Vec3b maxx,threshh;
    //threshh.val[0]=50;threshh.val[1]=50;threshh.val[2]=50;;
    //printf("MAXI is %d \n",maxi);int cnt=0;
   /*forr(i,rows)
    {
        forr(j,cols)
        {
          Vec3b temp=img1.at<Vec3b>(i,j);
          pii temp2;temp2.ff.ff=temp.val[0];temp2.ff.ss=temp.val[1];
          temp2.ss=temp.val[2];
          if(MP[temp2]==maxi)
          {
              cnt++;
              maxx=temp;
             printf("YO\n");;
          }

         }
    }
    cout<<cnt;*/
//    printf("Here is the maxi %d %d %d\n",maxi.val[0]),maxi.val[1],maxi.val[2];
     forr(i,rows)
    {
        forr(j,cols)
        {
            //forr(c,3)
            {
                Vec3b temp=img1.at<Vec3b>(i,j);
                if(temp.val[0]>al || temp.val[0]>al || temp.val[0]>al)
                {
                    newimg.at<Vec3b>(i,j).val[0]=255;
                    newimg.at<Vec3b>(i,j).val[1]=255;
                    newimg.at<Vec3b>(i,j).val[2]=255;
                }
                else
                {
                    newimg.at<Vec3b>(i,j).val[0]=0;
                    newimg.at<Vec3b>(i,j).val[1]=0;
                    newimg.at<Vec3b>(i,j).val[2]=0;
                }
             //Vec3b temp=img1.at<Vec3b>(i,j);
            // pii temp2;temp2.ff.ff=temp.val[0];temp2.ff.ss=temp.val[1];
            // temp2.ss=temp.val[2];
            // if(temp-maxx==threshh || maxx-temp==threshh)
             {
                 //newimg.at<Vec3b>(i,j).val[0]=0;newimg.at<Vec3b>(i,j).val[1]=0;newimg.at<Vec3b>(i,j).val[2]=0;
                 //MyFilledCircle(newimg,Point(j,i));
                 //continue;
             }
             //newimg.at<Vec3b>(i,j)=temp;
             //  if(temp.val[0]>al || temp.val[1]>al || temp.val[2]>al)
              // newimg.at<Vec3b>(i,j)=temp;
               {
      // double avg=temp.val[0]+temp.val[1]+temp.val[2];
      // avg=avg/3;
     //   newimg.at<Vec3b>(i,j).val[0]=avg;newimg.at<Vec3b>(i,j).val[1]=avg;newimg.at<Vec3b>(i,j).val[2]=avg;
               }
            }}}
          //  uchar *pt;
        //    pt=img.ptr<uchar>(i,j);
           // avg=0;

           // forr(k,c)
            ////{
              //avg+= (*reinterpret_cast<double*>(&img1.ptr<Vec3b>(i,j)[k]));
             // if(k==0)
            //  {
               //newimg.ptr<Vec3b>(i,j)[0]=newimg.ptr<Vec3b>(i,j)[c-1]/3;break;
              //}
             //newimg.ptr<Vec3b>(i,j)[k]=newimg.ptr<Vec3b>(i,j)[k-1]+img1.ptr<Vec3b>(i,j)[k];
              //avg=<int>(newimg.ptr<Vec3b>(i,j)[k]);

              // if(rows>)
            //   {
                 //newimg.ptr<Vec3b>(i,j)[k]=0;
             //  }
    //newimg.ptr<Vec3b>(i,j)[k]=(alpha* img1.ptr<Vec3b>(i,j)[k])+(beta* img2.ptr<Vec3b>(i,j)[k]);
           // }
           //// avg=avg/3;
            //newimg.ptr<Vec3b>(i,j)[k]= newimg.ptr<Vec3b>(i,j)[c-1];
            //newimg.ptr<Vec3b>(i,j)[0]=(newimg.ptr<Vec3b>(i,j)[c-1])/3;
           //newimg2.ptr<Vec3b>(i,j)[0]=(newimg.ptr<Vec3b>(i,j)[c-1])/3;

          //  forr(k,c)
            //{
             // if(k==0)
             // {
               //   break;continue;
             //// }
            /*     Vec3b temp=img1.ptr<Vec3b>(i,j)[k];
                 if((int)temp(0)>30)
                 {newimg.ptr<Vec3b>(i,j)[k]=(Vec3b)()}
            int avg=0;
            avg= c.val[0];
            avg+=newimg.ptr<Vec3b>(i,j)[k].val[1];
            avg+=newimg.ptr<Vec3b>(i,j)[k].val[2];
            avg=avg/3;
            Vec3b temp2;
            temp2.val[0]=avg;temp2.val[1]=avg;temp2.val[2]=avg;
            newimg.ptr<Vec3b>(i,j)[k]=temp2;
           */   //   else
             ////   {
                //      newimg.ptr<Vec3b>(i,j)[k]=0;

              //   }
              // if(rows>)
              // {
                 //newimg.ptr<Vec3b>(i,j)[k]=0;
      //         }
          //  newimg.ptr<Vec3b>(i,j)[k]=256;
      //  newimg.ptr<Vec3b>(i,j)[k]=(newimg.ptr<Vec3b>(i,j)[c-1])/3;
          //  }
        //}
    //}
    imshow(" THRESHOLDED IMAGE",newimg);
}
#define forr(i,N) for(int i=0;i<N;i++)
Mat copyy(Mat img)
{
    printf("\n COPYING");
    Mat ret=Mat(img.size(),img.type());
    forr(i,img.rows)
    {
        forr(j,img.cols)
        {
            Vec3b temp=img.at<Vec3b>(i,j);
            ret.at<Vec3b>(i,j)=temp;
        }
    }
    return ret;
}
int th=100;
Mat removebg(Mat img1,Mat img2)
{
     //return img1-img2;
     Mat ret=Mat(img1.size(),img1.type());
     Vec3b black;black.val[0]=0;black.val[1]=0; black.val[2]=0;
      Vec3b red;red.val[0]=rand()%256;red.val[1]=rand()%256; red.val[2]=rand()%256;
     forr(i,img1.rows)
     {
         forr(j,img1.cols)
         {
             Vec3b temp1=img1.at<Vec3b>(i,j);
             Vec3b temp2=img2.at<Vec3b>(i,j);
             if(abs(temp1.val[0]-temp2.val[0])<th && abs(temp1.val[1]-temp2.val[1])<th && abs(temp1.val[2]-temp2.val[2])<th)
             {
                 ret.at<Vec3b>(i,j)=black;
             }
             else
             {
                ret.at<Vec3b>(i,j)=red;
             }
          }
     }
     return ret;
}

int main()
{
    img1=imread("hand.jpg",1);
    //img2=imread("text.jpg",1);
    imshow(" Intially1 ",img1 );
    //imshow(" Intially2",img2 );
    //cout<<" "<<img1.size().height<<endl;
    //cout<<" "<<img1.size().width<<endl;
    ///cout<<" "<<img1.channels()<<endl;
    //namedWindow("Linear Blend", 1);
    int rows=img1.size().height;int cols=img1.size().width;int ch=img1.channels();
    al=50;//be=50;
    namedWindow("TRAKBAR");
    createTrackbar( " ALPHA ","TRAKBAR", &th, 256,mycall);
    VideoCapture cp(0);
    cp>>img1;int cnt=0;//Mat backg;
    Mat backg=Mat(img1.size(),img1.type());
    while(1)
    {
        cp>>img1;
        cnt++;
        imshow("Initially ",img1);
        //Mat res;res=Mat(img1.size(),img1.type());
        //printf(" Here %d \n\n\n\n",cnt);
        if(cnt<80)
        {
           continue;
        }
        else if(cnt==80)
        {
            backg=copyy(img1);
        }
        printf(" Out side ");
        imshow("Background",backg);
        imshow("Result",removebg(img1,backg));
        //temp=img1;
        int cc=waitKey(10);
        if(cc!=-1){ break;}
        continue;
    }
    //threshold(img1,al);
    //Vec3b check;
    //check=img1.ptr<Vec3b>(0,0)[3];
    //printf(" here %d",check.val[0]);
//    createTrackbar( TrackbarName," ALPHA ",&al,100,mycall);

//    createTrackbar( " ALPHA ", "Linear Blend", &al, 100, mycall);
    //createTrackbar(" BETA ","Linear Blend",&be,100,mycall);
    //mycall( al , 0);
    //mycall( al, 0 );
    //imshow("Linear Blend", img);
   // Point3_<uchar>* p = img1.ptr<Point3_<uchar> >(0,0);
   // //printf("%d ",p->x);
    //cv::Mat img = cv::imread("CAR.jpg");
//cout<<" heere "<<img.at<Vec3b>(0,0)[0]<<endl;
//cv::Mat newimg(img1.size(),img1.type());
//for(int i=0; i<img.rows; i++)
  //{
    //  for(int j=0; j<img.cols; j++)
      // {

       // You can now access the pixel value with cv::Vec3b
        //for(int c=0;c<img1.channels();c++)
        //{
          //  printf(" %d",j);
        //if( printf("inside "),img1.at<Vec3b>(i,j)[0]>10 , printf("inside "))
          //  {
          // printf("bbwr jkr  %d",img1.at<Vec3b>(i,j)[0]);
          //    ///   cout<<img1.at<Vec3b>(i,j)[0]<<" here  ";
        //    }
           // else{
             //       printf("inside");
            //    newimg.at<Vec3b>(i,j)[0]=0;
      //      }
    //    }
  //std::cout << img.at<Vec3b>(i,j)[0].val[0] << " " << img.at<Vec3b>(i,j)[1] << " " << img.at<Vec3b>(i,j)[2] << std::endl;
  //}
  //imshow(" Winnfw ",img1);
   while(waitKey()!=27){}
}
