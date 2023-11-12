//
//  Crusher.hpp
//  AAVP_CRUSHER
//
//  Created by Muiredach O'Riain on 21/01/2017.
//
//

#ifndef Crusher_hpp
#define Crusher_hpp

#include <stdio.h>
#include "ofxMaxim.h"
#include "ofMain.h"

class Crusher{
public:
    Crusher();
    
    //attributes
    ofxMaxiOsc Phase;
    
    double crusher(double input, float normfreq, int bits, float clipLevel);
};

#endif /* Crusher_hpp */
