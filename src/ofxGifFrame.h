//
//  ofxGifFrame.h
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofMain.h"

class ofxGifFrame
{
public:
    ofxGifFrame();

    // eventually localPalette, interlaced, disposal method
    // for user
    void setFromPixels(const ofPixels &px, int left, int top, float duration = 0.f);

    // for ofxGifFile
    void setFromGifPixels(const ofPixels &constructedPx, const ofPixels &rawPx, int left, int top, float duration = 0.f);
    void draw(float x, float y) const;
    void draw(float x, float y, int w, int h) const;

    ofPixels *getRawPixels();
    int getWidth() const;
    int getHeight() const;
    int getLeft() const;
    int getTop() const;

private:
    int m_Top, m_Left;
    ofPixels m_Pixels, m_RawPixels;
    ofTexture m_Texture;
    // optional
    float m_Duration;

    // optional
    std::vector<ofColor> m_Palette;
};
