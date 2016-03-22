//
//  ofxGifFrame.cpp
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifFrame.h"
#include "ofMain.h"

ofxGifFrame::ofxGifFrame()
    : m_Top(0)
    , m_Left(0)
    , m_Texture()
    , m_Duration(0.f)
{

}

void ofxGifFrame::setFromPixels(const ofPixels &px, int left , int top, const unsigned int &channels, float duration)
{
    m_Left = left;
    m_Top = top;
    m_Duration = duration;

    m_Texture.loadData(px.getData(), px.getWidth(), px.getHeight(), channels == 3 ? GL_RGB : GL_RGBA);
}

ofTexture *ofxGifFrame::getTexture()
{
    return &m_Texture;
}

int ofxGifFrame::getWidth() const
{
    return m_Texture.getWidth();
}

int ofxGifFrame::getHeight() const
{
    return m_Texture.getHeight();
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
