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


void ofxGifFrame::setFromPixels(ofPixels _px, int _left , int _top){
    printf("px w %i, h %i, left %i, top %i \n", _px.getWidth(), _px.getWidth(), _left, _top);
    pixels  = _px;
    top     = _top;
    left    = _left;
    
    tx.allocate(pixels.getWidth(), pixels.getHeight(), GL_RGB); // rgb for now
    tx.loadData(pixels);
}

void ofxGifFrame::draw(float _x, float _y){
    tx.draw(_x, _y);
}