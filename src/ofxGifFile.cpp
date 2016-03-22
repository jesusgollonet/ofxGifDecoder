//
//  ofxGifFile.cpp
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifFile.h"

ofxGifFile::ofxGifFile()
    : m_BgColor(ofColor::white)
    , m_Width(0)
    , m_Height(0)
    , m_PageCount(0)
    , m_IsAnimated(false)
    , m_IsLoop(false)
    , m_Duration(0.f)
    , m_AccumPixel()
    , m_GifDuration(0.f)
{

}

ofxGifFile::~ofxGifFile()
{

}

void ofxGifFile::setup(int width, int height, const std::vector<ofColor> &globalPalette, int pageCount)
{
    m_Width = width;
    m_Height = height;
    m_GlobalPalette = globalPalette;
    m_PageCount = pageCount;
}

// by now we're copying everything (no pointers)
void ofxGifFile::addFrame(ofPixels pixels, const int &left, const int &top, GifFrameDisposal disposal, float duration)
{
    ofxGifFrame frame;

    if (getNumFrames() == 0) {
        m_AccumPixel = pixels; // we assume 1st frame is fully drawn
        frame.setFromPixels(pixels , left, top, duration);
        m_GifDuration = duration;
    }
    else {
        // add new pixels to accumPx
        const int cropOriginX = left;
        const int cropOriginY = top;

        // [todo] make this loop only travel through _px, not accumPx
        for (int i = 0; i < m_AccumPixel.getWidth() * m_AccumPixel.getHeight(); i++) {
            const int x = i % m_AccumPixel.getWidth();
            const int y = i / m_AccumPixel.getWidth();

            if (x >= left  && x < left + pixels.getWidth()  && y >= top   && y < top  + pixels.getHeight()) {
                const int cropX = x - cropOriginX;  //   (i - _left) % _px.getWidth();
                const int cropY = y - cropOriginY;

                //int cropI = cropX + cropY * _px.getWidth();
                if (pixels.getColor(cropX, cropY).a == 0) {
                    switch (disposal) {
                    case GIF_DISPOSAL_BACKGROUND:
                        pixels.setColor(x, y, m_BgColor);
                        break;
                    case GIF_DISPOSAL_LEAVE:
                    case GIF_DISPOSAL_UNSPECIFIED:
                        pixels.setColor(x, y, m_AccumPixel.getColor(cropX, cropY));
//                            accumPx.setColor(x,y,_px.getColor(cropX, cropY));
                        break;
                    case GIF_DISPOSAL_PREVIOUS:
                        pixels.setColor(x, y, m_AccumPixel.getColor(cropX, cropY));
                        break;
                    }
                }
                else {
                    m_AccumPixel.setColor(x, y, pixels.getColor(cropX, cropY));
                }
            }
            else {
                if (pixels.getColor(x, y) == m_BgColor) {
                    switch (disposal) {
                    case GIF_DISPOSAL_BACKGROUND:
                        m_AccumPixel.setColor(x, y, m_BgColor);
                        break;
                    case GIF_DISPOSAL_UNSPECIFIED:
                    case GIF_DISPOSAL_LEAVE:
                        m_AccumPixel.setColor(x, y, pixels.getColor(x, y));
                        break;
                    case GIF_DISPOSAL_PREVIOUS:
                        pixels.setColor(x, y, m_AccumPixel.getColor(x, y));
                        break;
                    }
                }
                else {
                    m_AccumPixel.setColor(x, y, pixels.getColor(x, y));
                }
            }
        }

        frame.setFromPixels(pixels, left, top, duration);
    }

    m_AccumPixel = pixels;
    m_GifFrames.push_back(frame);
}

int ofxGifFile::getWidth() const
{
    return m_Width;
}

int ofxGifFile::getHeight() const
{
    return m_Height;
}

float ofxGifFile::getDuration() const
{
    return m_GifDuration;
}

void ofxGifFile::draw(float x, float y)
{
    m_GifFrames.at(0).draw(x, y);
}

void ofxGifFile::drawFrame(const int &frameNum, const float &x, const float &y)
{
    if (frameNum < 0 || frameNum >= m_GifFrames.size()) {
        ofLogWarning("ofxGifFile") << __FUNCTION__ << "Frame out of bounds. not drawing";
        return;
    }

    m_GifFrames.at(frameNum).draw(x , y , m_GifFrames.at(frameNum).getWidth(), m_GifFrames.at(frameNum).getHeight());
}

void ofxGifFile::drawFrame(const int &frameNum, const float &x, const float &y, const int &w, const int &h)
{
    if (frameNum < 0 || frameNum >= m_GifFrames.size()) {
        ofLogWarning("ofxGifFile") << __FUNCTION__ << "Frame out of bounds. not drawing";
        return;
    }

    m_GifFrames.at(frameNum).draw(x , y , w, h);
}


void ofxGifFile::setBackgroundColor(ofColor color)
{
    m_BgColor = color;
}

ofColor ofxGifFile::getBackgroundColor() const
{
    return m_BgColor;
}

int ofxGifFile::getNumFrames() const
{
    return m_GifFrames.size();
}

ofxGifFrame *ofxGifFile::getFrameAt(int index)
{
    return &m_GifFrames.at(index);
}

std::vector<ofColor> ofxGifFile::getPalette() const
{
    return m_GlobalPalette;
}

void ofxGifFile::clear()
{
    m_GifFrames.clear();
    m_GlobalPalette.clear();
}

bool ofxGifFile::isValid() const
{
    return m_GifFrames.size() > 0;
}
