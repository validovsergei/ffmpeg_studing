#include "decode_ffmpeg.h"


Decoder::Decoder()
{
    _pFormatContext = avformat_alloc_context();
    _pPacket = av_packet_alloc();
    _pFrame = av_frame_alloc();
    _pCodecContext = nullptr;
}


Decoder::~Decoder()
{
     av_packet_free(&_pPacket);
     av_frame_free(&_pFrame);
     avformat_close_input(&_pFormatContext);
     avcodec_free_context(&_pCodecContext);

}


int Decoder::get_video_codec(const std::string pathToVideo)
{
     int video_stream;

     avformat_open_input(&_pFormatContext, pathToVideo.c_str(), NULL, NULL);
     video_stream = av_find_best_stream(_pFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
     AVCodecParameters * pCodecParameters = _pFormatContext->streams[video_stream]->codecpar;
     AVCodec * pCodec = avcodec_find_decoder(pCodecParameters->codec_id);
     _pCodecContext = avcodec_alloc_context3(pCodec);
     avcodec_parameters_to_context(_pCodecContext, pCodecParameters);
     avcodec_open2(_pCodecContext, pCodec, NULL);
     return video_stream;
}


int Decoder::get_packet(int video_stream, int result, int i)
{
     result = av_read_frame(_pFormatContext, _pPacket);;

     if (result >= 0 && _pPacket->stream_index != video_stream) 
     {
         av_packet_unref(_pPacket);
         return -1;
     }
            
     if (result < 0)
         result = avcodec_send_packet(_pCodecContext, NULL);
     else 
     {
         if (_pPacket->pts == AV_NOPTS_VALUE)
             _pPacket->pts = _pPacket->dts = i;
         result = avcodec_send_packet(_pCodecContext, _pPacket);
     }
     av_packet_unref(_pPacket);
     if (result < 0) 
     {
         av_log(NULL, AV_LOG_ERROR, "Error submitting a packet for decoding\n");
         return -2;
     }
     return result;
}


int Decoder::receive_frame()
{
     int result = avcodec_receive_frame(_pCodecContext, _pFrame);
     if (result == AVERROR_EOF)
         return -1; 
     else if(result == AVERROR(EAGAIN))
         return -2;
     else if (result < 0) 
     {
         av_log(NULL, AV_LOG_ERROR, "Error decoding frame\n");
         return -3;
     }
     return result;
}
