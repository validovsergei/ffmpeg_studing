#include "bgr_histogramm.h"


BgrHistogramm::BgrHistogramm(cv::Mat* image, int height, int width) : Histogramm(image, height, width) {
    cv::split(*_src_image, _bgr);
}


void BgrHistogramm::calculationHistogramm(int height, int width) {
    calculationHist(&_bgr[0], _bHist, width, height, _hist_image);
    calculationHist(&_bgr[1], _gHist, width, height, _hist_image);
    calculationHist(&_bgr[2], _rHist, width, height, _hist_image);
}


void BgrHistogramm::drawHistogramm(int height, int width) {
    std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> windowHistogramm;
    windowHistogramm.push_back(std::make_pair(_hist_image, std::make_pair(_bHist, cv::Scalar(255, 0, 0))));
    windowHistogramm.push_back(std::make_pair(_hist_image, std::make_pair(_gHist, cv::Scalar( 0, 255, 0))));
    windowHistogramm.push_back(std::make_pair(_hist_image, std::make_pair(_rHist, cv::Scalar( 0, 0, 255))));
    drawingHistogramm(windowHistogramm, height, width);
}


void BgrHistogramm::showHistogramm() {
    cv::imshow("Histogramm for processed image", _hist_image);
    cv::waitKey(10);
}