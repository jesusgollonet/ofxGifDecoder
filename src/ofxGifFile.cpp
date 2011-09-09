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
    if(getNumFrames() == 0){
        accumPx = _px; // we assume 1st frame is fully drawn
    } else {
        // add new pixels to accumPx
        int cropOriginX = _left;
        int cropOriginY = _top;
        
        for (int i = 0; i < _px.getWidth() * _px.getHeight(); i++) {
            int x = i % accumPx.getWidth();
            int y = i / accumPx.getWidth();
            ofColor pxColor = accumPx.getColor(x, y);

            if (x >= _left  && x < _left + _px.getWidth()  &&
                y >= _top   && y < _top  + _px.getHeight()){
                int cropX = x - cropOriginX;  //   (i - _left) % _px.getWidth();
                int cropY = y - cropOriginY;
                int cropI = cropX + cropY * _px.getWidth();
                if (_px.getColor(cropX, cropY) != bgColor) {
                    accumPx.setColor(x, y, _px.getColor(cropX, cropY));
                }

 //               accumPx.getPixels()[i * 3    ] = _px.getPixels()[cropI * 3    ];
   //             accumPx.getPixels()[i * 3 + 1] = _px.getPixels()[cropI * 3 + 1];
     //           accumPx.getPixels()[i * 3 + 2] = _px.getPixels()[cropI * 3 + 2];
            } else {
                
                
            }
        }
    }
    
    
    f.setFromPixels(accumPx , _top, _left, _duration);
    gifFrames.push_back(f);
}

int ofxGifFile::getWidth(){
    return w;
}

int ofxGifFile::getHeight(){
    return h;
}

void ofxGifFile::draw(float _x, float _y){
    gifFrames[0].draw(_x, _y);
}

void ofxGifFile::drawFrame(int _frameNum, float _x, float _y){
    drawFrame(_frameNum, _x, _y, w, h);
}

void ofxGifFile::drawFrame(int _frameNum, float _x, float _y, int _w, int _h){
    if(_frameNum < 0 || _frameNum >= gifFrames.size()){
        ofLog(OF_LOG_WARNING, "ofxGifFile::drawFrame frame out of bounds. not drawing");
        return;
    }
    ofxGifFrame  f = gifFrames[_frameNum];
    f.draw(_x , _y , _w, _h);
}


void ofxGifFile::setBackgroundColor(ofColor _c) {
    bgColor = _c;
}

ofColor ofxGifFile::getBackgroundColor() {
    return bgColor;
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

void ofxGifFile::clear() {
    
    printf("clearing gif file\n ");
    gifFrames.clear();
    globalPalette.clear();
}
