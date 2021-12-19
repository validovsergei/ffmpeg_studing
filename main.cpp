 #include <opencv2/highgui.hpp>
 #include <opencv2/imgproc.hpp>
 #include <vector>
 #include <iostream>
 #include <utility>
 #include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
 
 extern "C"
 {
    #include "libavutil/adler32.h"
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/imgutils.h"
    #include "libswscale/swscale.h"
    #include "libavutil/timestamp.h"
 }

 cv::Mat AVFrametoCvMat(AVFrame * frame)
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
    std::cout << "convetion passed\n";
    return image;
 }


  void multiplication(int n, void * im)
{
      cv::Mat * image = static_cast<cv::Mat*>(im);
      cv::Mat new_image = cv::Mat::zeros(image->size(), image->type());
      for( int y = 0; y < image->rows; y++ ) 
      {
            for( int x = 0; x < image->cols; x++ ) 
            {
                  for( int c = 0; c < image->channels(); c++ ) 
                  {
                        new_image.at<cv::Vec3b>(y,x)[c] =
                        cv::saturate_cast<uchar>( image->at<cv::Vec3b>(y,x)[c] * n);
                  }
            }
      }
      cv::imshow("Change image brighntness", new_image);
}

void additional(int n, void * im)
{
      cv::Mat * image = static_cast<cv::Mat*>(im);
      cv::Mat  new_image = cv::Mat::zeros( image->size(), image->type());
      for( int y = 0; y < image->rows; y++ ) 
      {
            for( int x = 0; x < image->cols; x++ ) 
            {
                  for( int c = 0; c < image->channels(); c++ ) 
                  {
                        new_image.at<cv::Vec3b>(y,x)[c] =
                        cv::saturate_cast<uchar>( image->at<cv::Vec3b>(y,x)[c] + n);
                  }
            }
      }
      cv::imshow("Change image brighntness", new_image);
}

void Calculation_hist(const cv::Mat* images, cv::Mat& hist, int hist_w, int hist_h, cv::Mat& hist_image)
{
      int histSize = 256;
      float range[] = {0,256};
      const float * histRange[] = {range};
      cv::calcHist(images, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, true, false );
      cv::normalize(hist, hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
}

void draw_hist(const std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>>&  windowhist, int hist_h, int hist_w)
{
      int histSize = 256;
      int bin_w = cvRound( (double) hist_w/histSize );
      for( int i = 1; i < histSize; i++ )
      {
            for(auto whc = windowhist.begin(); whc != windowhist.end(); ++whc)
            {
                  cv::line(whc->first, cv::Point(bin_w*(i-1), hist_h - cvRound(whc->second.first.at<float>(i-1)) ),
                  cv::Point(bin_w * (i), hist_h - cvRound(whc->second.first.at<float>(i)) ),
                  whc->second.second, 2, 8, 0 );
            }
      }
}
 /* 
 int main(int argc, char *argv[])
 {
     AVFormatContext *pFormatContext = avformat_alloc_context();
     avformat_open_input(&pFormatContext, argv[0], NULL, NULL);
     printf("Format: %s, duration: %lld us", pFormatContext->iformat->long_name, pFormatContext->duration);
     avformat_find_stream_info(pFormatContext, NULL);
     AVCodec * pCodec = nullptr;
     AVCodecParameters * pCodecParameters = nullptr;
     for(auto i = 0; i < pFormatContext->nb_streams; ++i)
     {
         AVCodecParameters *plocalCodecParameters = pFormatContext->streams[i]->codecpar;
         AVCodec *plocalCodec = avcodec_find_decoder(plocalCodecParameters->codec_id);
         pCodec = plocalCodec;
         pCodecParameters = plocalCodecParameters;
         AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
         avcodec_parameters_to_context(pCodecContext, pCodecParameters);
         avcodec_open2(pCodecContext, pCodec, NULL);
         AVPacket *pPacket = av_packet_alloc();
         AVFrame *pFrame = av_frame_alloc();
         while(av_read_frame(pFormatContext, pPacket) > 0)
         {
             avcodec_send_packet(pCodecContext, pPacket);
             avcodec_receive_frame(pCodecContext, pFrame);
             
         }
     }
 }
*/




int main(int argc, char **argv)
{
     int regime;
      std::cout << "Input working regime 1 or 2 \n";
      std::cin >> regime;
      if(regime == 1)
      {
            std::string path;
            std::cout << "input path to video file:\n";
            std::cin >> path;
            cv::Mat src_image;
            AVFormatContext *pFormatContext = avformat_alloc_context();
            avformat_open_input(&pFormatContext, path.c_str(), NULL, NULL);
            std::cout << "Format: " << pFormatContext->iformat->long_name << ", duration: " << pFormatContext->duration << std::endl;
            avformat_find_stream_info(pFormatContext, NULL);
            int video_stream = av_find_best_stream(pFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
            AVCodecParameters * pCodecParameters = pFormatContext->streams[video_stream]->codecpar;
            AVCodec * pCodec = avcodec_find_decoder(pCodecParameters->codec_id);
            AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
            avcodec_parameters_to_context(pCodecContext, pCodecParameters);
            avcodec_open2(pCodecContext, pCodec, NULL);
            AVPacket *pPacket = av_packet_alloc();
            AVFrame *pFrame = av_frame_alloc();
            int result = 0;
            int i = 0;
            while(result >= 0)
            {
                  result = av_read_frame(pFormatContext, pPacket);
                  if (result >= 0 && pPacket->stream_index != video_stream) {
                        av_packet_unref(pPacket);
                        continue;
                  }
            
                  if (result < 0)
                        result = avcodec_send_packet(pCodecContext, NULL);
                  else {
                        if (pPacket->pts == AV_NOPTS_VALUE)
                        pPacket->pts = pPacket->dts = i;
                        result = avcodec_send_packet(pCodecContext, pPacket);
                  }
                  av_packet_unref(pPacket);
                  if (result < 0) {
                        av_log(NULL, AV_LOG_ERROR, "Error submitting a packet for decoding\n");
                        return result;
                  }
                  while (result >= 0) {
                        result = avcodec_receive_frame(pCodecContext, pFrame);
                        if (result == AVERROR_EOF)
                              goto finish;
                        else if (result == AVERROR(EAGAIN)) {
                              result = 0;
                              break;
                        } 
                        else if (result < 0) {
                              av_log(NULL, AV_LOG_ERROR, "Error decoding frame\n");
                              return result;
                        }
                  cv::Mat src_image = AVFrametoCvMat(pFrame);
                  std::vector<cv::Mat> bgr;
                  cv::split(src_image, bgr);
                  cv::Mat b_hist;
                  cv::Mat g_hist;
                  cv::Mat r_hist;
                  cv::Mat gray_hist;
                  cv::Mat src_gray;
                  cv::cvtColor(src_image, src_gray, cv::COLOR_BGR2GRAY);
                  int hist_w = 512, hist_h = 400;
                  cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0));
                  cv::Mat histGrayImage(hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0));
                  Calculation_hist(&src_gray, gray_hist, hist_w, hist_h, histGrayImage);
                  Calculation_hist(&bgr[0], b_hist, hist_w, hist_h, histImage);
                  Calculation_hist(&bgr[1], g_hist, hist_w, hist_h, histImage);
                  Calculation_hist(&bgr[2], r_hist, hist_w, hist_h, histImage);
                  std::vector<std::pair<cv::Mat, std::pair<cv::Mat, cv::Scalar>>> winhist;
                  winhist.push_back(std::make_pair(histImage, std::make_pair(b_hist, cv::Scalar(255, 0, 0))));
                  winhist.push_back(std::make_pair(histImage, std::make_pair(g_hist, cv::Scalar( 0, 255, 0))));
                  winhist.push_back(std::make_pair(histImage, std::make_pair(r_hist, cv::Scalar( 0, 0, 255))));
                  winhist.push_back(std::make_pair(histGrayImage, std::make_pair(gray_hist, cv::Scalar(255, 255, 255))));
                  draw_hist(winhist, hist_h, hist_w);
                  cv::imshow("Source image", src_image);
                  cv::imshow("Histogramm for processed image", histImage);
                  cv::imshow("Gray Histogram for processed image", histGrayImage);
                  cv::waitKey(1000);
            }
            i++;
      }
     finish:
     av_packet_free(&pPacket);
     av_frame_free(&pFrame);
     avformat_close_input(&pFormatContext);
     avcodec_free_context(&pCodecContext);
     return 0;
      }
      else if (regime == 2)
      {
            std::string path;
            std::cout << "Input path to picture file\n";
            std::cin >> path;
            cv::Mat src_image = cv::imread(path);
            cv::namedWindow("Change image brighntness", cv::WINDOW_AUTOSIZE);
            int st_pos = 1;
            cv::createTrackbar("Multiplication coefficient", "Change image brighntness", &st_pos, 10, multiplication, &src_image);
            cv::createTrackbar("Addition coefficient", "Change image brighntness", 0, 255, additional, &src_image);
            cv::imshow("Change image brighntness", src_image);
            cv::waitKey();
      }
       else
      {return 0;}
}