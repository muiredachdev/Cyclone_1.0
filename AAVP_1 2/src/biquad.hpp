//
//  biquad.hpp
//  AAVP_FILTER
//
//  Created by Muiredach O'Riain on 19/01/2017.
//
//

#ifndef biquad_hpp
#define biquad_hpp

#include <stdio.h>
#include "ofMain.h"
#include <array>



class Biquad{
public:
    
    
    Biquad();
    
    //Properties
    float SampleRate;
    float mX1,mX2,mY1,mY2;
    //array< float, 44100*10 > Buffer;
    int BufferIndex;

    double process(double input, int cutoffSlider, int resSlider);
    
    float cutoff;
    float res;
    float k;
    
    //placeholders
    float c1;
    float c2;
    float c3;
    
    
    //co efficients
    float mA0;
    float mA1;
    float mA2;
    float mB1;
    float mB2;
    
    double output;
    
};

#endif /* biquad_hpp */
