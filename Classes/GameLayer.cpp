//
//  GameLayer.cpp
//  Scales
//
//  Created by 吉田　理貴 on 2015/06/15.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

//コンストラクタ
GameLayer::GameLayer()
{
}

// シーンの生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto audio = SimpleAudioEngine::getInstance();
    audio->preloadEffect("scales/do.mp3");
    audio->preloadEffect("scales/re.mp3");
    audio->preloadEffect("scales/mi.mp3");
    audio->preloadEffect("scales/fa.mp3");
    audio->preloadEffect("scales/so.mp3");
    audio->preloadEffect("scales/ra.mp3");
    audio->preloadEffect("scales/si.mp3");
    audio->preloadEffect("scales/do+.mp3");
    
    _particlePoolDo = ParticleSystemPool::create("plist/do.plist", 200);
    _particlePoolDo->retain();
    _particlePoolRe = ParticleSystemPool::create("plist/re.plist", 200);
    _particlePoolRe->retain();
    _particlePoolMi = ParticleSystemPool::create("plist/mi.plist", 200);
    _particlePoolMi->retain();
    _particlePoolFa = ParticleSystemPool::create("plist/fa.plist", 200);
    _particlePoolFa->retain();
    _particlePoolSo = ParticleSystemPool::create("plist/so.plist", 200);
    _particlePoolSo->retain();
    _particlePoolRa = ParticleSystemPool::create("plist/ra.plist", 200);
    _particlePoolRa->retain();
    _particlePoolSi = ParticleSystemPool::create("plist/si.plist", 200);
    _particlePoolSi->retain();
    _particlePoolDop = ParticleSystemPool::create("plist/do+.plist", 200);
    _particlePoolDop->retain();

    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void GameLayer::onEnter()
{
    Layer::onEnter();
    
    auto v = Vect(0, -98);
    auto scene = dynamic_cast<Scene*>(this->getParent());
    scene->getPhysicsWorld()->setGravity(v);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    initBackground(); // 背景の初期化
    
    scale_do = initScaleImage("do.png", 40, WINSIZE.height*4/10);
    scale_re = initScaleImage("re.png", 120, WINSIZE.height*6/10);
    scale_mi = initScaleImage("mi.png", 200, WINSIZE.height*4/10);
    scale_fa = initScaleImage("fa.png", 280, WINSIZE.height*6/10);
    scale_so = initScaleImage("so.png", 360, WINSIZE.height*4/10);
    scale_ra = initScaleImage("ra.png", 440, WINSIZE.height*6/10);
    scale_si = initScaleImage("si.png", 520, WINSIZE.height*4/10);
    scale_dop = initScaleImage("do+.png", 600, WINSIZE.height*6/10);
    
}

// 背景の初期化
void GameLayer::initBackground()
{
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    addChild(background, Z_Background, T_Background);
}

Sprite* GameLayer::initScaleImage(std::string image, int x, int y)
{
    auto scale = Sprite::create(image);
    
    // 物質的特徴の設定
    PhysicsMaterial material;
    material.density = 0;
    material.restitution = 0;
    material.friction = 0;
    
    scale->setPosition(x, y);
    auto body = PhysicsBody::createBox(scale->getContentSize(), material);
    body->setDynamic(false);
    scale->setPhysicsBody(body);
    addChild(scale, Z_Scales);
    
    return scale;
}

void GameLayer::createScale(std::string image, Point point, Tag tag)
{
    auto scale = Sprite::create(image);
    scale->setPosition(point);
    scale->setTag(tag);
    
    PhysicsMaterial material;
    material.density = 0.5;
    material.restitution = 0.5;
    material.friction = 0.3;
    
    auto body = PhysicsBody::createCircle(scale->getContentSize().width * 0.47, material);
    body->setDynamic(true);
    body->setContactTestBitmask(1);
    scale->setPhysicsBody(body);
    
    addChild(scale, Z_Scales);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    if (scale_do->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/do.mp3", touch, _particlePoolDo);
        currentTag = T_Scale_Do;
    } else if (scale_re->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/re.mp3", touch, _particlePoolRe);
        currentTag = T_Scale_Re;
    } else if (scale_mi->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/mi.mp3", touch, _particlePoolMi);
        currentTag = T_Scale_Mi;
    } else if (scale_fa->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/fa.mp3", touch, _particlePoolFa);
        currentTag = T_Scale_Fa;
    } else if (scale_so->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/so.mp3", touch, _particlePoolSo);
        currentTag = T_Scale_So;
    } else if (scale_ra->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/ra.mp3", touch, _particlePoolRa);
        currentTag = T_Scale_Ra;
    } else if (scale_si->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/si.mp3", touch, _particlePoolSi);
        currentTag = T_Scale_Si;
    } else if (scale_dop->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/do+.mp3", touch, _particlePoolDop);
        currentTag = T_Scale_Dop;
    }
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
    if (currentTag != T_Scale_Do && scale_do->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/do.mp3", touch, _particlePoolDo);
        currentTag = T_Scale_Do;
    } else if (currentTag != T_Scale_Re && scale_re->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/re.mp3", touch, _particlePoolRe);
        currentTag = T_Scale_Re;
    } else if (currentTag != T_Scale_Mi && scale_mi->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/mi.mp3", touch, _particlePoolMi);
        currentTag = T_Scale_Mi;
    } else if (currentTag != T_Scale_Fa && scale_fa->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/fa.mp3", touch, _particlePoolFa);
        currentTag = T_Scale_Fa;
    } else if (currentTag != T_Scale_So && scale_so->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/so.mp3", touch, _particlePoolSo);
        currentTag = T_Scale_So;
    } else if (currentTag != T_Scale_Ra && scale_ra->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/ra.mp3", touch, _particlePoolRa);
        currentTag = T_Scale_Ra;
    } else if (currentTag != T_Scale_Si && scale_si->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/si.mp3", touch, _particlePoolSi);
        currentTag = T_Scale_Si;
    } else if (currentTag != T_Scale_Dop && scale_dop->getPosition().getDistance(touch->getLocation()) <= SCALE_IMAGE_SIZE/2) {
        showEffect("scales/do+.mp3", touch, _particlePoolDop);
        currentTag = T_Scale_Dop;
    }
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
    currentTag = T_Scale_Empty;
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

void GameLayer::showEffect(std::string soundEffect, Touch* touch, ParticleSystemPool* particlePool)
{
    SimpleAudioEngine::getInstance()->playEffect(soundEffect.c_str());
    auto particle = particlePool->pop();
    particle->setPosition(touch->getLocation());
    this->addChild(particle, Z_Particle, T_Particle);
}
