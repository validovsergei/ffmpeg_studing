#include "gray_histogramm.h"


Gray_Histogramm::Gray_Histogramm(cv::Mat* image, int height, int width) : Histogramm(image, height, width) {
    cv::cvtColor(*_src_image, _src_gray, cv::COLOR_BGR2GRAY);
}


 void Gray_Histogramm::calculationHistogramm(int height, int width) {
    calculationHist(&_src_gray, _gray_hist, width, height, _hist_image);
}


void Gray_Histogramm::drawHistogramm(int height, int width) {
    std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> winhist;
    winhist.push_back(std::make_pair(_hist_image, std::make_pair(_gray_hist, cv::Scalar(255, 255, 255))));
    drawingHistogramm(winhist, height, width);
}


void Gray_Histogramm::showHistogramm() {
    cv::imshow("Gray Histogram for processed image", _hist_image);
    cv::waitKey(10);
}