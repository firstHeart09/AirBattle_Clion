//
// Created by 12744 on 2023/4/6.
//

#include "DoubleList.h"

//双链表的定义
DoubleList* DoubleList_Init(){
    //定义临时指针，指向双链表的结构体
    DoubleList* temp = (DoubleList*)malloc(sizeof(DoubleList));
    //使用断言：判断申请空间是否成功
    assert(temp);//成功则继续程序，否则结束程序
    temp->Head = temp->End = nullptr;
    temp->length = 0;
    return temp;
}

//双链表节点的定义
Node* DoubleListNode_Init(){
    //定义临时指针，指向新的节点
    Node* temp = (Node*)malloc(sizeof(Node));
    assert(temp);//断言：判断申请空间是否成功
    temp->x = 0;
    temp->y = 0;
    temp->prev = temp->pNext = nullptr;
    return temp;
}

//双链表的插入
void DoubleList_Insert(DoubleList*temp,Node*node){
    //此项目中，在双链表的头部插入数据
    if(nullptr == temp->Head){
        //说明此时双链表中为空，也就是要插入第一个数据
        temp->Head = node;
        temp->End = temp->Head;
    } else {
        //说明此时双链表中已经有元素了
        DoubleListNode_Link(node,temp->Head);
        temp->Head = node;
    }
    temp->length++;
}

//双链表节点的连接
void DoubleListNode_Link(Node*n1,Node*n2){
    n1->pNext = n2;
    n2->prev = n1;
}

//双链表的删除
void DoubleList_Delete(DoubleList*temp,Node*node){
    //首先判断双链表是否为空
    assert(temp->Head);
    //判断要删除节点的位置
    if(node == temp->Head){
        //说明此时删除的是头结点
        Node*n = temp->Head;//定义临时指针，指向要删除的节点
        temp->Head = n->pNext;//头指针指向被删除节点的下一个节点
        //判断此时双链表中是否还有节点
        if(nullptr == temp->Head){
            //说明此时双链表中没有元素了，此时需要修改尾指针指向
            temp->End = nullptr;
        } else {
            //说明此时双链表中还有元素，此时需要修改头指针指向节点的前驱指针
            temp->Head->prev = nullptr;
        }
        free(n);
    } else if(node == temp->End){
        //说明此时删除的是尾结点
        Node*n = temp->End;//定义临时指针，指向被删除节点
        temp->End = n->prev;//尾指针指向被删除节点的前一个节点
        //判断此时双链表中是否还有元素
        if(nullptr == temp->Head){
            //说明此时已经没有元素，需要修改头指针的指向
            temp->Head = nullptr;
        } else {
            //说明此时还有元素，需要修改尾指针指向节点的后继指针
            temp->End->pNext = nullptr;
        }
        free(n);
    } else {
        //删除的是中间节点
        DoubleListNode_Link(node->prev,node->pNext);
        free(node);
    }
    temp->length--;
}

//双链表的销毁
void DoubleList_Destroy(DoubleList*temp){
    assert(temp->Head);
    Node*n = temp->Head;//定义临时指针，指向被删除节点
    while(nullptr != n){
        Node*e = n;
        n = n->pNext;
        free(e);
    }
    //此时已经删除完双链表中所有节点，只剩下双链表结构体空间
    temp->Head = temp->End = nullptr;
    temp->length = 0;
    free(temp);
}

