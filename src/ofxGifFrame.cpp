//
//  ofxGifFrame.cpp
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifFrame.h"

ofxGifFrame::ofxGifFrame(){

}


void ofxGifFrame::setFromPixels(ofPixels _px, int _left , int _top, float _duration){
    pixels   = _px;
    left     = _left;
    top      = _top;
    duration = _duration;
    
    tx.allocate(pixels.getWidth(), pixels.getHeight(), GL_RGB); // rgb for now
    tx.loadData(pixels);
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
