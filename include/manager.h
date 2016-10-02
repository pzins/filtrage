#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include "filter.h"

class Manager
{
public:
    static Manager& getInstance(){
        if(!instance){
            instance = new Manager();
            return *instance;
        }
        return *instance;
    }
    void print(){std::cout << "Hello I'm the manager" << std::endl;}

    void addFilter(Filter &_filter);
    void importImage(const std::string& _name, const std::string& _image);

    void filter(cv::Mat& _img, const cv::Mat& _kernel);

    //TODO : check if image/filter _name exists and change this way to filter
    cv::Mat& getImage(const std::string& _name) {images.at(_name);}
    const cv::Mat& getKernel(const std::string& _name) const {filters.at(_name);}

private:
    Manager();
    static Manager* instance;
    std::map<std::string, Filter> filters;
    std::map<std::string, cv::Mat> images;

    float convolution(const cv::Mat& _img, const cv::Mat& _kernel);
    float convolution_norm(const cv::Mat& _img, const cv::Mat& _kernel);

};

#endif // MANAGER_H
