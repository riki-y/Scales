//
//  GameLayer.h
//  Scales
//
//  Created by 吉田　理貴 on 2015/06/15.
//
//

#ifndef __Scales__GameLayer__
#define __Scales__GameLayer__

#include "cocos2d.h"
#include "ParticleSystemPool.h"

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ
#define SCALE_IMAGE_SIZE 60 // 音階画像のサイズ

class GameLayer : public cocos2d::Layer
{
protected:
    // タグ
    enum Tag
    {
        T_Background,
        T_Scale_Do,
        T_Scale_Re,
        T_Scale_Mi,
        T_Scale_Fa,
        T_Scale_So,
        T_Scale_Ra,
        T_Scale_Si,
        T_Scale_Dop,
        T_Scale_Empty,
        T_Particle,
    };
    
    // Zオーダー
    enum ZOreder
    {
        Z_Background,
        Z_Scales,
        Z_Particle,
    };
    
    void initBackground(); // 背景の初期化
    cocos2d::Sprite* initScaleImage(std::string image, int x, int y); // 音階の画像を初期化
    void createScale(std::string image, cocos2d::Point point, Tag tag);
    
    cocos2d::Sprite* scale_do;
    cocos2d::Sprite* scale_re;
    cocos2d::Sprite* scale_mi;
    cocos2d::Sprite* scale_fa;
    cocos2d::Sprite* scale_so;
    cocos2d::Sprite* scale_ra;
    cocos2d::Sprite* scale_si;
    cocos2d::Sprite* scale_dop;
    
    ParticleSystemPool* _particlePoolDo;
    ParticleSystemPool* _particlePoolRe;
    ParticleSystemPool* _particlePoolMi;
    ParticleSystemPool* _particlePoolFa;
    ParticleSystemPool* _particlePoolSo;
    ParticleSystemPool* _particlePoolRa;
    ParticleSystemPool* _particlePoolSi;
    ParticleSystemPool* _particlePoolDop;
    
public:
    GameLayer(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GameLayer); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    virtual void onEnter(); // レイヤー表示処理
    void showEffect(std::string soundEffect, cocos2d::Touch* touch, ParticleSystemPool* particlePool); // エフェクト表示
    Tag currentTag;
    
    // シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__Scales__GameLayer__) */
