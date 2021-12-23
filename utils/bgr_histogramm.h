#include "histogramm.h"
#include <vector>
#include <utility>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>


class BGR_Histogramm : public Histogramm
{
    public:
        BGR_Histogramm(cv::Mat* image, int h, int w);
        virtual ~BGR_Histogramm(){}
        virtual void draw_hist(int h, int w) override;
        virtual void calc_hist(int h, int w) override;
        virtual void show_hist() override;
        std::vector<cv::Mat> _bgr;
        cv::Mat _b_hist;
        cv::Mat _g_hist;
        cv::Mat _r_hist;
};
