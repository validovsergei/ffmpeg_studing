#ifndef HIST_H
#define HIST_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>



//void calculationHist(const cv::Mat* images, cv::Mat& hist, int hist_w, int hist_h, cv::Mat& hist_image);
//void drawHistogramm_(const std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>>&  windowhist, int hist_h, int hist_w);
namespace {
      void calculationHist(const cv::Mat* images, cv::Mat& hist, int hist_w, int hist_h, cv::Mat& hist_image) {
            int histSize = 256;
            float range[] = {0,256};
            const float * histRange[] = {range};
            cv::calcHist(images, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, true, false );
            cv::normalize(hist, hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
      }

      void drawingHistogramm(const std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>>&  windowHistogramm, int histHeight, int histWidth) {
            int histSize = 256;
            int binWidth = cvRound( (double) histWidth/histSize );
            for( int i = 1; i < histSize; i++ ) {
                  for(auto whc = windowHistogramm.begin(); whc != windowHistogramm.end(); ++whc) {
                        cv::line(whc->first, cv::Point(binWidth*(i-1), histHeight - cvRound(whc->second.first.at<float>(i-1)) ),
                        cv::Point(binWidth * (i), histHeight - cvRound(whc->second.first.at<float>(i)) ),
                        whc->second.second, 2, 8, 0 );
                  }
            }
      }
}


class Histogramm {
    public:
        Histogramm(cv::Mat* image, int height, int width);
        virtual ~Histogramm(){}
        virtual void drawHistogramm(int height, int width)  = 0;
        virtual void calculationHistogramm(int height, int width) = 0;
        virtual void showHistogramm() = 0;
        cv::Mat* _src_image;
        cv::Mat _hist_image;
};

#endif