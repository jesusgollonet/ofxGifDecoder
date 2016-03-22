//
//  ofxGifDecoder.h
//  gifPhasing
//
//  Created by Jesus Gollonet on 5/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofxGifFile.h"
#include "FreeImage.h"

// give it an animated gif and get a frame
class ofxGifDecoder
{
public:
    ofxGifDecoder();
    ~ofxGifDecoder();

    ofxGifFile decode(string fileName, bool isUseDataPath = false);

private :
    int m_GlobalPaletteSize;
    RGBQUAD *m_GlobalPalette;

    std::vector<ofColor> m_Palettes;

private:
    void reset();
    void createGifFile(FIBITMAP *bmp, const int &pageCount, ofxGifFile &gifFile);
    void processFrame(FIBITMAP *bmp, ofxGifFile &gifFile);
};
