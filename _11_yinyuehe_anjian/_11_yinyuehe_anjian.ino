#include "audio.h"//控制audio模块文件
#include "key.h"//检测按键按下文件
#include <SoftwareSerial.h>

int music1_Pin = 4;
int music2_Pin = 6;//按键控制引脚定义

boolean play_pause;
boolean play_change;//定义boolean型变量

int music_vol = 25; //初始音量0~30

void setup() {
  // 初始化串口：
  Serial.begin(9600);//初始化串口通信，并将波特率设为9600
  pinMode(music1_Pin, INPUT);
  pinMode(music2_Pin, INPUT);/*pinMode(pin,mode)用以配置引脚为输出或输出模式，它是一个无返回值函数，函数有两个参数pin和mode，pin参数表示所要配置的引脚，mode参数表示设置的模式—INPUT（输入）或OUTPUT（输出）。*/

  key_init();

  audio_pause();

  audio_init(DEVICE_Flash, MODE_loopOne, music_vol); //初始化mp3模块
}

void loop()//根据按键按下情况发送串口指令控制Audio播放、暂停、切歌
 {
  if (key_get(music1_Pin, 0))
  {
    delay(200);//程序执行延时200ms
    play_pause = !play_pause;//若true则false，若false则true
  }
  if (play_change != play_pause)//如果两变量真值不同
  {
    play_change = play_pause;
    if (play_pause)//如果播放暂停为true
      audio_play();//音乐播放
    else//如果播放暂停为false
      audio_pause();//音乐暂停
  }
  if (key_get(music2_Pin, 0))
audio_down();//音乐停止
}



