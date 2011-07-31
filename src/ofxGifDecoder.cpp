//
//  ofxGifDecoder.cpp
//  gifPhasing
//
//  Created by Jesus Gollonet on 5/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifDecoder.h"
// from ofimage
//----------------------------------------------------

void ofxGifDecoder::putBmpIntoPixels(FIBITMAP * bmp, ofPixels &pix, bool swapForLittleEndian ){
	// some images use a palette, or <8 bpp, so convert them to raster 8-bit channels
	FIBITMAP* bmpConverted = NULL;
    
    
	if(FreeImage_GetColorType(bmp) == FIC_PALETTE || FreeImage_GetBPP(bmp) < 8) {
		if(FreeImage_IsTransparent(bmp)) {
			bmpConverted = FreeImage_ConvertTo32Bits(bmp);
		} else {
			bmpConverted = FreeImage_ConvertTo24Bits(bmp);
		}
		bmp = bmpConverted;
	}
    
	unsigned int width = FreeImage_GetWidth(bmp);
	unsigned int height = FreeImage_GetHeight(bmp);
	unsigned int bpp = FreeImage_GetBPP(bmp);
	unsigned int channels = (bpp / sizeof(PixelType)) / 8;
	unsigned int pitch = FreeImage_GetPitch(bmp);
	
	// ofPixels are top left, FIBITMAP is bottom left
	FreeImage_FlipVertical(bmp);
	
	unsigned char* bmpBits = FreeImage_GetBits(bmp);
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

void ofxGifDecoder::decode(string fileName) {
    
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
        
		multiBmp = FreeImage_OpenMultiBitmap(fif, fileName.c_str(), false, false,true, GIF_PLAYBACK);////(fif, fileName.c_str(), 0);
		if (multiBmp){
			bLoaded = true;
		}
	}
	//-----------------------------
    
	if ( bLoaded ){
        printf("loaded!!!   ");
        int count = FreeImage_GetPageCount(multiBmp);
        printf ("we have %i num pages\n", count);
		//putBmpIntoPixels(bmp,pix);
        for (int i = 0; i < count; i++) {
            FIBITMAP * dib = FreeImage_LockPage(multiBmp, i);

            if(dib) {
                
                pxs.push_back(new ofPixels());
                putBmpIntoPixels(dib, *pxs.back(), true);
                printf("we have dib!!\n");
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
