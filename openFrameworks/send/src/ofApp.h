//https://r-dimension.xsrv.jp/classes_j/ofxosc/
#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

#define REMOTE_IP "127.0.0.1"  //送信先のiOSデバイスのIPアドレス
#define PORT_OUTGOING 12000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
        void sendMousePos(int x, int y);
        void sendMousePressed(bool _isPressed);
		
        ofxOscSender sender;
        int cX, cY;
        bool isPressed;
};
