#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //dcd.decode("iwdrm04.gif");
    //bool success = dcd.decode("iwdrm02.gif"); 
    bool success = dcd.decode("iana/i02.gif"); 
    if (success) decodedFile = dcd.getFile();
    //colors = dcd.palette;
    
//    for (int i = 0; i < dcd.pxs.size(); i++) {
//        decodedImages.push_back(new ofImage(*dcd.pxs[i]));
//    }
}

//--------------------------------------------------------------
void testApp::update(){ 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255, 255);
//    for(int i = 0; i < decodedImages.size() ; i++) {
//        decodedImages[i]->draw(i*decodedImages[0]->width*.5,0, decodedImages[0]->width*.5, decodedImages[0]->height*.5);
//    }
//
    decodedFile.draw(200, 200);
    for (int i = 0; i < decodedFile.getPalette().size(); i++) {
        ofSetColor(decodedFile.getPalette()[i]);
        ofRect((i%25)*10, (i/25)*10, 10, 10);
    }
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

