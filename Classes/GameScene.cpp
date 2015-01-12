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





void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    this->girl->stop();
}

void GameScene::update(float delts) {
    float layer_std_width = 1600.0f;
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float x = this->girl->getPositionX();
    int halfx = int(x/layer_std_width);
    //CCLog(" girl position = %f",x);
    //CCLog(" x/l = %i, count = %i",halfx,this->tile_map_count);
    if (halfx>=this->tile_map_count) {
        CCLog("we do some");

        //this->girl->setVisible(false);
        this->tile_map_count++;
        this->createWorldPart(int(this->tile_map_count*layer_std_width),0);
        auto map_to_delete = this->getChildByName(std::to_string(int((this->tile_map_count-3)*layer_std_width)));
        if (map_to_delete!=NULL) {
            CCLog("we delete some");

            map_to_delete->removeAllChildrenWithCleanup(true);
        }
    }
    //CCLog("vis width  = %f",visibleSize.width);
    //CCLog("or x = %f",x);

}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){
       this->girl->action(keyCode);
       if (keyCode==EventKeyboard::KeyCode::KEY_SPACE) {
           this->girl->say("FUCK!!! SHIT!!!11");
           //this->setScale(5);

           //this->setAnchorPoint(this->girl->getPosition());
           /*
           auto _bg2 = this->_tileMap->layerNamed("l2");

           for ( int y = 0; y < _bg2->getLayerSize().height; y++) {
               for (int x = 0; x < _bg2->getLayerSize().width; x++){
                   if (_bg2->tileAt(Vec2(x,y)) == NULL) {
                      //CCLog("Tile is NULL");
                   } else {
                       auto _s_body = PhysicsBody::createBox(Size(16,16),PhysicsMaterial(100.0f, 0.0f, 0.0f));
                      _s_body->setDynamic(true);
                      _bg2->tileAt(Vec2(x,y))->setPhysicsBody(_s_body);
                      _bg2->tileAt(Vec2(x,y))->setTag(99);
                   }
               }
           }
        */

       }

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
    this->scheduleUpdate();
    this->setColor(ccc3(255,0,0));


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




    this->girl = new Girl();
    this->girl->setPosition(300,1200);
    //this->girl->born();
    this->createWorldPart(0,0);
    //this->girl->setScale(0.2);

    this->runAction(Follow::create(this->girl));
  //this->addChild(_bg1);


    this->addChild(this->girl, 1);
    //auto v =  this->getScene()->getPhysicsWorld()->fo
    return true;
}

void GameScene::createPhysicsObjectsOnTileLayer(TMXLayer* l) {
    for ( int y = 0; y < l->getLayerSize().height; y++) {
        for (int x = 0; x < l->getLayerSize().width; x++){
            if (l->tileAt(Vec2(x,y)) == NULL) {
               //CCLog("Tile is NULL");
            } else {
                auto _s_body = PhysicsBody::createBox(Size(16,16),PhysicsMaterial(100.0f, 20.0f, -20.0f));
                _s_body->setDynamic(false);
                l->tileAt(Vec2(x,y))->setPhysicsBody(_s_body);
            }
        }
    }
}

void GameScene::createWorldPart(int x =0, int y = 0) {
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto _tileMap =  CCTMXTiledMap::create("tile_map_4.tmx");
    _tileMap->setName(std::to_string(x));
    _tileMap->setScale(3);
    auto _bg1 = _tileMap->layerNamed("l1");
    //if (x==0)
    this->createPhysicsObjectsOnTileLayer(_bg1);
    _tileMap->setPosition(Vec2(x,y));

    this->addChild(_tileMap);

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
