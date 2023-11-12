//
//  biquad.cpp
//  AAVP_FILTER
//
//  Created by Muiredach O'Riain on 19/01/2017.
//
//

#include "biquad.hpp"

//Biquad LPF with a cutoff and resonance perameters

Biquad::Biquad(): SampleRate(44100), mX1(0), mX2(0), mY1(0), mY2(0), BufferIndex(0) {
    
}
//this process runs a signal through a series of coefficents that
double Biquad::process(double input, int cutoffSlider, int resSlider)
{
    

    cutoff = 2*cutoffSlider/SampleRate;
    res = pow(10, 0.05*resSlider);
    
    k = 0.5*res*sin(M_1_PI*cutoff);
    
    c1 = 0.5 * (1 - k)/(1 + k);
    c2 = (0.5 + c1) * cos(pi * cutoff);
    c3 = (0.5 + c1 - c2) * 0.5/2;
    
    //coefficents
    mA0 = 2 * c3;
    mA1 = 2 * 2 * c3;
    mA2 = 2 * c3;
    mB1 = 2 * (-1*c2);
    mB2 = 2 * c1;
    
    //trransfer function
    output = (mA0*input) + (mA1*mX1) + (mA2*mX2) - (mB1*mY1) - (mB2*mY2);
    
    mX2 = mX1;
    mX1 = input;
    mY2 = mY1;
    mY1 = output;
    
    return output;
}