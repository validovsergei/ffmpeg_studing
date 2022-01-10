#include "histogramm.h"

#include <vector>
#include <utility>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>


class BgrHistogramm : public Histogramm {
    public:
        BgrHistogramm(cv::Mat* image, int h, int w);
        virtual ~BgrHistogramm(){}
        virtual void drawHistogramm(int h, int w) override;
        virtual void calculationHistogramm(int h, int w) override;
        virtual void showHistogramm() override;
        std::vector<cv::Mat> _bgr;
        cv::Mat _bHist;
        cv::Mat _gHist;
        cv::Mat _rHist;
};
