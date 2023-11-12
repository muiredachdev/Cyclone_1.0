//
//  CircleDelay.cpp
//  AAVP_1
//
//  Created by Muiredach O'Riain on 16/01/2017.
//
//

#include "CircleDelay.hpp"

CircleDelay::CircleDelay(int _x, int _y, int _w, float _FB): x(_x), y(_y), w(_w), FB(_FB){
    
    BufferIndex = 0;
    Feedback = FB;
}




void CircleDelay::draw()
{
    ofCircle(x,y,w); //draws a circle at position (x,y) with a circumference of w;
}




int CircleDelay::calcNote(int transpose, bool key){
    
    int SampleRate = 44100;
    
    
    //fills an array with all note frequency values
    float midi[127];
    
    for (int i= 0; i < 127; ++i)
    {
        // nf=2^{(d-69)/12} * 440
        
        //This is an algoithm that i found at "http://subsynth.sourceforge.net/midinote2freq.html" and convetrted to C++
        //It converts a midi not value into its respective frequency value
        
        midi[i] = pow(2, ((i-69.0)/12)) * 440;
    }
    
    
    float distance = sqrt(((ofGetWidth()/2 - x)*(ofGetWidth()/2 - x))+( (ofGetHeight()/2 - y) * (ofGetHeight()/2 - y) )); //calculates the distance of circle from the center of the window
    float maxDistance = sqrt((ofGetWidth()/2*ofGetWidth()/2)+(ofGetHeight()/2*ofGetHeight()/2));
    
    int maxSections = 8; //determines how many notes the area of the window is split into
    int section = floor(maxSections*(distance/maxDistance)); //pos of circle put into 1 of 8 categories
    
    
    //sets note of each section
    int note;
    
    if (section == 0) note = 48; //C
    if (section == 1) note = 50; //D
    if (section == 2 && !key) note = 51; //E♭
    if (section == 2 && key) note = 52; //E
    if (section == 3) note = 53; //F
    if (section == 4) note = 55; //G
    if (section == 5 && !key) note = 56; //A♭
    if (section == 5 && key) note = 57; //A
    if (section == 6 && !key) note = 57; //B♭
    if (section == 6 && key) note = 59; //B
    if (section == 7) note = 60; //C
    
    return 44100/midi[note + transpose]; //sets the length of the delay (in samples) and the pitch of the pluck
}




double CircleDelay::CircleOscs()
{
    
    //sets the enelope depending on positon and size of circle
    CircleEnvelope.setAttack(1);
    CircleEnvelope.setDecay(1);  // Needs to be at least 1
    CircleEnvelope.setSustain(1);
    CircleEnvelope.setRelease(w*30);
    
    //initialises the oscilators to a noise and a Phazor :P
    double pluck = CirclePluck.noise();
    CircleCurrentVolume=CircleEnvelope.adsr(1.,CircleEnvelope.trigger);
    
    
    //triggers a pluck
    if (trig == true){
        CircleEnvelope.trigger=1;
    }
    if (trig == false){
        CircleEnvelope.trigger=0;
    }

    
    return (CircleCurrentVolume*pluck);
}





double CircleDelay::process(double input,int transpose, bool key, int cutoffSlider, int resSlider)
{
    
    double output = Buffer[BufferIndex];
    
    Buffer[BufferIndex] = biquad.process (input + (Buffer[BufferIndex] * Feedback), cutoffSlider, resSlider); //feeds each circle process through the LFP
    
    BufferIndex ++;
    BufferIndex%=calcNote(transpose, key); //sets the number of samples read before the bufferIndex resets, by changing this number ( to the sampleRate over the desired frequency ) we can generate any given tone
    
    return output;
}






