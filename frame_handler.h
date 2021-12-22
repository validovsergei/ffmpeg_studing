#ifndef HANDLER_H
#define HANDLER_H


#include "histogramm.h"
#include "decode_ffmpeg.h"



class Frame_Handler
{
    public:
        Frame_Handler(AVFrame * frame);
        static cv::Mat AVFrametoCvMat(AVFrame * frame);
        void show_image();
        void show_histogramms();
        cv::Mat * get_image(){return &_src_image;}
    private:
        cv::Mat _src_image; 
};

#endif