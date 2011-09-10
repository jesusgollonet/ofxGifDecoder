//
//  ofxGifFrame.cpp
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifFrame.h"

ofxGifFrame::ofxGifFrame(){
    left = top = 0;
    duration = 0.f;
}


void ofxGifFrame::setFromPixels(ofPixels _px, int _left , int _top, float _duration){
    //rawPixels = _px;
    pixels    = _px;
    left      = _left;
    top       = _top;
    duration  = _duration;
    tx.allocate(pixels.getWidth(), pixels.getHeight(), GL_RGB); // rgb for now
    tx.loadData(pixels);
}

void ofxGifFrame::setFromGifPixels(ofPixels _constructedPx, ofPixels _rawPx , int _left , int _top, float _duration){
    pixels   = _constructedPx;
    rawPixels = _rawPx;
    left     = _left;
    top      = _top;
    duration = _duration;
    
    tx.allocate(pixels.getWidth(), pixels.getHeight(), GL_RGB); // rgb for now
    tx.loadData(pixels);
}

ofPixels * ofxGifFrame::getRawPixels(){
    if(rawPixels.getWidth() > 0 && rawPixels.getHeight() > 0) return &rawPixels;
    return &pixels;
}

int ofxGifFrame::getWidth(){
    return pixels.getWidth();
}

int ofxGifFrame::getHeight(){
    return pixels.getHeight();
}

int ofxGifFrame::getLeft(){
    return left;
}

int ofxGifFrame::getTop(){
    return top;
}

void ofxGifFrame::draw(float _x, float _y){
    draw(_x, _y, getWidth(), getHeight());
}

void ofxGifFrame::draw(float _x, float _y, int _w, int _h){
    tx.draw(_x, _y, _w, _h);
}
