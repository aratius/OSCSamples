// https://sojamo.de/libraries/oscP5/reference/index.html
import oscP5.*;
import netP5.*;
  
OscP5 oscP5;  // OscP5のインスタンス
NetAddress myRemoteLocation;  // OSC送信時に使うリモート（送信先）の情報を含んだオブジェクト

final int PORTOUTGOING = 12000;
final int PORTINCOMMING = 12001;

void setup() {
  size(400,400);
  frameRate(25);

  oscP5 = new OscP5(this, PORTINCOMMING);  // OscP5のインスタンス作成
  
  myRemoteLocation = new NetAddress("127.0.0.1", PORTOUTGOING);  // リモート（送信先）のオブジェクトを作成
}

void draw() {
background(0);  
  sendMousePosition();
  if(mousePressed) fill(255, 0, 0);
  else fill(255, 255, 255);
  circle(mouseX, mouseY, 30);  // 自身の確認用にも円を描画
}

// マウス座標をリモートにOSCで送信
void sendMousePosition() {
  OscMessage posXMessage = new OscMessage("/position/x");  // OSCメッセージ（アドレス: "/position/x"）のためのOscMessageオブジェクトを作成
  posXMessage.add((float)mouseX / (float)width);  // 送る値をバインド
  oscP5.send(posXMessage, myRemoteLocation);  // 送信
  
  OscMessage posYMessage = new OscMessage("/position/y");  // OSCメッセージ（アドレス: "/position/y"）のためのOscMessageオブジェクトを作成
  posYMessage.add((float)mouseY / (float)height);  // 送る値をバインド
  oscP5.send(posYMessage, myRemoteLocation);  // 送信
}

// マウス押した時にOSC送信する
void mousePressed() {
  sendMouseStatus(true);
}

// マウス離した時にOSC送信する
void mouseReleased() {
  sendMouseStatus(false);
}

// マウスが押されているか、離されているかをOSCで送信（1: 押された, 0: 離された）
void sendMouseStatus(boolean isPressed) {
  OscMessage mousePressedMessage = new OscMessage("/mouse/isPressed");  // "/mouse/isPressed"のためのOscMessageオブジェクトを作成
  mousePressedMessage.add(isPressed ? 1 : 0);  // 送る値をバインド
  oscP5.send(mousePressedMessage, myRemoteLocation);  // 送信
}
