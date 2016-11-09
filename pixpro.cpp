#include<iostream>
#include<string>
#include<time.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>


//g++ pixpro.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`
using namespace std ;
using namespace cv ;

int main()
{
  //http://172.16.0.254:9176/     pixpro
  //http://192.168.3.104:8080/    gopro
  VideoCapture cap("http://192.168.3.104:8080/") ;

  time_t timer ;
  struct tm *t_st ;
  /* 現在時刻の取得 */
  
  namedWindow("pixpro") ;
  
  while(1){

    Mat frame ;
    cap >> frame ;
             
    imshow("pixpro",frame) ;
    

    int key = cv::waitKey(2) ;

    if(key == 27){//escボタンが押されたとき
      break;//whileループから抜ける．
    }
    else if(key == 115){//sが押されたとき
      
      time(&timer) ;
      t_st = localtime(&timer) ;
      
      string date =  to_string(t_st->tm_year + 1900) + '_' + 
        to_string(t_st->tm_mon + 1) + '_' + to_string(t_st->tm_mday) + '_'  +
        to_string(t_st->tm_hour) + '_' + to_string(t_st->tm_min) + '_' + 
        to_string(t_st->tm_sec) ;
      
      string jpg = ".jpg" ;
      
      string filename = date + jpg ;
      
      //フレーム画像を保存する
      imwrite(filename, frame) ;
    }
    
  }
  
  return 0 ;
}
