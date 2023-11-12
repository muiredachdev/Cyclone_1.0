#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMaxim.h"
#include "CircleDelay.hpp"
#include "biquad.hpp"
#include "Crusher.hpp"


#include <vector>
#include <array>

using std::vector;
using std::array;

class ofApp : public ofBaseApp{

	public:
    
    //methods
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
    
    //general methods for tidyness
    
        void guiSetup();
        void backgroundSections();

    
        int		bufferSize; /* buffer size */
        int		sampleRate; /* sample rate -- should be 44100 */
    
        float fftFun;
    
    
    
        //--- Gui Setup Stuff-----
    
    //interface
    
        ofxPanel gui; //main pannel
        ofxFloatSlider speed;//Speed of playhead  -- also playback speed for the Sampler
        ofxFloatSlider length;//length of playhead
    
    //karplus
    
        ofxFloatSlider FB;//Karplus Feedback Amount
        ofxFloatSlider CircleRadius;//radius of drawn circles -- also Karplus release time
        ofxIntSlider transpose;//Transposes Karplus pitch
        ofxToggle Key;//major or minor
    
    //LPF
        ofxFloatSlider cutoffSlider; // Cutoff of LPF
        ofxFloatSlider resonanceSlider; // Resonance of LPF
    
    //Bitcrusher
        ofxIntSlider DownSample;
        ofxFloatSlider DownSampleMix;
        ofxIntSlider BitDepth;
    
    //Sampler
        ofxToggle Sampler;//sampler mode on or off
    
    
        //--- Sound Setup Stuff-----
    
    //karplus
        ofxMaxiOsc noise; //noise generator for initital karplus sound
        vector <CircleDelay> Circles; //vector to be filled with Circle objects
    
    //Bitcrusher
        Crusher Bitcrusher; //Bitcrusher object

    
    //Sampler
        maxiSample sample; //bossa sample for sampler mode
    
    //fft
    
    maxiFFT fft;
    
    
    
		
};

