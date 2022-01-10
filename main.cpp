#include "utils/frame_handler.h"

#include <iostream>
 
#include "decoder/decode_ffmpeg.h"

void multiplication(int n, void * im) {
      cv::Mat * image = static_cast<cv::Mat*>(im);
      cv::Mat newImage = cv::Mat::zeros(image->size(), image->type());
      for( int y = 0; y < image->rows; y++ ) 
      {
            for( int x = 0; x < image->cols; x++ ) 
            {
                  for( int c = 0; c < image->channels(); c++ ) 
                  {
                        newImage.at<cv::Vec3b>(y,x)[c] =
                        cv::saturate_cast<uchar>( image->at<cv::Vec3b>(y,x)[c] * n);
                  }
            }
      }
      cv::imshow("Change image brighntness", newImage);
}

void additional(int n, void * im) {
      cv::Mat * image = static_cast<cv::Mat*>(im);
      cv::Mat  newImage = cv::Mat::zeros( image->size(), image->type());
      for( int y = 0; y < image->rows; y++ ) 
      {
            for( int x = 0; x < image->cols; x++ ) 
            {
                  for( int c = 0; c < image->channels(); c++ ) 
                  {
                        newImage.at<cv::Vec3b>(y,x)[c] =
                        cv::saturate_cast<uchar>( image->at<cv::Vec3b>(y,x)[c] + n);
                  }
            }
      }
      cv::imshow("Change image brighntness", newImage);
}


int main(int argc, char **argv) {
      int regime;
      std::cout << "Input working regime 1 or 2 \n";
      std::cin >> regime;
      if(regime == 1) {
            std::string path;
            std::cout << "input path to video file:\n";
            std::cin >> path;
            Decoder decodForHistogramm;
            int result = 0;
            int i = 0;
            int videoStream = decodForHistogramm.get_video_codec(path);
            if(videoStream < 0) {
                  std::cout << "Video codec havenot gotten.\n";
            }
            while(result >= 0) {
                  result = decodForHistogramm.get_packet(videoStream, i = i);
                  if(result == -1) {
                        result = 0;
                        continue;
                  }
                  else if(result == -2) {
                        return result;
                  }
                  while(result >= 0) {
                        result = decodForHistogramm.prepare_frame();
                        if(result == -1) {
                              return result;
                        }
                        else if(result == -2) {
                              result = 0;
                              break;
                        }
                        else if(result == -3) {
                              return result;
                        }
                        Frame_Handler handler(decodForHistogramm.get_frame());
                        handler.showImage();
                        handler.showHistogramms();
                  }
                  ++i;
            }
      }
      else if (regime == 2) {
            std::string path;
            std::cout << "Input path to picture file\n";
            std::cin >> path;
            cv::Mat srcImage = cv::imread(path);
            cv::namedWindow("Change image brighntness", cv::WINDOW_AUTOSIZE);
            int stPos = 1;
            cv::createTrackbar("Multiplication coefficient", "Change image brighntness", &stPos, 10, multiplication, &srcImage);
            cv::createTrackbar("Addition coefficient", "Change image brighntness", 0, 255, additional, &srcImage);
            cv::imshow("Change image brighntness", srcImage);
            cv::waitKey();
      }
       else {
             return 0;
      }
}