#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    for (int i = 1; i < 10; i++) {
        bool success = dcd.decode("iana/i0"+ofToString(i)+".gif");
        if (success) {
            gifs.push_back(dcd.getFile());
        }
    }    
    sizeMult = .3f;
}

//--------------------------------------------------------------
void testApp::update(){ 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    float mousePct = (float)mouseY/ofGetWindowHeight();

    for (int i = 0; i < gifs.size(); i++) {
        
        int frameIndex =MIN((int)( mousePct * gifs[i].getNumFrames()-1), gifs[i].getNumFrames()-1);
        //printf("frameIndex %i \n", frameIndex);        
        int gifW = gifs[0].getWidth()*sizeMult;
        int gifH = gifs[i].getHeight()*sizeMult;
        gifs[i].drawFrame(frameIndex, i * gifW, 0, gifW, gifH);
        
        for (int j = 0; j < gifs[i].getPalette().size(); j++) {
            ofSetColor(gifs[i].getPalette()[j].r, gifs[i].getPalette()[j].g, gifs[i].getPalette()[j].b);
            ofRect(i * gifW + j%15*10, gifH + j/15*10 , 10, 10);
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case ' ':
            break;
        case 's':
            
            break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
//--------------------------------------------------------------
void testApp::exit(){ 
    
}

