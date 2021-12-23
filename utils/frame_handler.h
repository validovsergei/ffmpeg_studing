#ifndef HANDLER_H
#define HANDLER_H


#include "gray_histogramm.h"
#include "bgr_histogramm.h"
#include "../decoder/decode_ffmpeg.h"



class Frame_Handler
{
    public:
        Frame_Handler(AVFrame * frame);
        static cv::Mat AVFrametoCvMat(AVFrame * frame);
        void show_image();
        void show_histogramms(int h = 400, int w = 512);
        cv::Mat * get_image(){return &_src_image;}
    private:
        cv::Mat _src_image; 
};

#endif