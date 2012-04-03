//
//  ofxGifFile.h
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGifFrame.h"

// todo. add loop to setup

class ofxGifFile {
    public:
    
        ofxGifFile();
        ~ofxGifFile();
        void setup(int _w, int _h, vector<ofColor> _globalPalette, int _nPages);
        void setBackgroundColor(ofColor _c);
        ofColor getBackgroundColor();
        void addFrame(ofPixels _px, int _left , int _top, float _duration = 0);
        vector <ofColor> getPalette();
        // void numFrames, void isAnimated, void duration
        int getNumFrames();
        int getWidth();
        int getHeight();
        float getDuration();
		 
    
        ofxGifFrame * getFrameAt(int _index);
    // array operator overload? 
    // gif[1] is frame 1, and we can treat is as such
    // gif[1].getTop(); gif[1].draw() ...    

        // void update
        void draw(float _x, float _y);  
        // this should draw with the offsets correctly applied. 
        void drawFrame(int _frameNum, float _x, float _y); 
        void drawFrame(int _frameNum, float _x, float _y, int _w, int _h); 
        void clear();
        
    private:
        ofColor bgColor;
        vector <ofxGifFrame > gifFrames;
        vector <ofImage> rawFrames;
        vector <ofColor> globalPalette;
        //vector <ofPixels *> rawPixels;
        int w, h, nPages;
        bool bAnimated;    
        bool bLoop;
        float duration;
        ofPixels accumPx;
    	float gifDuration;
};