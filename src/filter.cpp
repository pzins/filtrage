#include "filter.h"

Filter::Filter(const std::string &_name, int _size, const cv::Mat &_kernel) :
    name(_name), size(_size), kernel(_kernel)
{

}


Filter::Filter(const std::string& _name, int _size) : name(_name), size(_size)
{

}

Filter::Filter() : name(""), size(0)
{

}
