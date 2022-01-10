#include "decode_ffmpeg.h"

Decoder::Decoder() {
    _pFormatContext = avformat_alloc_context();
    _pPacket = av_packet_alloc();
    _pFrame = av_frame_alloc();
    _pCodecContext = nullptr;
}

Decoder::~Decoder() {
    av_packet_free(&_pPacket);
    av_frame_free(&_pFrame);
    avformat_close_input(&_pFormatContext);
    avcodec_free_context(&_pCodecContext);
}

int Decoder::get_video_codec(const std::string &pathToVideo) {
    int videoStream;

    if (avformat_open_input(&_pFormatContext, pathToVideo.c_str(), NULL, NULL)) {
        return -1;
    }
    videoStream = av_find_best_stream(_pFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (videoStream < 0) {
        return -2;
    }
    AVCodecParameters *pCodecParameters = _pFormatContext->streams[videoStream]->codecpar;
    AVCodec *pCodec = avcodec_find_decoder(pCodecParameters->codec_id);
    if (!pCodec) {
        return -3;
    }
    _pCodecContext = avcodec_alloc_context3(pCodec);
    if (!_pCodecContext) {
        return -4;
    }
    if (avcodec_parameters_to_context(_pCodecContext, pCodecParameters) < 0) {
        return -5;
    }
    if (avcodec_open2(_pCodecContext, pCodec, NULL)) {
        return -6;
    }
    return videoStream;
}

int Decoder::get_packet(int videoStream, int result, int i) {
    result = av_read_frame(_pFormatContext, _pPacket);
    if (result >= 0 && _pPacket->stream_index != videoStream) {
        av_packet_unref(_pPacket);
        return -1;
    }

    if (result < 0) {
        result = avcodec_send_packet(_pCodecContext, NULL);
    }
    else {
        if (_pPacket->pts == AV_NOPTS_VALUE) {
            _pPacket->pts = _pPacket->dts = i;
        }
        result = avcodec_send_packet(_pCodecContext, _pPacket);
    }
    av_packet_unref(_pPacket);
    if (result < 0) {
        std::cout << "Error submitting a packet for decoding\n";
        return -2;
    }
    return result;
}

int Decoder::prepare_frame() {
    int result = avcodec_receive_frame(_pCodecContext, _pFrame);
    if (result == AVERROR_EOF) {
        return -1;
    }
    else if (result == AVERROR(EAGAIN)) {
        return -2;
    }
    else if (result < 0) {
        std::cout << "Error decoding frame\n";
        return -3;
    }
    return result;
}
