#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // 設定されたポートを設定
    cout << "listening for osc messages on port " << PORT_INCOMMING << "\n";
    receiver.setup( PORT_INCOMMING );

    //変数の初期化
    cX = 0;
    cY = 0;
    isPressed = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    //senderからメッセージが送られてくるまで待機
    while( receiver.hasWaitingMessages() ){
        // 次のメッセージを取得
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // マウスが動いたかをチェック
        if( m.getAddress() == "/position/x" ){
            // both the arguments are int32's
            cX = m.getArgAsFloat(0) * ofGetWidth();;
        } else if(m.getAddress() == "/position/y") {
            cY = m.getArgAsFloat(0) * ofGetHeight();
        } else if(m.getAddress() == "/mouse/isPressed") {
            isPressed = m.getArgAsInt(0) == 1;
        }
        
    }
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

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
