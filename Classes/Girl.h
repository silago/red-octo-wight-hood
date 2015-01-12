#ifndef __GIRL_H__
#define __GIRL_H__

#include "cocos2d.h"
#include "chipmunk.h"

//USING_NS_CC;
using namespace cocos2d;




class Girl : public cocos2d::Sprite
{
public:
    //  bool createGirl();
    Girl();

    static cocos2d::Sprite* createGirl();
    //void walk();
    bool isMoving = false;
    void action(EventKeyboard::KeyCode keyCode);
    void stop();
    void walkAnimation();
    void say(std::string text);

};

#endif // __HELLOWORLD_SCENE_H__
