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
    // eventually localPalette, interlaced, disposal method
    void setFromPixels(ofPixels px , int _left , int _top, float _duration = 0.f);
    void draw(float _x, float _y);
    void draw(float _x, float _y, int _w, int _h);
    int getWidth();
    int getHeight();
    int getLeft();
    int getTop();
    
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
