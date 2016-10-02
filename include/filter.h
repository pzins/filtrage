#ifndef FILTER_H
#define FILTER_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

class Filter
{
private:
    int size;
    cv::Mat kernel;
protected:
    std::string name;
public:
    Filter(const std::string& _name, int _size, const cv::Mat& _kernel);
    Filter(const std::string& _name, int _size);
    Filter();
    virtual ~Filter(){}
    std::string& getName() {return name;}
};

#endif // FILTER_H
