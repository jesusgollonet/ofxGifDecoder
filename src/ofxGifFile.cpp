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

void ofxGifFile::setup(int _w, int _h) {
    w = _w;
    h = _h;
}

