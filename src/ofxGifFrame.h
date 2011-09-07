//
//  ofxGifFrame.h
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once


#include "ofMain.h"

class ofxGifFrame{
    
public:
    ofxGifFrame();
    //ofxGifFrame(ofPixels px, int _top, int _left);
    // eventually localPalette, interlaced, disposal method, duration
    void setFromPixels(ofPixels px , int _left , int _top);
    void draw(float _x, float _y);
private:
    int top;
    int left;
    ofPixels pixels;
    ofTexture tx;
    // optional
    float duration;
    // optional
    vector<ofColor> palette;

};
