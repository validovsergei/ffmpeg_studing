#ifndef HIST_H
#define HIST_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>



void Calculation_hist(const cv::Mat* images, cv::Mat& hist, int hist_w, int hist_h, cv::Mat& hist_image);
void draw_hist_(const std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>>&  windowhist, int hist_h, int hist_w);



class Histogramm
{
    public:
        Histogramm(cv::Mat* image, int h, int w);
        virtual ~Histogramm(){}
        virtual void draw_hist(int h, int w)  = 0;
        virtual void calc_hist(int h, int w) = 0;
        virtual void show_hist() = 0;
        cv::Mat* _src_image;
        cv::Mat _hist_image;
};

#endif