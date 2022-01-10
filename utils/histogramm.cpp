#include "histogramm.h"



Histogramm::Histogramm(cv::Mat* image, int height, int width) {
    _hist_image = cv::Mat(height, width, CV_8UC3, cv::Scalar( 0,0,0));
    _src_image = image;
}