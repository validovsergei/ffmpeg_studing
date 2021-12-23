#include "utils/frame_handler.h"
#include "decoder/decode_ffmpeg.h"
#include <iostream>
 


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
            Decoder decod_for_hist;
            int result = 0;
            int i = 0;
            int video_stream = decod_for_hist.get_video_codec(path);
            while(result >= 0)
            {
                  result = decod_for_hist.get_packet(video_stream, i = i);
                  if(result == -1)
                  {
                        result = 0;
                        continue;
                  }
                  else if(result == -2)
                        return result;
                  while(result >= 0)
                  {
                        result = decod_for_hist.receive_frame();
                        if(result == -1)
                              return result;
                        else if(result == -2)
                        {
                              result = 0;
                              break;
                        }
                        else if(result == -3)
                              return result;
                        Frame_Handler handler(decod_for_hist.get_frame());
                        handler.show_image();
                        handler.show_histogramms();
                  }
                  ++i;
            }
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