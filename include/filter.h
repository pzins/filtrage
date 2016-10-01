#ifndef FILTER_H
#define FILTER_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

class Filter
{
private:
    std::string name;
    int size;
    cv::Mat kernel;
public:
    Filter(const std::string& _name, int _size, const cv::Mat& _kernel);
    Filter(const std::string& _name, int _size);
    Filter();
    virtual ~Filter(){}
};

#endif // FILTER_H
