//
//  ofxGifDecoder.cpp
//  gifPhasing
//
//  Created by Jesus Gollonet on 5/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifDecoder.h"
#include "ofMain.h"

ofxGifDecoder::ofxGifDecoder()
    : m_GlobalPaletteSize(0)
    , m_GlobalPalette(nullptr)
{

}

ofxGifDecoder::~ofxGifDecoder()
{

}

ofxGifFile ofxGifDecoder::decode(string fileName, bool isUseDataPath)
{
    reset();

    if (isUseDataPath) {
        fileName = ofToDataPath(fileName);
    }

    ofxGifFile gifFile;
    FIMULTIBITMAP *multiBmp = nullptr;

    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    fif = FreeImage_GetFileType(fileName.c_str(), 0);
    if (fif != FIF_GIF) {
        ofLogWarning() << __FUNCTION__ << ": This is not a gif file. Not processing.";
        return gifFile;
    }

    multiBmp = FreeImage_OpenMultiBitmap(fif, fileName.c_str(), false, false, true, GIF_LOAD256);
    if (multiBmp) {
        // Frame numbers
        const int pageCount = FreeImage_GetPageCount(multiBmp);

        // Here we process the first frame
        for (int pageIndex = 0; pageIndex < pageCount; pageIndex++) {
            FIBITMAP *currentPage = FreeImage_LockPage(multiBmp, pageIndex);

            if (currentPage) {
                if (pageIndex == 0) {
                    createGifFile(currentPage, pageCount, gifFile);
                }

                processFrame(currentPage, gifFile);
                FreeImage_UnlockPage(multiBmp, currentPage, false);
            }
            else {
                ofLogWarning() << __FUNCTION__ << "Problem locking page.";
            }
        }
        FreeImage_CloseMultiBitmap(multiBmp, 0);
    }
    else {
        ofLogWarning() << __FUNCTION__ << "There was an error processing.";
    }

    return gifFile;
}

void ofxGifDecoder::createGifFile(FIBITMAP *bmp, const int &pageCount, ofxGifFile &gifFile)
{
    FITAG *tag = nullptr;
    int logicalWidth = 0, logicalHeight = 0;

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "LogicalWidth", &tag)) {
        logicalWidth = *(unsigned short *)FreeImage_GetTagValue(tag);
    }

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "LogicalHeight", &tag)) {
        logicalHeight = *(unsigned short *)FreeImage_GetTagValue(tag);
    }

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "GlobalPalette", &tag)) {
        m_GlobalPaletteSize = FreeImage_GetTagCount(tag);

        if (m_GlobalPaletteSize >= 2) {
            m_GlobalPalette = (RGBQUAD *)FreeImage_GetTagValue(tag);
            for (int i = 0 ; i < m_GlobalPaletteSize; i++) {
                ofColor c;
                c.set(m_GlobalPalette[i].rgbRed, m_GlobalPalette[i].rgbGreen, m_GlobalPalette[i].rgbBlue);
                m_Palettes.push_back(c);
            }
        }
    }

    gifFile.setup(logicalWidth, logicalHeight, m_Palettes, pageCount);

    RGBQUAD bgColor;
    if (FreeImage_GetBackgroundColor(bmp, &bgColor)) {
        gifFile.setBackgroundColor(ofColor(bgColor.rgbRed, bgColor.rgbGreen, bgColor.rgbBlue));
    }
}

void ofxGifDecoder::processFrame(FIBITMAP *bmp, ofxGifFile &gifFile)
{
    FITAG *tag = nullptr;
    unsigned short frameLeft = 0, frameTop = 0;
    float frameDuration = 0.f;
    GifFrameDisposal disposal_method = GIF_DISPOSAL_BACKGROUND;

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameLeft", &tag)) {
        frameLeft = *(unsigned short *)FreeImage_GetTagValue(tag);
    }

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameTop", &tag)) {
        frameTop = *(unsigned short *)FreeImage_GetTagValue(tag);
    }

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "FrameTime", &tag)) {
        long frameTime = *(long *)FreeImage_GetTagValue(tag);// Centiseconds 1/100 sec
        frameDuration = (float)frameTime / 1000.f;
    }

    if (FreeImage_GetMetadata(FIMD_ANIMATION, bmp, "DisposalMethod", &tag)) {
        disposal_method = (GifFrameDisposal) * (unsigned char *)FreeImage_GetTagValue(tag);
    }

    if (FreeImage_GetColorType(bmp) == FIC_PALETTE || FreeImage_GetBPP(bmp) < 8) {
        FIBITMAP *bmpConverted = nullptr;
        if (FreeImage_IsTransparent(bmp)) {
            bmpConverted = FreeImage_ConvertTo32Bits(bmp);
        }
        else {
            bmpConverted = FreeImage_ConvertTo24Bits(bmp);
        }

        bmp = bmpConverted;
    }

    const unsigned int width = FreeImage_GetWidth(bmp);
    const unsigned int height = FreeImage_GetHeight(bmp);
    const unsigned int bpp = FreeImage_GetBPP(bmp);
    // Changed this because we're not using PixelType template anywhere else...
    const unsigned int channels = (bpp / sizeof(unsigned char)) / 8;
    const unsigned int pitch = FreeImage_GetPitch(bmp);

    // ofPixels are top left, FIBITMAP is bottom left
    FreeImage_FlipVertical(bmp);
    const unsigned char *bmpBits = FreeImage_GetBits(bmp);

    if (bmpBits != NULL) {
        ofPixels pixels;
        pixels.setFromAlignedPixels(bmpBits, width, height, channels, pitch);
#ifdef TARGET_LITTLE_ENDIAN
        pixels.swapRgb();
#endif //TARGET_LITTLE_ENDIAN
        gifFile.addFrame(pixels, frameLeft, frameTop, channels, disposal_method, frameDuration);
    }
    else {
        ofLogError() << __FUNCTION__ << "Unable to set ofPixels from FIBITMAP.";
    }
}

void ofxGifDecoder::reset()
{
    m_Palettes.clear();
}
