#include "ofApp.h"
#include <cstdlib>
#include "maximilian.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(999);
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 1024*20; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    
    
    guiSetup(); //loads the graphical user interface
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    
    sample.load(ofToDataPath("bossa.wav")); //loading a bossa sample from the data
    
    
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        float * sound;//to be sent to buffer
        
        float noiseTone;
        float bossa = sample.play(speed/5); // starts sample playback
        float Karplus;
        float Bitcrushed;
        
        
        for (auto & CircleDelay : Circles) //for each circledelay object in the vector Circles
        {
            noiseTone = CircleDelay.CircleOscs()/Circles.size(); //generate the noise tone -- level is divided by the number of circledelay objects so everytime you add one the overall level doesnt get too much
            
            if (Sampler == false)//if sampler mode is NOT active process the noise tones into Karplus-Strong Plucks
            {
                 Karplus = CircleDelay.process(noiseTone, transpose, Key, cutoffSlider, resonanceSlider);
            }
            else{//if sampler mode IS active process the sample instead
                Karplus = CircleDelay.process(bossa, transpose, Key, cutoffSlider, resonanceSlider);
            }
            
            Bitcrushed = Bitcrusher.crusher(Karplus, DownSample, BitDepth, DownSampleMix);
            
            *sound += Bitcrushed;
            
        }
        
        output[i*nChannels    ] = *sound; //output *sound to both stereo channels
        output[i*nChannels + 1] = output[i*nChannels    ];
        
        
    }
    
    
}


void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    // ofBackground(0,0,0);
    backgroundSections();
    
    //s
    ofSetLineWidth(5);
    ofColor c;
    ofSetColor(200, 255, 200);
    int frameCount = ofGetFrameNum();
    int frameAngle = frameCount;
    
    float lineX = length * cos((frameAngle*speed)/60);
    float lineY = length * sin((frameAngle*speed)/60);
    ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2 + lineX, ofGetHeight()/2 + lineY);
    
    for (auto & CircleDelay : Circles)
    {
        CircleDelay.draw();
        //cout << CircleDelay.x << endl;
        for (int i = 0; i <= length; i++)
        {
            if(CircleDelay.x >= (int)((ofGetWidth()/2 + i*(lineX/length))-(0.05*i + (CircleDelay.w/2)))   &&
               CircleDelay.x <= (int)((ofGetWidth()/2 + i*(lineX/length))+(0.05*i + (CircleDelay.w/2)))   &&
               CircleDelay.y >= (int)((ofGetHeight()/2 + i*(lineY/length))-(0.05*i + (CircleDelay.w/2)))   &&
               CircleDelay.y <= (int)((ofGetHeight()/2 + i*(lineY/length))+(0.05*i + (CircleDelay.w/2))))
            {
                CircleDelay.trig = true;
            }
            else CircleDelay.trig = false;
        }
    }
    
    
    
    gui.draw();
    
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //If the mouse is pressed && there are less than 5 circles add a new circle oject in that position
    //If there are more than 5 objects in the vector the first one created is poped out of the vector and a new circle added
    
    if (Circles.size() < 5)
    {
        Circles.insert(Circles.begin(), CircleDelay(x, y, CircleRadius, FB));
    }else if (Circles.size() >= 5)
    {
        Circles.pop_back();
        Circles.insert(Circles.begin(), CircleDelay(x, y, CircleRadius, FB));
        
    }
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

///--- my functions

void ofApp::guiSetup()
{
    //setting up the GUI
    gui.setup();
    gui.add(speed.setup("speed", 0.6, 0.1, 10));
    gui.add(length.setup("length", 640, 10, sqrt( (((ofGetHeight()/2)*(ofGetHeight()/2)) + ((ofGetWidth()/2)*(ofGetWidth()/2))))));
    gui.add(CircleRadius.setup("sustain", 10, 1, 50));
    
    gui.add(FB.setup("FeedBack", 0.98, 0.01, .99));
    
    gui.add(cutoffSlider.setup("Dampen", 20000, 20, 20000));
    gui.add(resonanceSlider.setup("Tightness", 30, 25, 40));
    
    gui.add(transpose.setup("Transpose", 0, -24, 24));
    gui.add(Key.setup("Key", true));
    gui.add(Sampler.setup("Sampler Mode", false));
    
    gui.add(DownSample.setup("Downsample",44100,0,44100));
    gui.add(DownSampleMix.setup("Downsample mix",1,0,1));
    gui.add(BitDepth.setup("Bit Depth",16,1,16));
}

void ofApp::backgroundSections()
{
    //gets distance between centre and corner
    float maxDistance = sqrt((ofGetWidth()/2*ofGetWidth()/2)+(ofGetHeight()/2*ofGetHeight()/2));
    
    //sets number of sections that will sybolise the change in notes
    int Sections = 8;
    
    //splits the distance into 8 sections
    int CurrentSection = floor(maxDistance/Sections);
    int sec = 0;
    for(int i = maxDistance; i > 0; i -= (CurrentSection))
    {
        //cout << i << endl;
        //cout << 255*(i/maxDistance) << endl;
        ofSetColor(255*(i/maxDistance));
        ofCircle(ofGetWidth()/2,ofGetHeight()/2, i);
    }
}

