#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0,0,0);


    ofSetBackgroundAuto(false);


	camWidth 		= 640;	// try to grab at this size.
	camHeight 		= 480;

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);

    font.loadFont("Courier New Bold.ttf", 12);

    // this set of characters comes from processing:
    //http://processing.org/learning/library/asciivideo.html

	// changed order slightly to work better for mapping
    //asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");

    ofEnableAlphaBlending();
    holdingframe = vidGrabber.getPixelsRef();

    // SOUND STUFF SOUND STUFF SOUND STUFF
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)

	soundStream.listDevices();

	//if you want to set a different device id
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

	int bufferSize = 256;


	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);

	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;

	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);


}

void ofApp::setupStage(){



}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();

	//lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

	//lets record the volume into an array
	volHistory.push_back( scaledVol );

	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    //glEnable(GL_DEPTH_TEST);

    if(clearscreen){
        ofSetColor(0,0,0);
        ofRect(0,0,windowWidth,windowHeight);
        clearscreen = false;
    }

    // change background video alpha value based on the mouse position
    float videoAlphaValue = ofMap(mouseX, 0,ofGetWidth(),0,255);

    // set a white fill color with the alpha generated above
    //ofSetColor(255,255,255,videoAlphaValue);

    // draw the raw video frame with the alpha value generated above
    //if(diff)

    //vidGrabber.draw(0,0);

    ofPixelsRef pixelsRef = vidGrabber.getPixelsRef();

    frames.push_front((ofPixels)pixelsRef);
    qsize+=1;
    if(qsize > 200){
        frames.pop_back();
        qsize-=1;
    }

    //cout << "Frames : " << qsize << "\n";

    int frame = 0;
    holdingImage.setFromPixels(frames[1]);
    //holdingImage.draw(camWidth,0);
    //ofSetHexColor(0xffffff);


    framediff=0;
    for (int i = 0; i < camWidth; i+= 3){
        for (int j = 0; j < camHeight; j+= 3){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
            float holdinglightness = holdingframe.getColor(i,j).getLightness();

            int magnitude = (int)abs(lightness-holdinglightness);

            framediff = framediff + magnitude;
            // calculate the index of the character from our asciiCharacters array
            //int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
            // draw the character at the correct location

            if(magnitude > 25){
                ofSetColor(pixelsRef.getColor(i,j));



                int csize = ofMap(volmod,0,100,1,50);
                int iX = ofMap(i,0,camWidth,50,windowWidth-50);
                int jY = ofMap(j,0,camHeight,10,windowHeight-10);
                int noise = -5.0;
                ofCircle(iX+ofRandom(-noise,noise),jY+ofRandom(-noise,noise), csize);
                //ofLine(iX,jY,iX+ofRandom(-noise,noise),jY+ofRandom(-noise,noise));
                //font.drawString(ofToString(magnitude), i, j);

            }

        }
    }
    /*
    for(int i=0;i<circles.size();i++){
        ofVec2f p = circles[i];
        ofCircle(p.x, p.y, 5);
    }*/


    if(framediff > threshold){
        diff = true;
    }else{
        diff = false;
    }
    holdingframe = vidGrabber.getPixelsRef();

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

	// in fullscreen mode, on a pc at least, the
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...

	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
		ofSetColor(0,0,0);
		soundStream.start();
		clearscreen = true;
	}
	if( key == 'e' ){
		soundStream.stop();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //cout << "Threshold : " <<threshold << "\n";
    //threshold = ofMap(mouseX,0,ofGetWidth(),500,3500);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    windowHeight = h;
    windowWidth = w;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){

	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}

	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;

	// this is how we get the root of rms :)
	curVol = sqrt( curVol );

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

    volmod = (smoothedVol*50)*(smoothedVol*50);

    printf("volmod: %.2f\n",volmod);

    if(volmod > 100){
        clearscreen=true;
    }

	bufferCounter++;

}

