//
//  ofxGifDecoder.h
//  gifPhasing
//
//  Created by Jesus Gollonet on 5/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofMain.h"
#include "ofxGifFile.h"

#include "FreeImage.h"

// give it an animated gif and get a frame
class ofxGifDecoder {
public:
    ofxGifDecoder();
    bool decode(string fileName);
    ofxGifFile getFile();
    
    vector<ofPixels *> pxs;    
    vector <ofColor> palette;
    
private :
    
    ofxGifFile  gifFile;
    
    void reset();
    void createGifFile(FIBITMAP * bmp, int _nPages);
    void processFrame(FIBITMAP * bmp, int _frameNum);
    
    int globalPaletteSize;
    RGBQUAD * globalPalette;
    

};