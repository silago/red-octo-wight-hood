#include "Girl.h"

USING_NS_CC;

Sprite* Girl::createGirl()
{

}



Girl::Girl(){
    //Sprite r = Sprite::create("girl.png");
    this->initWithFile("girl.png");
    //this->setScale(1);
    auto girl_physical_body = PhysicsBody::createBox(this->getBoundingBox().size,PhysicsMaterial(100.0f, 0.0f, 0.0f));
    this->setPhysicsBody(girl_physical_body);
    //this->get;
    this->getPhysicsBody()->setRotationEnable(false);
    return;// Sprite;
}

void Girl::say(std::string text){

    CCLabelTTF* ttf1 = CCLabelTTF::create(text, "Helvetica", 16,
                                          CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->addChild(ttf1);
    ttf1->setPositionY(this->getBoundingBox().size.height);
    //this->addChild

}



void Girl::stop() {
        if (!this->isMoving) {
        return;
    }

    this->stopAllActionsByTag(1);
    this->isMoving = false;
}

void Girl::action(EventKeyboard::KeyCode keyCode) {
    int x_move = 0;
    int y_move = 0;
    this->setRotation(0);
    if (this->isMoving) {
   //     return;
    }

    this->isMoving = true;

    if (keyCode==EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        x_move = -1500;
    }
    else if (keyCode==EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        x_move =  1500;

    } else if  (keyCode==EventKeyboard::KeyCode::KEY_UP_ARROW) {
       y_move = 1020;
    } else return;

    //CCRepeatForever::create(actionMove)

    auto actionMove = CCRepeatForever::create(CCMoveBy::create(10,Vect(x_move,y_move)));
    actionMove->setTag(1);

    this->runAction( actionMove);
    this->walkAnimation();
}

void Girl::walkAnimation(){
    char str2[100] = {0};

    //sprintf(str2, "%d",this->getRotation());
    CCLog(str2);
    Vector<SpriteFrame*> animFrames(4);
    char str[100] = {0};
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "gs/girl%d.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,this->getBoundingBox().size.width,this->getBoundingBox().size.height)); //we assume that the sprites' dimentions are 40*40 rectangles.
        animFrames.pushBack(frame);
    }

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = CCRepeatForever::create(Animate::create(animation));
    animate->setTag(1);
    this->runAction(animate);
}


