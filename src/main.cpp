#include	<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "manager.h"
#include "meanfilter.h"

using	namespace	std;
using	namespace	cv;

//print Mat image CV_8U
void printMat(const Mat& m){
    for(int i = 0; i < m.rows; i++)
    {
        const uchar* pt = m.ptr<uchar>(i);
        for(int j = 0; j < m.cols; j++)
            std::cout << static_cast<unsigned>(*(pt+j)) << " ";
        std::cout << std::endl;
    }
}
//print Mat kernel CV_8S
void printKernel(const Mat& m){
    for(int i = 0; i < m.rows; i++)
    {
        const char* pt = m.ptr<char>(i);
        for(int j = 0; j < m.cols; j++)
            std::cout << static_cast<int>(*(pt+j)) << " ";
        std::cout << std::endl;
    }
}


int main()
{
//    Mat kernel = (Mat_<char>(3,3) << -1,0,1,-2,0,2,-1,0,1);
//    Mat kernel = (Mat_<char>(3,3) << -1,-1,-1,-1,8,-1,-1,-1,-1);
    Mat kernel = Mat::ones(7,7, CV_8U);
    MeanFilter mf(3);
    Manager m = Manager::getInstance();
    m.addFilter(mf);
    m.importImage("lyon","lyon.jpg");

    namedWindow("original");
    imshow("original",m.getImage("lyon"));

    m.filter(m.getImage("lyon"), m.getKernel("mean"));
    namedWindow("filtered");
    imshow("filtered", m.getImage("lyon"));
    waitKey();
    return 0;
}


//add filterFactory

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


/**
 vendredi 30 septembre : premiere etape : lib de base
 20h-21h --> 0h-1h-2h

 architecture du système : use case, classes, ...
 juste un main basique qui ouvre une image et applique le filtre
 d'abord PB, puis PH, puis bruit, puis morpho
 only CLI


 ==>
 trucs basique à faire : 
 myclass matrice (ou celle de opencv Mat, je sais pas encore)
 parcours image
 convolution, différentes tailles possibles

fonctionnalités : 
charger un kernel
taille du kernel (check taille impaire par ex)

si temps essayer d'en faire une vraie lib qi pourra être utilisée plus tard (par l'interface graphique par ex, ou autre chose)
...
	
**/





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


Mat gauss(Mat& source)
{
    Mat res(source.size().width, source.size().height, CV_8UC1);
    blur(source, res, Size(3,3));
    return res;
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
