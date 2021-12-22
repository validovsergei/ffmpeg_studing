#include "histogramm.h"


void Calculation_hist(const cv::Mat* images, cv::Mat& hist, int hist_w, int hist_h, cv::Mat& hist_image)
{
      int histSize = 256;
      float range[] = {0,256};
      const float * histRange[] = {range};
      cv::calcHist(images, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, true, false );
      cv::normalize(hist, hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
}

void draw_hist_(const std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>>&  windowhist, int hist_h, int hist_w)
{
      int histSize = 256;
      int bin_w = cvRound( (double) hist_w/histSize );
      for( int i = 1; i < histSize; i++ )
      {
            for(auto whc = windowhist.begin(); whc != windowhist.end(); ++whc)
            {
                  cv::line(whc->first, cv::Point(bin_w*(i-1), hist_h - cvRound(whc->second.first.at<float>(i-1)) ),
                  cv::Point(bin_w * (i), hist_h - cvRound(whc->second.first.at<float>(i)) ),
                  whc->second.second, 2, 8, 0 );
            }
      }
}


Histogramm::Histogramm(cv::Mat* image, int h, int w)
{
    _hist_image = cv::Mat((h, w, CV_8UC3, cv::Scalar( 0,0,0)));
    _src_image = image;
}


BGR_Histogramm::BGR_Histogramm(cv::Mat* image, int h, int w) : Histogramm(image, h, w)
{
    cv::split(*_src_image, _bgr);
}


void BGR_Histogramm::calc_hist() 
{
    Calculation_hist(&_bgr[0], _b_hist, 400, 512, _hist_image);
    Calculation_hist(&_bgr[1], _g_hist, 400, 512, _hist_image);
    Calculation_hist(&_bgr[2], _r_hist, 400, 512, _hist_image);
}


void BGR_Histogramm::draw_hist() 
{
    std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> winhist;
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_b_hist, cv::Scalar(255, 0, 0))));
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_g_hist, cv::Scalar( 0, 255, 0))));
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_r_hist, cv::Scalar( 0, 0, 255))));
    draw_hist_(winhist, 512, 400);
}


void BGR_Histogramm::show_hist() 
{
    cv::imshow("Histogramm for processed image", _hist_image);
    cv::waitKey(1000);
}


Gray_Histogramm::Gray_Histogramm(cv::Mat* image, int h, int w) : Histogramm(image, h, w)
{
    cv::cvtColor(*_src_image, _src_gray, cv::COLOR_BGR2GRAY);
}


 void Gray_Histogramm::calc_hist() 
{
    Calculation_hist(&_src_gray, _gray_hist, 400, 512, _hist_image);
}


void Gray_Histogramm::draw_hist() 
{
    std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> winhist;
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_gray_hist, cv::Scalar(255, 255, 255))));
    draw_hist_(winhist, 512, 400);
}


void Gray_Histogramm::show_hist() 
{
    cv::imshow("Gray Histogram for processed image", _hist_image);
    cv::waitKey(1000);
}