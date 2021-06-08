#ifndef ANIMATIONS_HPP
#define ANIMATIONS_HPP

struct Animation{

    int speed;
    int index;
    int frames;
    int x;
    int y;

    Animation(){}
    Animation(int i, int f, int s, int startX, int Y)
    {
        index = i;
        frames = f;
        speed = s;
        x = startX;
        y = Y;
    }

};

#endif