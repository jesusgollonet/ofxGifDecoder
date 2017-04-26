//
//  ofxGifFrame.h
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofTexture.h"
#include "ofColor.h"

class ofxGifFrame
{
public:
    ofxGifFrame();

    void setFromPixels(const ofPixels &px, int left, int top, const unsigned int &channels, float duration = 0.f);

    void draw(float x, float y) const;
    void draw(float x, float y, int w, int h) const;

    ofTexture *getTexture();
    int getWidth() const;
    int getHeight() const;
    int getLeft() const;
    int getTop() const;

private:
    int m_Top, m_Left;
    ofTexture m_Texture;
    float m_Duration;
    std::vector<ofColor> m_Palette;
};
