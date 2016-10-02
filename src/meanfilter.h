#ifndef MEANFILTER_H
#define MEANFILTER_H
#include <opencv2/opencv.hpp>
#include "filter.h"
class MeanFilter : public Filter
{
public:
    MeanFilter(int _size);
    const cv::Mat& getKernel(){return kernel;}
private:
    cv::Mat kernel;
    int size;
};

#endif // MEANFILTER_H
