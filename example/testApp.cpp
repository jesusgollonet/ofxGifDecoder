#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    bool success = dcd1.decode("iana/i01.gif"); 
    if (success) gif1 = dcd1.getFile();
    
    success = dcd1.decode("iana/i02.gif");
    if (success) {
        gif2 = dcd1.getFile();
    }
    
    success = dcd1.decode("iana/i03.gif");
    if (success) {
        gif3 = dcd1.getFile();
    }
    
    
    printf("gif 1 frames %i \n ", gif1.getNumFrames());
    printf("gif 2 frames %i \n ", gif2.getNumFrames());
    printf("gif 3 frames %i \n ", gif3.getNumFrames());
    ofSetFrameRate(2);
}

//--------------------------------------------------------------
void testApp::update(){ 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255, 255);
    
    for(int i = 0; i < gif1.getNumFrames(); i++){
        gif1.drawFrame(i, i*gif1.getWidth()*.3f, 0, gif1.getWidth()*.3f, gif1.getHeight()*.3f);
    }
    for(int i = 0; i < gif2.getNumFrames(); i++){
        gif2.drawFrame(i, i*gif2.getWidth()*.3f, 200, gif2.getWidth()*.3f, gif2.getHeight()*.3f);

    }
    for(int i = 0; i < gif3.getNumFrames(); i++){
        gif3.drawFrame(i, i*gif3.getWidth()*.3f, 400, gif3.getWidth()*.3f, gif3.getHeight()*.3f);    
    }
    
//    gif1.drawFrame((int)(floor(ofRandom(gif1.getNumFrames()))), 0, 0);
//    gif2.drawFrame((int)(floor(ofRandom(gif2.getNumFrames()))), 0, 250);
//    gif3.drawFrame((int)(floor(ofRandom(gif3.getNumFrames()))), 0, 500);
//    //    
    //    for (int i = 0; i < gif1.getPalette().size(); i++) {
    //        ofSetColor(gif1.getPalette()[i]);
    //        ofRect((i%25)*10, (i/25)*10, 10, 10);
    //    }
    //
//    for (int i = 0; i < gif2.getPalette().size(); i++) {
//        ofSetColor(gif2.getPalette()[i]);
//        ofRect(200 + (i%25)*10, (i/25)*10, 10, 10);
//    }
    //
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

