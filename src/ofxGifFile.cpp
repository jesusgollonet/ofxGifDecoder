//
//  ofxGifFile.cpp
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifFile.h"



ofxGifFile::ofxGifFile(){
    w = h = 0;
}

ofxGifFile::~ofxGifFile(){}

void ofxGifFile::setup(int _w, int _h, vector<ofColor> _globalPalette, int _nPages){
    w               = _w;
    h               = _h;
    globalPalette   = _globalPalette;
    nPages          = _nPages;
}

// by now we're copying everything (no pointers)
void ofxGifFile::addFrame(ofPixels _px, int _left, int _top, float _duration){
    ofxGifFrame f;
    f.setFromPixels(_px, _top, _left, _duration);
    gifFrames.push_back(f);
}

void ofxGifFile::draw(float _x, float _y){
    gifFrames[0].draw(_x, _y);
}

void ofxGifFile::drawFrame(int _frameNum, float _x, float _y){
    if(_frameNum < 0 || _frameNum >= gifFrames.size()){
        ofLog(OF_LOG_WARNING, "ofxGifFile::drawFrame frame out of bounds. not drawing");
        return;
    }
    gifFrames[_frameNum].draw(_x, _y);
}




int ofxGifFile::getNumFrames() {
    return gifFrames.size();
}

ofxGifFrame * ofxGifFile::getFrameAt(int _index) {
    return &(gifFrames[_index]); //??
}


vector <ofColor> ofxGifFile::getPalette(){
    return globalPalette;
}
