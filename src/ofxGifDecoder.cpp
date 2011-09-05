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

//----------------------------------------------------
void ofxGifDecoder::putBmpIntoPixels(FIBITMAP * bmp, ofPixels &pix, bool swapForLittleEndian ){
	// some images use a palette, or <8 bpp, so convert them to raster 8-bit channels
	FIBITMAP* bmpConverted = NULL;
    FITAG *tag;
    
    // on page 0!!
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "LogicalWidth", &tag)) {
        WORD logicalWidth = *(WORD *)FreeImage_GetTagValue(tag);
        //printf("logical width %i \n", logicalWidth);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "LogicalHeight", &tag)) {
        WORD logicalHeight = *(WORD *)FreeImage_GetTagValue(tag);
        //printf("logical height %i \n", logicalHeight);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameLeft", &tag)) {
        WORD frameLeft = *(WORD *)FreeImage_GetTagValue(tag);
        //printf("frameLeft %i \n", frameLeft);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameTop", &tag)) {
        WORD frameTop = *(WORD *)FreeImage_GetTagValue(tag);
        //printf("frameTop %i \n", frameTop);
    }
    
    if( FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "GlobalPalette", &tag) ) {
        globalPaletteSize = FreeImage_GetTagCount(tag);
        printf("we have a palette of %i colors \n", globalPaletteSize);
        if( globalPaletteSize >= 2 ) {
            globalPalette = (RGBQUAD *)FreeImage_GetTagValue(tag);
            for (int i = 0 ; i < globalPaletteSize; i++) {
                ofColor c;
                c.set(globalPalette[i].rgbRed, globalPalette[i].rgbGreen, globalPalette[i].rgbBlue);
                palette.push_back(c);
                //printf("n %i r %i g %i b %i\n", i, dcd.globalPalette[i].rgbRed, dcd.globalPalette[i].rgbGreen, dcd.globalPalette[i].rgbBlue);
                //printf("r %i g %i b %i \n", globalPalette[i].rgbRed, globalPalette[i].rgbGreen, globalPalette[i].rgbBlue);
            }
        }
    }

    
    if(FreeImage_GetBPP(bmp) == 8) {
        bmp = FreeImage_ConvertTo24Bits(bmp);
    }
    
    
	unsigned int width      = FreeImage_GetWidth(bmp);
	unsigned int height     = FreeImage_GetHeight(bmp);
	unsigned int bpp        = FreeImage_GetBPP(bmp);
	unsigned int channels   = (bpp / sizeof(PixelType)) / 8;
	unsigned int pitch      = FreeImage_GetPitch(bmp);
    
	// ofPixels are top left, FIBITMAP is bottom left
	FreeImage_FlipVertical(bmp);
	
	unsigned char * bmpBits = FreeImage_GetBits(bmp);
	if(bmpBits != NULL) {
		pix.setFromAlignedPixels(bmpBits, width, height, channels, pitch);
	} else {
		ofLogError() << "ofImage::putBmpIntoPixels() unable to set ofPixels from FIBITMAP";
	}
	
	if(bmpConverted != NULL) {
		FreeImage_Unload(bmpConverted);
	}
    
#ifdef TARGET_LITTLE_ENDIAN
	if(swapForLittleEndian) {
		pix.swapRgb();
	}
#endif
}
void ofxGifDecoder::reset(){
    pxs.clear();
    palette.clear();
}

void ofxGifDecoder::decode(string fileName) {
    reset();
	int					width, height, bpp;
	fileName                    = ofToDataPath(fileName);
	bool bLoaded                = false;
	FIMULTIBITMAP	* multiBmp  = NULL;
    
    
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(fileName.c_str(), 0);
	if(fif != FIF_UNKNOWN) {
		// or guess via filename
		fif = FreeImage_GetFIFFromFilename(fileName.c_str());
	}
	if(fif == FIF_GIF)  {
        // this will always give 32bpp gifs - see Additional notes (GIF specific) in fi doc p. 123 -!!!
        // also, apparently I shouldn't be using it.
		multiBmp = FreeImage_OpenMultiBitmap(fif, fileName.c_str(), false, false,true, GIF_LOAD256);
        
		if (multiBmp){
			bLoaded = true;
		}
	}
	//-----------------------------
    
	if ( bLoaded ){
        int count = FreeImage_GetPageCount(multiBmp);
        for (int i = 0; i < count; i++) {
            FIBITMAP * dib = FreeImage_LockPage(multiBmp, i);

            if(dib) {
                pxs.push_back(new ofPixels());
                
                putBmpIntoPixels(dib, *pxs.back(), true);
                FreeImage_UnlockPage(multiBmp, dib, false);
            }
        }
	} else {
		width = height = bpp = 0;
	}
    
	if (multiBmp != NULL){
        FreeImage_CloseMultiBitmap(multiBmp, 0);

	}
	
}
