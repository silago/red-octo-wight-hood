#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,-200));
    //scene->getPhysicsWorld()->set

    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance

//void HelloWorld::ccTouchEnded(Touch *pTouch, Event *pEvent){
//}

void GameScene::girlWalk(){
//    /return;
    Vector<SpriteFrame*> animFrames(4);
    char str[100] = {0};
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "gs/girl%d.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,150,214)); //we assume that the sprites' dimentions are 40*40 rectangles.
        animFrames.pushBack(frame);
    }

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = CCRepeatForever::create(Animate::create(animation));
    animate->setTag(1);
    this->girl->runAction(animate);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    CCLog("key released");
    if (!this->isGirlMoving) {
        return;
    }

    this->girl->stopAllActionsByTag(1);
    //this->girl->stopA
    this->isGirlMoving = false;
    CCLog("key released - all stopped");
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){
    int x_move = 0;
    int y_move = 0;
    this->girl->setRotation(0);
    if (this->isGirlMoving) {
   //     return;
    }

    this->isGirlMoving = true;

    if (keyCode==EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        x_move = -2500;
    }
    else if (keyCode==EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        x_move =  2500;

    } else if  (keyCode==EventKeyboard::KeyCode::KEY_UP_ARROW) {
       y_move = 6200;
    } else return;

    //CCRepeatForever::create(actionMove)

    auto actionMove = CCRepeatForever::create(CCMoveBy::create(10,Vect(x_move,y_move)));
    actionMove->setTag(1);

    this->girl->runAction( actionMove);
    this->girlWalk();

}

void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    return;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    auto key_listener = EventListenerKeyboard::create();
         key_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
         key_listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);


    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);


    //this->getEventDispatcher()->addCustomEventListener()


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    /* create floor */
       // auto block = Sprite::create("white_block.png");
       // auto block_physical_body = PhysicsBody::createBox(block->getContentSize());
       // block_physical_body->setGravityEnable(false);
       // block_physical_body->setDynamic(false);
       // block->setPhysicsBody(PhysicsBody::createBox(Size(16,16)));
       // block->setPosition(Vec2(visibleSize.width/2 + origin.x,200));
       // this->addChild(block, 0);

    //auto bg = Sprite::create("bg.png");
    //bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(bg,0);

    /* girl sprite */
    //this->girl = Sprite::create("girl.png");
    this->girl = Sprite::create();
    this->girl->setScale(0.25);
    auto girl_physical_body = PhysicsBody::createBox(Size(37,53));


    //this->girl->setScale(0.5);
    this->girl->setPhysicsBody(girl_physical_body);
    //this->girl->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + 200+origin.y));
    //this->girlWalk();
        this->runAction(Follow::create(this->girl));
    //girl_physical_body->setGravityEnable(false);

    /* wolf */
    //auto wolf = Sprite::create("wolf.png");
    //wolf->setPosition(Vec2(90,90));
    //2this->addChild(wolf,2);

     auto _tileMap =  CCTMXTiledMap::create("tile_map.tmx");
     //_tileMap->initWithTMXFile("tile_map.tmx");
     //_tileMap->initWithTMXFile("tile_map.tmx");
     auto _bg1 = _tileMap->layerNamed("l1");
     //_bg1->setVisible(false);
     //auto tiles_phys = CCArray::create();
     //Sprite* tiles_phys[][99];
     //char str[100] = {0};
     for ( int y = 0; y < _bg1->getLayerSize().height; y++) {
         for (int x = 0; x < _bg1->getLayerSize().width; x++){
             if (_bg1->tileAt(Vec2(x,y)) == NULL) {
                CCLog("Tile is NULL");
             } else {
                // auto _s = Sprite::create("red.png");
                  auto _s_body = PhysicsBody::createBox(Size(100,100));
                 //_s_body->c
                 //_s_body->setGravityEnable(false);
                 //_s->setOpacity(00);
                 //_s->setPosition(Vect(x*16+60,y*-16+560));
                 //_s->setPhysicsBody(_s_body);
                 _s_body->setDynamic(false);

                 _bg1->tileAt(Vec2(x,y))->setPhysicsBody(_s_body);
                 //sprintf(str, "%dx%d",x,y);
                 //tiles_phys[x*y]->setName(  str );
                 //tiles_phys[x*y]->setPosition(Vect(x,y));
                 //this->addChild(_s,99);

              //   tiles_phys.
                 //tiles_phys->addObject(PhysicsBody::createBox(Size(16,16)));
                 //tiles_phys->lastObject()
                 //CCLog("Tile is not NULL");
             }
         }
     }













     _tileMap->setPosition(Vec2(visibleSize.width/2 -430, visibleSize.height/2 + origin.y- 410));
     //_bg1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

     this->addChild(_tileMap);
     //this->addChild(_bg1);



    this->addChild(this->girl, 1);
    //auto v =  this->getScene()->getPhysicsWorld()->fo
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
