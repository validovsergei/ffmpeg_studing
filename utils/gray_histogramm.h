#include "histogramm.h"

#include <vector>
#include <utility>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>


class Gray_Histogramm : public Histogramm {
    public:
        Gray_Histogramm(cv::Mat* image, int height, int width);
        virtual ~Gray_Histogramm(){}
        virtual void drawHistogramm(int height, int width) override;
        virtual void calculationHistogramm(int height, int width) override;
        virtual void showHistogramm() override;
        cv::Mat _gray_hist;
        cv::Mat _src_gray;
};
