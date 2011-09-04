#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    dcd.decode("iana.gif");
    for (int i = 0; i < dcd.pxs.size(); i++) {
        decodedImages.push_back(new ofImage(*dcd.pxs[i]));
    }
}

//--------------------------------------------------------------
void testApp::update(){ 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 250);
    for(int i = 0; i < decodedImages.size() ; i++) {
        decodedImages[i]->draw(i*decodedImages[i]->width*.5,0, decodedImages[i]->width*.5, decodedImages[i]->height*.5);
    }
    ofDisableAlphaBlending();
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

