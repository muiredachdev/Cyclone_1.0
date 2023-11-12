//
//  CircleDelay.hpp
//  AAVP_1
//
//  Created by Muiredach O'Riain on 16/01/2017.
//
//

#ifndef CircleDelay_hpp
#define CircleDelay_hpp

#include <stdio.h>
#include "ofxMaxim.h"
#include "biquad.hpp"
#include "ofMain.h"
#include <array>

using std::array;

class CircleDelay{

public:
    //constuctor and initialisation
    explicit CircleDelay(int _x, int _y, int _w, float FB);
    
    //properties for the circle
    int x;
    int y;
    int w;
    float FB;
    
    //properties for the delay
    array< float, 44100*2 > Buffer; //this sets the size of the delay buffer to 2 seconds (considering a SamleRate of 44100Hz
    float Feedback;
    int BufferIndex, BufferLength;
    
    //properties noise generation
    ofxMaxiOsc CirclePluck;
    ofxMaxiOsc CircleCounter;
    maxiEnv CircleEnvelope;
    double CircleOscOutput, CircleCurrentVolume;
    bool trig = false;
    
    Biquad biquad;

    
    
    // Methods
    void draw();
    double process(double input,int transpose, bool key, int cutoffSlider, int resSlider);
    
    int calcNote( int transpose, bool key);
    double CircleOscs();
    
};

#endif /* CircleDelay_hpp */
