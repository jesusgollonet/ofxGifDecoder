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

    // eventually localPalette, interlaced, disposal method
    // for user
    void setFromPixels(ofPixels _px , int _left , int _top, float _duration = 0.f);
    // for ofxGifFile 
    void setFromGifPixels(ofPixels _constructedPx, ofPixels _rawPx , int _left , int _top, float _duration = 0.f);
    void draw(float _x, float _y);
    void draw(float _x, float _y, int _w, int _h);
    ofPixels * 	getRawPixels();
    int getWidth();
    int getHeight();
    int getLeft();
    int getTop();
    
private:
    int top;
    int left;
    ofPixels pixels;
    ofPixels rawPixels;
    ofTexture tx;
    // optional
    float duration;
    // optional
    vector<ofColor> palette;

};
