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