#ifndef ANIMATIONS_HPP
#define ANIMATIONS_HPP

struct Animation{

    int speed;
    int index;
    int frames;

    Animation(){}
    Animation(int i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
    }

};

#endif