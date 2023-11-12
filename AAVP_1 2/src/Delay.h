//
//  Delay.h
//  AAVP_1
//
//  Created by Muiredach O'Riain on 15/01/2017.
//
//

#ifndef myDelay_h
#define myDelay_h

#include <stdio.h>
#include <array>
#include <cstdlib>

using std::array;

class myDelay{
    
public:
    
    array< float, 44100*2 > Buffer;
    float Feedback;
    int BufferIndex, BufferLength;
    
    myDelay(/*cum*/)
    {
        BufferIndex = 0;
        Feedback = 0.5;
        BufferLength = 44100;
    }
    
    float process(float input)
    {
        float output = Buffer[BufferIndex];
        BufferIndex = input * Feedback;
        BufferIndex ++;
        BufferIndex%=BufferLength;
        
        return output;
        
    }
    
};

#endif /* myDelay_h */
