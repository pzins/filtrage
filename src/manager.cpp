#include "manager.h"
#include <iostream>
Manager* Manager::instance = 0;


Manager::Manager()
{

}


void Manager::addFilter(Filter& _filter){
    filters[_filter.getName()] = _filter;
}

void Manager::importImage(const std::string& _name, const std::string& _image){
    cv::Mat img = cv::imread(_image, CV_LOAD_IMAGE_GRAYSCALE);
    if(img.empty()){
        std::cout << "error image" << std::endl;
    } else {
        images[_name] = img;
    }
}



//compute convolution with normalization
float Manager::convolution_norm(const cv::Mat& _img, const cv::Mat& _kernel){
    if(_kernel.size != _img.size)
    {
        std::cerr << "Convolution impossible : size are different" << std::endl;
        return 0;
    }
    else
    {
        float res = 0;
        for(int i = 0; i < _img.rows; i++)
        {
            const char* kernel_line = _kernel.ptr<char>(i);
            const uchar* img_line = _img.ptr<uchar>(i);
            for(int j = 0; j < _img.cols; j++){
                res += static_cast<int>(*(kernel_line+j)) * static_cast<int>(*(img_line+j));
            }
        }
        res = res/(_kernel.rows*_kernel.cols);
        if(res < 0) return 0;
        if(res > 255) return 255;
        return res;
    }
}

//computer convolution without normalization
float Manager::convolution(const cv::Mat& _img, const cv::Mat& _kernel){
    if(_kernel.size != _img.size)
    {
        std::cerr << "Convolution impossible : size are different" << std::endl;
        return 0;
    }
    else
    {
        float res = 0;
        for(int i = 0; i < _img.rows; i++)
        {
            const char* kernel_line = _kernel.ptr<char>(i);
            const uchar* img_line = _img.ptr<uchar>(i);
            for(int j = 0; j < _img.cols; j++){
                res += static_cast<int>(*(kernel_line+j)) * static_cast<int>(*(img_line+j));
            }
        }
        if(res < 0) return 0;
        if(res > 255) return 255;
        return res;
    }
}

//filter _img with _kernel
void Manager::filter(cv::Mat& _img, const cv::Mat& _kernel)
{
    if(_kernel.rows != _kernel.cols)
    {
        std::cerr << "Error filter : kernel not a square" << std::endl;
    }
    else if(_kernel.rows % 2 != 1)
    {
        std::cerr << "Error filter : bad size kernel" << std::endl;
    }
    else
    {
        cv::Mat ref_img = _img.clone();
        int len = _kernel.rows/2;

        for(int i = len; i < ref_img.rows-len; i++)
        {
            uchar* element = _img.ptr<uchar>(i);
            for(int j = len; j < ref_img.cols-len; j++)
            {
                cv::Mat tmp = ref_img(cv::Rect(j-len, i-len, 2*len+1, 2*len+1));
                int res = convolution_norm(tmp, _kernel);
                *(element + j) = uchar(res);
            }
        }
    }
}
