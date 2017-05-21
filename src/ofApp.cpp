#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    soundStream.printDeviceList();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

    drawBuffer.resize(bufferSize);
    
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    gray.allocate(640, 480);
    normals.allocate(640, 480);
    
    ofSetWindowShape(640*2, 480);
}

//--------------------------------------------------------------
void ofApp::update(){
    gray.update();
    
    normals << gray;
    normals.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofSetColor(255);
    
    gray.draw();
    ofDrawBitmapString("GrayScott Reaction Diffusion", 15,15);
    ofDrawBitmapString("K ( mouseX ): " + ofToString(gray.getK()) , 15,35);
    ofDrawBitmapString("F ( mouseY ): " + ofToString(gray.getF()) , 15,55);
    
    normals.draw(640,0);
    ofDrawBitmapString("NormalMap of the GrayScott", 640+15,15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //printf("aaa %f\n", ofMap(mouseY,0,480,0.01,0.028,true));

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    gray.begin();
    ofSetColor(ofNoise( ofGetElapsedTimef() )*255);
    ofDrawCircle(x, y, 3);
    gray.end();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    double in;
    
    for(int i = 0; i<bufferSize; i++){
        counter++;
        in = input[i*2];
        //drawBuffer[counter%drawBuffer.size()] = in;
        printf("input %f\n", in);
        actualAudio = in;
    }
    gray.setK( abs(actualAudio) );
    gray.setF( abs(actualAudio) );
    //printf("target %f\n", ofMap(mouseY,0,480,0.01,0.028,true));
    //printf("actual %f\n", actualAudio);
}
