#include	<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using	namespace	std;
using	namespace	cv;

Mat sobel(Mat source)
{
    Mat img(source.size().height, source.size().width, CV_8UC1);
    int p00, p01, p02, p10, p12, p20, p21, p22;
    int H,V, GN;
    for(int i  = 0; i < img.size().height * img.size().width; ++i)
    {
        p00 = source.at<uchar>(i);
        p01 = source.at<uchar>(i+1);
        p02 = source.at<uchar>(i+2);
        p10 = source.at<uchar>(i+img.size().width);
        p12 = source.at<uchar>(i+img.size().width+2);
        p20 = source.at<uchar>(i+2*img.size().width);
        p21 = source.at<uchar>(i+2*img.size().width+1);
        p22 = source.at<uchar>(i+2*img.size().width+2);
        H = -p00-2*p01-p02+p20+2*p21+p22;
        V = -p00+p02-2*p10+2*p12-p20+p22;

        GN = abs(H) + abs(V);
        if(GN > 255) GN = 255;
        img.at<uchar>(i) = GN;
    }
    return img;
}


Mat prewitt(Mat source)
{
    Mat img(source.size().height, source.size().width, CV_8UC1);
    int p00, p01, p02, p10, p12, p20, p21, p22;
    int H,V, GN;
    for(int i  = 0; i < img.size().height * img.size().width; ++i)
    {
        p00 = source.at<uchar>(i);
        p01 = source.at<uchar>(i+1);
        p02 = source.at<uchar>(i+2);
        p10 = source.at<uchar>(i+img.size().width);
        p12 = source.at<uchar>(i+img.size().width+2);
        p20 = source.at<uchar>(i+2*img.size().width);
        p21 = source.at<uchar>(i+2*img.size().width+1);
        p22 = source.at<uchar>(i+2*img.size().width+2);
        H = -p00-p01-p02+p20+p21+p22;
        V = -p00+p02-p10+p12-p20+p22;

        GN = abs(H) + abs(V);
        if(GN > 255) GN = 255;
        img.at<uchar>(i) = GN;
    }
    return img;
}


Mat gauss(Mat& source)
{
    Mat res(source.size().width, source.size().height, CV_8UC1);
    blur(source, res, Size(3,3));
    return res;
}

int main()
{
    Mat img = imread("ol.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if(img.empty()){
        std::cout << "error image" << std::endl;
    }
    namedWindow("win");
    imshow("win",img);
    std::cout << "press any key to exit \n";
    waitKey();
    return 0;
}



void video(){
    VideoCapture webcam(0);
    Mat frame, other;
    double fps=20;
    if(!webcam.isOpened())
        return ;
    int width = (int)webcam.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = (int)webcam.get(CV_CAP_PROP_FRAME_HEIGHT);
    namedWindow("OL");
    while(1)
    {
        webcam >> frame; // Read frame from camera
        cvtColor(frame, other, CV_BGR2GRAY);
        imshow("Sobel", sobel(gauss(other))); // Show frame
        imshow("Prewitt", prewitt(other)); // Show frame
        if (waitKey(1000/fps) >= 0)
        break;
    }
    webcam.release();
}

/**
  filtre passe-bas :
    -   filtre moyen
    -   fitlre gaussien
    -   filtre median
    -   filtre median adaptatif



  filtre passe-haut :
    -   filtre high-boost
    -   filtre gradient
    -   filtre Laplacien

 modèle de bruit :
    -   bruit gaussien
    -   bruit blanc
    -   bruit povire/sel

 filtrage morphologique :
    -   translation
    -   errosion
**/
