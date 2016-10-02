#include "meanfilter.h"

MeanFilter::MeanFilter(int _size) : Filter("mean", _size), size(_size),
    kernel(cv::Mat::ones(_size, _size, CV_8U))

{

}
