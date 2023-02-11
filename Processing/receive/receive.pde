// https://sojamo.de/libraries/oscP5/reference/index.html
import oscP5.*;
import netP5.*;

OscP5 oscP5;

final int PORTINCOMMING = 12000;
float posX = 0, posY = 0;

void setup() {
  size(400,400);
  frameRate(25);
  
  oscP5 = new OscP5(this, PORTINCOMMING);
}

void draw() {
  background(0);  
  circle(posX, posY, 30);
}

void oscEvent(OscMessage theOscMessage) {
  
  if(theOscMessage.checkAddrPattern("/position/x")==true) {
    if(theOscMessage.checkTypetag("f")) {
      float value = theOscMessage.get(0).floatValue();  
      posX = value * width;
    }  
  } else if(theOscMessage.checkAddrPattern("/position/y")==true) {
    if(theOscMessage.checkTypetag("f")) {
      float value = theOscMessage.get(0).floatValue();
      posY = value * height;
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
