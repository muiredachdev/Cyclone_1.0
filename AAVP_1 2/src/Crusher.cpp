//
//  Crusher.cpp
//  AAVP_CRUSHER
//
//  Created by Muiredach O'Riain on 21/01/2017.
//
//

#include "Crusher.hpp"

Crusher::Crusher()
{
}
double Crusher::crusher(double input, float normfreq, int bits, float clipLevel){
    
    //this simple bitcrusher takes a signal and decreases its resolution by quantizing each bit based on the phase of a phasor
    
    //by changing the frequency of the phasor we can also essentially change the samplerate of the input signal, degrading it further
    
    float step = pow(0.5, bits); //sets the bit depth
    
    double last = 0;
    
    //returns the
    if (Phase.phasor(normfreq) >= clipLevel) {
        last = step * floor(input/step + 0.5);//quantize the signal
    }
    
    return last; //returns the bitcrushed value
}