#include "frame_handler.h"


cv::Mat Frame_Handler::AVFrametoCvMat(AVFrame * frame) {
     int imageHeight = frame->height;
     int imageWidth = frame->width;
     cv::Mat image(imageHeight, imageWidth, CV_8UC3);
     int cvLinesize[1];
     cvLinesize[0] = image.step1();
     SwsContext * conversion = sws_getContext( imageWidth, imageHeight,(AVPixelFormat)frame->format, imageWidth, imageHeight, AVPixelFormat::AV_PIX_FMT_BGR24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
     sws_scale(conversion, frame->data, frame->linesize, 0, imageHeight, &image.data,
     cvLinesize);
     sws_freeContext(conversion);
     return image;
}


Frame_Handler::Frame_Handler(AVFrame * frame) {
    _src_image = AVFrametoCvMat(frame);
}


void Frame_Handler::showImage() {
    cv::imshow("Source image", _src_image);
    cv::waitKey(10);
}


void Frame_Handler::showHistogramms(int height, int width) {
    Gray_Histogramm  g_hist(&_src_image, height, width);
    BgrHistogramm  bgr_hist(&_src_image, height, width);
    g_hist.calculationHistogramm(height, width);
    bgr_hist.calculationHistogramm(height, width);
    g_hist.drawHistogramm(height, width);
    bgr_hist.drawHistogramm(height, width);
    g_hist.showHistogramm();
    bgr_hist.showHistogramm();
}
