//
// Created by 12744 on 2023/4/6.
//

#ifndef AIRBATTLE_CLION_AIRPLAY_H
#define AIRBATTLE_CLION_AIRPLAY_H

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <easyx.h>
#include <ctime>
#include <conio.h>
#include <math.h>
#include "DoubleList.h"

//枚举类型   保存我们要贴图的背景的下标
enum Air{
    background,
    plane,
    enemy,
    bullet
};

//飞机大战的函数定义
//飞机函数的初始化函数：
void Init();

//绘制游戏背景、飞机与敌机等
void Draw();

//游戏逻辑
void Start();

//飞机的移动
void PlaneControl();

//子弹生成
void SpawnBullet();

//敌机的生成
void SpawnEnemy();

//敌机与子弹的移动:更新数据
void Update();

//子弹和敌机的越界销毁
void Destroy();

//实现碰撞逻辑：子弹与敌机的碰撞
bool BulletBoom(Node*n1,Node*n2);

//实现碰撞逻辑：敌机和我方飞机的碰撞
bool PlaneBoom(Node*n1,Node*n2);

//碰撞后的处理
void BoomCollide();

//游戏是否结束
bool IsGameOver();


#endif //AIRBATTLE_CLION_AIRPLAY_H
