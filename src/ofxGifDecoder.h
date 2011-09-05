//
//  ofxGifDecoder.h
//  gifPhasing
//
//  Created by Jesus Gollonet on 5/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofMain.h"
#include "FreeImage.h"

// give it an animated gif and get a frame
class ofxGifDecoder {
public:
    ofxGifDecoder();
    void decode(string fileName);
    
    
    vector<ofPixels *> pxs;    
    vector <ofColor> palette;
private :
    void reset();
    void putBmpIntoPixels(FIBITMAP * bmp, ofPixels &pix, bool swapForLittleEndian = true);
    void postBmpInfo(FIBITMAP * bmp);

    int globalPaletteSize;
    RGBQUAD * globalPalette;
    

};