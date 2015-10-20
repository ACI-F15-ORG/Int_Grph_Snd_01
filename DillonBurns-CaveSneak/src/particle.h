//
//  Particle.h
//  ParticleMadness
//
//  Created by Shawn Lawson on 9/9/14.
//
//

#ifndef __ParticleMadness__Particle__
#define __ParticleMadness__Particle__

#include "ofApp.h"

class particle {

public:
    particle();
    particle(ofVec2f pos, ofVec2f vel, ofColor col);
    void draw();
    void drawR(float r);
    void update();
    void applyForces();

    ofVec2f position, velocity;
    ofColor color;
    bool    destroy;

};


#endif /* defined(__ParticleMadness__Particle__) */
