//
//  ofxGifFile.h
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofxGifFrame.h"
#include "ofColor.h"

enum GifFrameDisposal {
    GIF_DISPOSAL_UNSPECIFIED,
    GIF_DISPOSAL_LEAVE,
    GIF_DISPOSAL_BACKGROUND,
    GIF_DISPOSAL_PREVIOUS
};

// todo. add loop to setup

class ofxGifFile
{
public:
    ofxGifFile();
    ~ofxGifFile();

    void setup(int width, int height, const std::vector<ofColor> &globalPalette, int pageCount);

    void setBackgroundColor(ofColor color);
    ofColor getBackgroundColor() const;

    void addFrame(ofPixels &pixels, const int &left , const int &top, const unsigned int &channels, GifFrameDisposal disposal = GIF_DISPOSAL_PREVIOUS, float duration = 0);
    const std::vector<ofColor> &getPalette() const;

    size_t getNumFrames() const;
    int getWidth() const;
    int getHeight() const;
    float getDuration() const;

    ofxGifFrame *getFrameAt(int index);

    void draw(float x, float y);

    // This should draw with the offsets correctly applied.
    void drawFrame(const int &frameNum, const float &x, const float &y);
    void drawFrame(const int &frameNum, const float &x, const float &y, const int &w, const int &h);
    void clear();

    bool isValid() const;

private:
    ofColor m_BgColor;
    int m_Width,
        m_Height,
        m_PageCount;

    bool m_IsAnimated, m_IsLoop;
    float m_Duration;
    ofPixels m_AccumPixel;
    float m_GifDuration;

    std::vector<ofxGifFrame> m_GifFrames;
    std::vector<ofColor> m_GlobalPalette;
};
