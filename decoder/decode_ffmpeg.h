#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <iostream>

 extern "C" {
    #include "libavutil/adler32.h"
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/imgutils.h"
    #include "libswscale/swscale.h"
    #include "libavutil/timestamp.h"
 }

 

 class Decoder {
     public:
        Decoder();
        ~Decoder();
        int get_video_codec(const std::string& pathToVideo);
        int get_packet(int video_stream, int result = 0, int i = 0);
        int prepare_frame();
        AVFrame * get_frame() {return _pFrame;}

     private:
        AVFormatContext *_pFormatContext;
        AVCodecContext *_pCodecContext;
        AVPacket *_pPacket;
        AVFrame *_pFrame;

 };

 #endif