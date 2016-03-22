//
//  ofxGifFrame.cpp
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifFrame.h"

ofxGifFrame::ofxGifFrame()
    : m_Top(0)
    , m_Left(0)
    , m_Pixels()
    , m_RawPixels()
    , m_Texture()
    , m_Duration(0.f)
{

}

void ofxGifFrame::setFromPixels(const ofPixels &px, int left , int top, float duration)
{
    m_Pixels = px;
    m_Left = left;
    m_Top = top;
    m_Duration = duration;

    m_Texture.allocate(m_Pixels.getWidth(), m_Pixels.getHeight(), GL_RGB); // RGB for now
    m_Texture.loadData(m_Pixels);
}

void ofxGifFrame::setFromGifPixels(const ofPixels &constructedPx, const ofPixels &rawPx, int left, int top, float duration)
{
    m_Pixels = constructedPx;
    m_RawPixels = rawPx;
    m_Left = left;
    m_Top = top;
    m_Duration = duration;

    m_Texture.allocate(m_Pixels.getWidth(), m_Pixels.getHeight(), GL_RGB); // RGB for now
    m_Texture.loadData(m_Pixels);
}

ofPixels *ofxGifFrame::getRawPixels()
{
    if (m_RawPixels.getWidth() > 0 && m_RawPixels.getHeight() > 0) {
        return &m_RawPixels;
    }

    return &m_Pixels;
}

int ofxGifFrame::getWidth() const
{
    return m_Pixels.getWidth();
}

int ofxGifFrame::getHeight() const
{
    return m_Pixels.getHeight();
}

int ofxGifFrame::getLeft() const
{
    return m_Left;
}

int ofxGifFrame::getTop() const
{
    return m_Top;
}

void ofxGifFrame::draw(float x, float y) const
{
    draw(x, y, getWidth(), getHeight());
}

void ofxGifFrame::draw(float x, float y, int w, int h) const
{
    m_Texture.draw(x, y, w, h);
}
