// https://sojamo.de/libraries/oscP5/reference/index.html
import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

final int PORTOUTGOING = 12000;
final int PORTINCOMMING = 12001;

void setup() {
  size(400,400);
  frameRate(25);

  oscP5 = new OscP5(this, PORTINCOMMING);
  
  myRemoteLocation = new NetAddress("127.0.0.1", PORTOUTGOING);
}


void draw() {
background(0);  
  sendMousePosition();
  circle(mouseX, mouseY, 30);
}

void sendMousePosition() {
  OscMessage posXMessage = new OscMessage("/position/x");
  OscMessage posYMessage = new OscMessage("/position/y");
  
  posXMessage.add((float)mouseX / (float)width);
  posYMessage.add((float)mouseY / (float)height);

  oscP5.send(posXMessage, myRemoteLocation); 
  oscP5.send(posYMessage, myRemoteLocation); 
}


void oscEvent(OscMessage theOscMessage) {
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
}
