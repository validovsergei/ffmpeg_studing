#include "histogramm.h"
#include <vector>
#include <utility>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>


class Gray_Histogramm : public Histogramm
{
    public:
        Gray_Histogramm(cv::Mat* image, int h, int w);
        virtual ~Gray_Histogramm(){}
        virtual void draw_hist(int h, int w) override;
        virtual void calc_hist(int h, int w) override;
        virtual void show_hist() override;
        cv::Mat _gray_hist;
        cv::Mat _src_gray;
};
