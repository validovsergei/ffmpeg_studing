#include "bgr_histogramm.h"


BGR_Histogramm::BGR_Histogramm(cv::Mat* image, int h, int w) : Histogramm(image, h, w)
{
    cv::split(*_src_image, _bgr);
}


void BGR_Histogramm::calc_hist(int h, int w) 
{
    Calculation_hist(&_bgr[0], _b_hist, w, h, _hist_image);
    Calculation_hist(&_bgr[1], _g_hist, w, h, _hist_image);
    Calculation_hist(&_bgr[2], _r_hist, w, h, _hist_image);
}


void BGR_Histogramm::draw_hist(int h, int w) 
{
    std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> winhist;
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_b_hist, cv::Scalar(255, 0, 0))));
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_g_hist, cv::Scalar( 0, 255, 0))));
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_r_hist, cv::Scalar( 0, 0, 255))));
    draw_hist_(winhist, h, w);
}


void BGR_Histogramm::show_hist() 
{
    cv::imshow("Histogramm for processed image", _hist_image);
    cv::waitKey(10);
}