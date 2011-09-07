//
//  ofxGifDecoder.cpp
//  gifPhasing
//
//  Created by Jesus Gollonet on 5/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifDecoder.h"
//#include "FreeImage.h"
 #define WORD uint16_t

ofxGifDecoder::ofxGifDecoder(){
    globalPalette = NULL;
    globalPaletteSize = 0;
}

// return a bool if succesful?
bool ofxGifDecoder::decode(string fileName) {
    reset();
	int width, height, bpp;
	fileName                    = ofToDataPath(fileName);
	bool bDecoded               = false;
	FIMULTIBITMAP	* multiBmp  = NULL;
    
    
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(fileName.c_str(), 0);
    
	if(fif != FIF_GIF) {
        ofLog(OF_LOG_WARNING, "ofxGifDecoder::decode. this is not a gif file. not processing");
        
        return bDecoded;
	}
    
    multiBmp = FreeImage_OpenMultiBitmap(fif, fileName.c_str(), false, false,true, GIF_LOAD256);
    
    if (multiBmp){
        printf("we have multibitmap\n");

        // num frames
        int nPages = FreeImage_GetPageCount(multiBmp);
        printf("we have count %i frames  \n", nPages);            
        
        // here we process the first frame
        for (int i = 0; i < nPages; i++) {
            FIBITMAP * dib = FreeImage_LockPage(multiBmp, i);            
            if(dib) {
                if (i == 0) {
                    createGifFile(dib, nPages);
                    bDecoded = true;   // we have at least 1 frame
                }
                
                processFrame(dib, i);
                FreeImage_UnlockPage(multiBmp, dib, false);
            } else {
                ofLog(OF_LOG_WARNING, "ofxGifDecoder::decode. problem locking page");
                
            }
        }
        FreeImage_CloseMultiBitmap(multiBmp, 0);
    }else {
        ofLog(OF_LOG_WARNING, "ofxGifDecoder::decode. there was an error processing.");
	}    
    return bDecoded;
}

void ofxGifDecoder::createGifFile(FIBITMAP * bmp, int _nPages){
    FITAG *tag;
    // on page 0!!
    int logicalWidth, logicalHeight;
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "LogicalWidth", &tag)) {
        logicalWidth = *(int *)FreeImage_GetTagValue(tag);
        printf("logical width %i \n", logicalWidth);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "LogicalHeight", &tag)) {
        logicalHeight = *(int *)FreeImage_GetTagValue(tag);
        printf("logical height %i \n", logicalHeight);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "GlobalPalette", &tag) ) {
        globalPaletteSize = FreeImage_GetTagCount(tag);
        printf("we have a global palette of %i colors \n", globalPaletteSize);
        if( globalPaletteSize >= 2 ) {
            globalPalette = (RGBQUAD *)FreeImage_GetTagValue(tag);
            for (int i = 0 ; i < globalPaletteSize; i++) {
                ofColor c;
                c.set(globalPalette[i].rgbRed, globalPalette[i].rgbGreen, globalPalette[i].rgbBlue);
                palette.push_back(c);
            }
        }
    }
    
    gifFile.setup(logicalWidth, logicalHeight, palette, _nPages);    
    
}

void ofxGifDecoder::processFrame(FIBITMAP * bmp, int _frameNum){
    FITAG *tag;
    ofPixels pix;

    int frameLeft, frameTop;
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameLeft", &tag)) {
        frameLeft = *(int *)FreeImage_GetTagValue(tag);
        //printf("frameLeft %i \n", frameLeft);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameTop", &tag)) {
        frameTop = *(int *)FreeImage_GetTagValue(tag);
        //printf("frameTop %i \n", frameTop);
    }
    
    // we do this for drawing. eventually we should be able to draw 8 bits?
    if(FreeImage_GetBPP(bmp) == 8) {
        // maybe we should only do this when asked for rendering?
        bmp = FreeImage_ConvertTo24Bits(bmp);
    }
    
    
	unsigned int width      = FreeImage_GetWidth(bmp);
	unsigned int height     = FreeImage_GetHeight(bmp);
	unsigned int bpp        = FreeImage_GetBPP(bmp);
	unsigned int channels   = (bpp / sizeof(PixelType)) / 8;
	unsigned int pitch      = FreeImage_GetPitch(bmp);
    
    printf("getwidth %i height %i \n", width, height);
	// ofPixels are top left, FIBITMAP is bottom left
	FreeImage_FlipVertical(bmp);
	
	unsigned char * bmpBits = FreeImage_GetBits(bmp);
	if(bmpBits != NULL) {
		pix.setFromAlignedPixels(bmpBits, width, height, channels, pitch);
        gifFile.addFrame(pix, frameLeft, frameTop);
	} else {
		ofLogError() << "ofImage::putBmpIntoPixels() unable to set ofPixels from FIBITMAP";
	}
	
    
#ifdef TARGET_LITTLE_ENDIAN
	//if(swapForLittleEndian) {
		pix.swapRgb();
	//}
#endif

}

void ofxGifDecoder::reset(){
    pxs.clear();
    palette.clear();
}


// should I return a pointer of a copy?
ofxGifFile ofxGifDecoder::getFile() {
    return gifFile;
}
