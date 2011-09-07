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
        void addFrame(ofPixels _px, int _left , int _top);
        vector <ofColor> getPalette();
        // void numFrames, void isAnimated, void duration
    
    private:
        vector <ofxGifFrame > gifFrames;
        vector <ofColor> globalPalette;
        //vector <ofPixels *> rawPixels;
        int w, h, nPages;
        bool bAnimated;    
        bool bLoop;
        float duration;
    
};