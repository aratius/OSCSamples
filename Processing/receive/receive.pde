// https://sojamo.de/libraries/oscP5/reference/index.html
import oscP5.*;
import netP5.*;

OscP5 oscP5;  // OscP5のインスタンス

final int PORTINCOMMING = 12000;  // 受信ポート
float posX = 0, posY = 0;                 // 円を表示する座標
boolean isPressed = false;                // 送信元でマウスが押されているかの判別

void setup() {
  size(400,400);
  frameRate(25);
  
  oscP5 = new OscP5(this, PORTINCOMMING);  // OscP5のインスタンス作成
}

void draw() {
  background(0);  
  if(isPressed) fill(255, 0, 0);
  else fill(255, 255, 255);
  circle(posX, posY, 30);  // 円描画
}

// OSCを受け取った時に実行される関数
void oscEvent(OscMessage theOscMessage) {
  
  if(theOscMessage.checkAddrPattern("/position/x")==true) {            // OSCアドレスが"/position/x"の時
      if(theOscMessage.checkTypetag("f")) {                                        // floatの単体引数の時
      float value = theOscMessage.get(0).floatValue();                        // 1個目の引数（float）を受け取る  
      posX = value * width;                                                              // posXの値を更新, valueの値の幅は0-1なので、画面幅にマッピング
    }  
  } else if(theOscMessage.checkAddrPattern("/position/y")==true) {  // OSCアドレスが"/position/y"の時
    if(theOscMessage.checkTypetag("f")) {                                        // floatの単体引数の時
      float value = theOscMessage.get(0).floatValue();                       // 1個目の引数（float）を受け取る
      posY = value * height;                                                            // posYの値を更新, valueの値の幅は0-1なので、画面幅にマッピング
    }
  } else if(theOscMessage.checkAddrPattern("/mouse/isPressed")==true) {  // OSCアドレスが"/mouse/isPressed"の時
    if(theOscMessage.checkTypetag("i")) {                                        // intの単体引数の時
      int value = theOscMessage.get(0).intValue();                       // 1個目の引数（float）を受け取る
      isPressed = value == 1;                                                            // posYの値を更新, valueの値の幅は0-1なので、画面幅にマッピング
    } else if(theOscMessage.checkTypetag("f")) {                                        // intの単体引数の時
      float value = theOscMessage.get(0).floatValue();                       // 1個目の引数（float）を受け取る
      isPressed = value == 1;                                                            // posYの値を更新, valueの値の幅は0-1なので、画面幅にマッピング
    }    
  }
  
  // 例1）
  // 複数の引数を受け取る
  if(theOscMessage.checkAddrPattern("/somedata")==true) {
    if(theOscMessage.checkTypetag("fis")) {  // float, int, string
        float value1 = theOscMessage.get(0).floatValue();  
        int value2 = theOscMessage.get(1).intValue();  
        String value3 = theOscMessage.get(2).stringValue();
        // 何らかの処理      
    }
  }
  
  println("### received an osc message. with address pattern "+theOscMessage.addrPattern()+", with typetag "+theOscMessage.typetag());
}
