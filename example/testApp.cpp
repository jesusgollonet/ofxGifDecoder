#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    for (int i = 1; i < 10; i++) {
        bool success = dcd.decode("iana/i0"+ofToString(i)+".gif");
        if (success) {
            gifs.push_back(dcd.getFile());
        }
    }    
    sizeMult = .2f;
}

//--------------------------------------------------------------
void testApp::update(){ 
    
}

//--------------------------------------------------------------
void testApp::draw(){

    for (int i = 0; i < gifs.size(); i++) {
        for (int j = 0; j < gifs[i].getNumFrames(); j++) {
            ofSetColor(255, 255, 255, 255);
            gifs[i].drawFrame(
                              j, 
                              j * gifs[i].getWidth()  * sizeMult, 
                              i * gifs[i].getHeight() * sizeMult, 
                              gifs[i].getWidth()      * sizeMult, 
                              gifs[i].getHeight()     * sizeMult
                              );
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

