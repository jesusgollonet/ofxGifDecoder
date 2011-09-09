#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
        void keyPressed  (int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void exit();
    
        ofxGifDecoder dcd1;
        ofxGifDecoder dcd2;
        ofxGifDecoder dcd3;
        ofxGifFile  gif1;
        ofxGifFile  gif2;
        ofxGifFile  gif3;
 
};

#endif
