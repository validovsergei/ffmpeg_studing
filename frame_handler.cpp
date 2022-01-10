#include "frame_handler.h"


cv::Mat Frame_Handler::AVFrametoCvMat(AVFrame * frame)
{
     int image_height = frame->height;
     int image_width = frame->width;
     cv::Mat image(image_height, image_width, CV_8UC3);
     int cvLinesize[1];
     cvLinesize[0] = image.step1();
     SwsContext * conversion = sws_getContext( image_width, image_height,(AVPixelFormat)frame->format, image_width, image_height, AVPixelFormat::AV_PIX_FMT_BGR24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
     sws_scale(conversion, frame->data, frame->linesize, 0, image_height, &image.data,
     cvLinesize);
     sws_freeContext(conversion);
     return image;
}


Frame_Handler::Frame_Handler(AVFrame * frame)
{
    _src_image = AVFrametoCvMat(frame);
}


void Frame_Handler::show_image()
{
    cv::imshow("Source image", _src_image);
    cv::waitKey(1000);
}


void Frame_Handler::show_histogramms()
{
    Gray_Histogramm  g_hist(&_src_image, 512, 400);
    BGR_Histogramm  bgr_hist(&_src_image, 512, 400);
    g_hist.calc_hist();
    bgr_hist.calc_hist();
    g_hist.draw_hist();
    bgr_hist.draw_hist();
    g_hist.show_hist();
    bgr_hist.show_hist();
}
