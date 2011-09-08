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
    top      = _top;
    left     = _left;
    duration = _duration;
    
    tx.allocate(pixels.getWidth(), pixels.getHeight(), GL_RGB); // rgb for now
    tx.loadData(pixels);
}

void ofxGifFrame::draw(float _x, float _y){
    tx.draw(_x, _y);
}