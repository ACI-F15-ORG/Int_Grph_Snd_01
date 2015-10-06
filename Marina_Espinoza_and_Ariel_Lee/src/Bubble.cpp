#include "Bubble.h"

// Constructor - only the image is specified.
Bubble::Bubble(ofImage  img, ofSoundPlayer sd) {
    image = img;
    pop_sd = sd;
    img_ratio = ofRandom(0.2,1.0);
    image.resize(image.getHeight() * img_ratio, image.getWidth() * img_ratio );
    position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    velocity = ofVec2f(ofRandom(-8,8),ofRandom(-8,8));
    color.r = ofRandom( 0, 255 );
    color.g = ofRandom( 0, 255 );
    color.b = ofRandom( 0, 255 );
    speed_sd = float(color.getHex() ) / ((0xffffff) / 2) ;
    std::cout << speed_sd << std::endl;
}

bool Bubble::isOffScreen(){
    int radius = image.getHeight()/2;
    int leftmost = position.x - radius;
    int rightmost = position.x + radius;
    int uppermost = position.y - radius;
    int bottommost = position.y + radius;

    return (uppermost > ofGetHeight()) || (bottommost < 0 ) || (leftmost > ofGetWidth() || (rightmost < 0));
}

ofColor Bubble::getColor(){
    return color;
}

//Mutators
void Bubble::update(){
    velocity.x *= .99;
    velocity.y *= .99;
    position.x += velocity.x;
    position.y += velocity.y;

}

//Call back
void Bubble::draw() {
    ofSetColor( color );
    image.draw(position.x, position.y);
}

//Event Listener
bool Bubble::onClick(int x, int y){
    float radius = image.getHeight()/2;
    float current_dist = ofDist(x,y,position.x, position.y);
    if ( current_dist <= radius ){
        pop_sd.play();
        pop_sd.setSpeed(speed_sd);
        pop_sd.setVolume(img_ratio);
        return true;
    }
    return false;
}
