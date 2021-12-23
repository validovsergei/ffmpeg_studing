#include "gray_histogramm.h"


Gray_Histogramm::Gray_Histogramm(cv::Mat* image, int h, int w) : Histogramm(image, h, w)
{
    cv::cvtColor(*_src_image, _src_gray, cv::COLOR_BGR2GRAY);
}


 void Gray_Histogramm::calc_hist(int h, int w) 
{
    Calculation_hist(&_src_gray, _gray_hist, w, h, _hist_image);
}


void Gray_Histogramm::draw_hist(int h, int w) 
{
    std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> winhist;
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_gray_hist, cv::Scalar(255, 255, 255))));
    draw_hist_(winhist, h, w);
}


void Gray_Histogramm::show_hist() 
{
    cv::imshow("Gray Histogram for processed image", _hist_image);
    cv::waitKey(10);
}