//
// Created by 12744 on 2023/4/6.
//

#ifndef AIRBATTLE_CLION_DOUBLELIST_H
#define AIRBATTLE_CLION_DOUBLELIST_H

#include <cstdio>
#include <cstdlib>
#include <cassert>

//双链表中每个节点定义
struct Node{
    //由于每个节点需要保存位置，所以需要定义x与y两个数据
    int x;
    int y;
    struct Node*pNext;//后继指针
    struct Node*prev;//前驱指针
};
typedef struct Node Node;
//双链表结构体定义
struct DoubleList{
    int length;//保存双链表的节点个数
    Node*Head;//保存头结点的指针
    Node*End;//保存尾结点的指针
};
typedef struct DoubleList DoubleList;

//双链表函数定义
//双链表的定义
DoubleList* DoubleList_Init();

//双链表节点的定义
Node* DoubleListNode_Init();

//双链表的插入
void DoubleList_Insert(DoubleList*temp,Node*node);

//双链表节点的连接
void DoubleListNode_Link(Node*n1,Node*n2);

//双链表的删除
void DoubleList_Delete(DoubleList*temp,Node*node);

//双链表的销毁
void DoubleList_Destroy(DoubleList*temp);

#endif //AIRBATTLE_CLION_DOUBLELIST_H
