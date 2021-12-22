#ifndef HIST_H
#define HIST_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <utility>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>


#include <iostream>


void Calculation_hist(const cv::Mat* images, cv::Mat& hist, int hist_w, int hist_h, cv::Mat& hist_image);
void draw_hist(const std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>>&  windowhist, int hist_h, int hist_w);



class Histogramm
{
    public:
        Histogramm(cv::Mat* image, int h, int w);
        virtual ~Histogramm(){}
        virtual void draw_hist()  = 0;
        virtual void calc_hist() = 0;
        virtual void show_hist() = 0;
        cv::Mat* _src_image;
        cv::Mat _hist_image;
};


class BGR_Histogramm : public Histogramm
{
    public:
        BGR_Histogramm(cv::Mat* image, int h, int w);
        virtual ~BGR_Histogramm(){}
        virtual void draw_hist() override;
        virtual void calc_hist() override;
        virtual void show_hist() override;
        std::vector<cv::Mat> _bgr;
        cv::Mat _b_hist;
        cv::Mat _g_hist;
        cv::Mat _r_hist;
};


class Gray_Histogramm : public Histogramm
{
    public:
        Gray_Histogramm(cv::Mat* image, int h, int w);
        virtual ~Gray_Histogramm(){}
        virtual void draw_hist() override;
        virtual void calc_hist() override;
        virtual void show_hist() override;
        cv::Mat _gray_hist;
        cv::Mat _src_gray;

        
};

#endif