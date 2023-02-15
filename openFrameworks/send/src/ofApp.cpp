#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // ポートを開く
    sender.setup( REMOTE_IP, PORT_OUTGOING );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    if(isPressed)
        ofSetColor(255, 0, 0);
    else
        ofSetColor(255);
    
    ofDrawCircle(cX, cY, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    sendMousePos(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    sendMousePos(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofxOscMessage m;
    m.setAddress( "/mouse/isPressed" );
    m.addInt32Arg(1);
    sender.sendMessage(m);
    isPressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofxOscMessage m;
    m.setAddress( "/mouse/isPressed" );
    m.addInt32Arg(0);
    sender.sendMessage(m);
    isPressed = false;
}

void ofApp::sendMousePos(int x, int y ){
    ofxOscMessage mX;
    mX.setAddress( "/position/x" );
    mX.addFloatArg((float)x / (float)ofGetWidth());
    sender.sendMessage(mX);
    cX = x;
    
    ofxOscMessage mY;
    mY.setAddress( "/position/y" );
    mY.addFloatArg((float)y / (float)ofGetHeight());
    sender.sendMessage(mY);
    cY = y;
}

void ofApp::sendMousePressed(bool _isPressed){
    ofxOscMessage m;
    m.setAddress( "/mouse/isPressed" );
    m.addInt32Arg(isPressed ? 1 : 0);
    sender.sendMessage(m);
    isPressed = _isPressed;
}
