//
// Created by 12744 on 2023/4/6.
//

#ifndef AIRBATTLE_CLION_DOUBLELIST_H
#define AIRBATTLE_CLION_DOUBLELIST_H

#include <cstdio>
#include <cstdlib>
#include <cassert>

//˫������ÿ���ڵ㶨��
struct Node{
    //����ÿ���ڵ���Ҫ����λ�ã�������Ҫ����x��y��������
    int x;
    int y;
    struct Node*pNext;//���ָ��
    struct Node*prev;//ǰ��ָ��
};
typedef struct Node Node;
//˫����ṹ�嶨��
struct DoubleList{
    int length;//����˫����Ľڵ����
    Node*Head;//����ͷ����ָ��
    Node*End;//����β����ָ��
};
typedef struct DoubleList DoubleList;

//˫����������
//˫����Ķ���
DoubleList* DoubleList_Init();

//˫����ڵ�Ķ���
Node* DoubleListNode_Init();

//˫����Ĳ���
void DoubleList_Insert(DoubleList*temp,Node*node);

//˫����ڵ������
void DoubleListNode_Link(Node*n1,Node*n2);

//˫�����ɾ��
void DoubleList_Delete(DoubleList*temp,Node*node);

//˫���������
void DoubleList_Destroy(DoubleList*temp);

#endif //AIRBATTLE_CLION_DOUBLELIST_H
