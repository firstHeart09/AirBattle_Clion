//
// Created by 12744 on 2023/4/6.
//

#include "DoubleList.h"

//˫����Ķ���
DoubleList* DoubleList_Init(){
    //������ʱָ�룬ָ��˫����Ľṹ��
    DoubleList* temp = (DoubleList*)malloc(sizeof(DoubleList));
    //ʹ�ö��ԣ��ж�����ռ��Ƿ�ɹ�
    assert(temp);//�ɹ���������򣬷����������
    temp->Head = temp->End = nullptr;
    temp->length = 0;
    return temp;
}

//˫����ڵ�Ķ���
Node* DoubleListNode_Init(){
    //������ʱָ�룬ָ���µĽڵ�
    Node* temp = (Node*)malloc(sizeof(Node));
    assert(temp);//���ԣ��ж�����ռ��Ƿ�ɹ�
    temp->x = 0;
    temp->y = 0;
    temp->prev = temp->pNext = nullptr;
    return temp;
}

//˫����Ĳ���
void DoubleList_Insert(DoubleList*temp,Node*node){
    //����Ŀ�У���˫�����ͷ����������
    if(nullptr == temp->Head){
        //˵����ʱ˫������Ϊ�գ�Ҳ����Ҫ�����һ������
        temp->Head = node;
        temp->End = temp->Head;
    } else {
        //˵����ʱ˫�������Ѿ���Ԫ����
        DoubleListNode_Link(node,temp->Head);
        temp->Head = node;
    }
    temp->length++;
}

//˫����ڵ������
void DoubleListNode_Link(Node*n1,Node*n2){
    n1->pNext = n2;
    n2->prev = n1;
}

//˫�����ɾ��
void DoubleList_Delete(DoubleList*temp,Node*node){
    //�����ж�˫�����Ƿ�Ϊ��
    assert(temp->Head);
    //�ж�Ҫɾ���ڵ��λ��
    if(node == temp->Head){
        //˵����ʱɾ������ͷ���
        Node*n = temp->Head;//������ʱָ�룬ָ��Ҫɾ���Ľڵ�
        temp->Head = n->pNext;//ͷָ��ָ��ɾ���ڵ����һ���ڵ�
        //�жϴ�ʱ˫�������Ƿ��нڵ�
        if(nullptr == temp->Head){
            //˵����ʱ˫������û��Ԫ���ˣ���ʱ��Ҫ�޸�βָ��ָ��
            temp->End = nullptr;
        } else {
            //˵����ʱ˫�����л���Ԫ�أ���ʱ��Ҫ�޸�ͷָ��ָ��ڵ��ǰ��ָ��
            temp->Head->prev = nullptr;
        }
        free(n);
    } else if(node == temp->End){
        //˵����ʱɾ������β���
        Node*n = temp->End;//������ʱָ�룬ָ��ɾ���ڵ�
        temp->End = n->prev;//βָ��ָ��ɾ���ڵ��ǰһ���ڵ�
        //�жϴ�ʱ˫�������Ƿ���Ԫ��
        if(nullptr == temp->Head){
            //˵����ʱ�Ѿ�û��Ԫ�أ���Ҫ�޸�ͷָ���ָ��
            temp->Head = nullptr;
        } else {
            //˵����ʱ����Ԫ�أ���Ҫ�޸�βָ��ָ��ڵ�ĺ��ָ��
            temp->End->pNext = nullptr;
        }
        free(n);
    } else {
        //ɾ�������м�ڵ�
        DoubleListNode_Link(node->prev,node->pNext);
        free(node);
    }
    temp->length--;
}

//˫���������
void DoubleList_Destroy(DoubleList*temp){
    assert(temp->Head);
    Node*n = temp->Head;//������ʱָ�룬ָ��ɾ���ڵ�
    while(nullptr != n){
        Node*e = n;
        n = n->pNext;
        free(e);
    }
    //��ʱ�Ѿ�ɾ����˫���������нڵ㣬ֻʣ��˫����ṹ��ռ�
    temp->Head = temp->End = nullptr;
    temp->length = 0;
    free(temp);
}

