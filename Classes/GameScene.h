#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "Girl.h"
//#include "GameLayer.h"

//USING_NS_CC;
using namespace cocos2d;




class GameScene : public cocos2d::Layer
{
public:
     PhysicsWorld *world;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    cpSpace* space;
    CCTMXTiledMap* _tileMap;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void onTouch();
    void girlWalk();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setPhyWorld(PhysicsWorld* world){this->world = world;}
    void createWorldPart(int x, int y);
    void createPhysicsObjectsOnTileLayer(cocos2d::TMXLayer* l);
    Girl* girl;
    int tile_map_count = 0;
    bool isGirlMoving = false;
    void update(float delts);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

    //GameLayer* _game_layer ;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);


    private:
        PhysicsWorld* m_worVld;
};

#endif // __HELLOWORLD_SCENE_H__
