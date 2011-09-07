//
//  ofxGifFile.h
//  ofxGifDecoderAddon
//
//  Created by Jesus.Gollonet on 9/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGifFrame.h"

class ofxGifFile {
    public:
        ofxGifFile();
        ~ofxGifFile();
        void setup(int _w, int _h);
        
    private:
        vector <ofxGifFrame > gifFrames;
        //vector <ofPixels *> rawPixels;
               int w, h;

};