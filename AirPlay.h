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

//ö������   ��������Ҫ��ͼ�ı������±�
enum Air{
    background,
    plane,
    enemy,
    bullet
};

//�ɻ���ս�ĺ�������
//�ɻ������ĳ�ʼ��������
void Init();

//������Ϸ�������ɻ���л���
void Draw();

//��Ϸ�߼�
void Start();

//�ɻ����ƶ�
void PlaneControl();

//�ӵ�����
void SpawnBullet();

//�л�������
void SpawnEnemy();

//�л����ӵ����ƶ�:��������
void Update();

//�ӵ��͵л���Խ������
void Destroy();

//ʵ����ײ�߼����ӵ���л�����ײ
bool BulletBoom(Node*n1,Node*n2);

//ʵ����ײ�߼����л����ҷ��ɻ�����ײ
bool PlaneBoom(Node*n1,Node*n2);

//��ײ��Ĵ���
void BoomCollide();

//��Ϸ�Ƿ����
bool IsGameOver();


#endif //AIRBATTLE_CLION_AIRPLAY_H
