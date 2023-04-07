//
// Created by 12744 on 2023/4/6.
//

#include "AirPlay.h"
/*
 * ȫ�ֱ���
 */
//�����Ŀ����
int hei = 600;
int wid = 360;
//�л�˫����
DoubleList* enemyList;
//�ӵ�����
DoubleList* bulletList;
//�ӵ��Ĵ�С
#define bulletSize 10
//�ɻ���л��Ĵ�С
#define planeSize 40
//�ӵ��͵л������������ͬһ�Ż����ϣ�
#define enemyBulletSize 20
//����image���飬��������Ҫ��ͼ��ͼƬ��Դ
IMAGE image[4];
//����ɻ��ṹ��
Node player = {0,0};
//����
int grade = 0;
//�����ڻ���ɻ�һ������ʱ���л��ƶ��ٶȼӿ�
static int planeCount = 0;
int planeCount1 = 20;//���û���20���ٶȼӿ�
static int planeSpeed = 10;//�����ٶ�Ϊ10
int bulletPlaneSpeed = 5;//�л����ӵ��ĳ�ʼ�ٶ�

//�ɻ������ĳ�ʼ������������ͼƬ��Դ��
void Init(){
    initgraph(wid,hei);
    //��Ҫʹ��c�����ṩ���������
    srand((unsigned )time(nullptr));
    //����ͼƬ��Դ�����������ͼʹ��
    loadimage(&image[background],R"(E:\CC++\Project\AirBattle_Clion\res\5.jpg)",
              wid,hei,false);
    loadimage(&image[plane],R"(E:\CC++\Project\AirBattle_Clion\res\2.jpg)",
              planeSize,planeSize, false);
    loadimage(&image[enemy],R"(E:\CC++\Project\AirBattle_Clion\res\1.jpg)",
              planeSize,planeSize, false);
    loadimage(&image[bullet],R"(E:\CC++\Project\AirBattle_Clion\res\3.jpg)",
              bulletSize,bulletSize, false);
    //��ʼ���ɻ���λ��
    player = {(wid/2)-(planeSize/2),hei-planeSize};
    //��ʼ���ӵ�����͵л�����
    bulletList = DoubleList_Init();
    enemyList = DoubleList_Init();
}

//������Ϸ�������ɻ���л���
void Draw(){
    //ʹ��������ͼ
    BeginBatchDraw();
    //��ͼ����Init�����м��ص�ͼƬ��Դ���ڻ�����
    putimage(0,0,&image[background]);//������ͼ
    //�������еĵл�
    for(Node*temp=enemyList->Head;temp!= nullptr;temp=temp->pNext){
        putimage(temp->x,temp->y,&image[enemy]);
    }
    //�������е��ӵ�
    for(Node*temp=bulletList->Head;temp!= nullptr;temp=temp->pNext){
        putimage(temp->x, temp->y,&image[bullet]);
    }
    putimage(player.x,player.y,&image[plane]);//���ɻ�

    //�ڽ������Ͻ���ʾ��ǰ�÷�
    setbkmode(TRANSPARENT);//��ʾ͸������
    settextcolor(RED);
    settextstyle(20,0,"����");
    TCHAR str[10];
    wsprintf(str,"�÷֣�%d",grade);
    outtextxy(0,0,str);
    //����������ͼ
    EndBatchDraw();
}

//��Ϸ�߼�
void Start(){
    Init();
    Draw();
    while(1){
        PlaneControl();//���Ʒɻ��ƶ�
        Update();//���µл����ӵ���λ��
        Draw();
        if(IsGameOver()){
            //��ʱ��Ϸ�Ѿ���������Ҫʹ�õ�������
            TCHAR str[50];
            wsprintf(str,"��Ϸ�Ѿ����������ĵ÷�Ϊ��%d",grade);
            if(MessageBox(GetHWnd(),str,"��ʾ��",MB_YESNO) == IDYES){
                //��ʱѡ����Ǽ�����Ϸ
                //�����ӵ�����͵л�����
                //������ǰ��Ҫ�жϣ���ǰ�������ӵ�����͵л��������Ƿ��нڵ�
                if(bulletList->length != 0){
                    DoubleList_Destroy(bulletList);
                }
                if(enemyList->length != 0){
                    DoubleList_Destroy(enemyList);
                }
                grade = 0;
                Init();
                Draw();

            } else {
                exit(0);
            }
        }
        Sleep(20);
    }
}

//�ɻ����ƶ�
void PlaneControl(){
    //ͨ�������ϵİ������Ʒɻ����ƶ�
    int speed = 5;//�ɻ�ÿ�ΰ����ƶ������ص�
    //GetAsyncKeyState��ȡ�����ϵİ���
    if(GetAsyncKeyState(VK_UP)){
        //��ʱ���µ��Ǽ����ϵ��ϼ�
        if(player.y > 0){
            player.y -= speed;//ÿ��һ�Σ���������ƶ�8�����ص�
        }
    }
    if(GetAsyncKeyState(VK_DOWN)){
        //��ʱ���µ��Ǽ����ϵ��¼�
        if(player.y < hei-planeSize){
            player.y += speed;//ÿ��һ�Σ���������ƶ�8�����ص�
        }
    }
    if(GetAsyncKeyState(VK_LEFT)){
        //��ʱ���µ��Ǽ����ϵ����
        if(player.x > 0){
            player.x -= speed;//ÿ��һ�Σ���������ƶ�8�����ص�
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        //��ʱ���µ��Ǽ����ϵ��Ҽ�
        if(player.x < wid-planeSize){
            player.x += speed;//ÿ��һ�Σ���������ƶ�8�����ص�
        }
    }
    if(_kbhit()){//���¿ո������ӵ�
        int key = getch();
        if(key == ' '){
            SpawnBullet();
        }
    }
}

//�ӵ�����
void SpawnBullet(){
    //ͨ�����¼����ϵĿո�����ڷɻ��м������ӵ�
    if(bulletList->length < enemyBulletSize){//������Ҫ�жϵ�ǰҳ�����ж����ӵ�
        int x = player.x + planeSize/2-bulletSize/2;
        int y = player.y;
        Node*temp = DoubleListNode_Init(x,y);
        DoubleList_Insert(bulletList,temp);
    }
}

//�л�������
void SpawnEnemy(){
    //�л��ӻ������������������
    static int count = 0;
    if(count >= 30){
        //ÿ30�β���һ���л�
        //��ʱ��Ҫ�жϵл��ĸ����Ƿ�С���������
        if(enemyList->length < enemyBulletSize){
            //��ʱ�����л�
            Node*temp = DoubleListNode_Init(rand()%(wid-planeSize),0-planeSize);
            DoubleList_Insert(enemyList,temp);
        }
        count = 0;
    }
    count++;
}

//�л����ӵ����ƶ�:��������,ÿ���ƶ�����Ҫ�ж��Ƿ�Խ���Լ��Ƿ���ײ
void Update(){
    //����������ÿһ���ڵ㣬�ƶ�������
    //�ƶ��л�
    if(planeCount  >= planeCount1){
        for(Node*temp = enemyList->Head;temp!= nullptr;temp=temp->pNext){
            temp->y += planeSpeed;//ÿ��ˢ�£��л��ƶ�5�����ص�
        }
        planeCount = 0;
        planeSpeed += 10;
    } else {
        for(Node*temp = enemyList->Head;temp!= nullptr;temp=temp->pNext){
            temp->y += bulletPlaneSpeed;//ÿ��ˢ�£��л��ƶ�5�����ص�
        }
    }

    //�ƶ��ӵ�
    for(Node*temp=bulletList->Head;temp!= nullptr;temp=temp->pNext){
        temp->y -= bulletPlaneSpeed;
    }
    SpawnEnemy();//���ɵл�
    Destroy();//�ж��Ƿ���Խ�磬�Ƿ���Ҫ����
    BoomCollide();//�ж��ƶ����ӵ��͵л�����û����ײ
}

//�ӵ��͵л���Խ������
void Destroy(){
    //�л���Խ������
    Node*e = enemyList->Head;
    while(e!= nullptr){
        if(e->y >= hei){
            Node*temp = e;//������ʱָ�룬ָ��ɾ���ڵ�
            e = e->pNext;
            DoubleList_Delete(enemyList,temp);
        } else {
            e = e->pNext;
        }
    }

    //�ӵ���Խ������
    Node*b=bulletList->Head;
    while(b!= nullptr){
        if(b->y <= 0){
            Node*temp = b;//������ʱָ�룬ָ��ɾ���ڵ�
            b = b->pNext;
            DoubleList_Delete(bulletList,temp);
        } else {
            b = b->pNext;
        }
    }
}

//ʵ����ײ�߼����ӵ���л�����ײ
bool BulletBoom(Node*n1,Node*n2){//n1���ӵ�   n2�ǵл�
    //����������ʱ���������������ڵ�x��y���ϵľ���
    int x = abs((n1->x+bulletSize/2)-(n2->x+planeSize/2));//ʹ�����ĵ����ж�
    //�ӵ����ĵ����� - �л����ĵ�����
    int y = abs(n1->y - n2->y);
    return (x <= (bulletSize/2+planeSize/2)) && (y <= planeSize);
    //����ӵ��ͽڵ���ײ����true�����򷵻�false
}

//��ײ��Ĵ����л����ӵ�
void BoomCollide(){
    for(Node*b=bulletList->Head;b!= nullptr;b=b->pNext){
        for(Node*e=enemyList->Head;e!= nullptr;e=e->pNext){
            if(BulletBoom(b,e)){
                //���������ײ������Ҫɾ����ײ�Ľڵ�
                DoubleList_Delete(enemyList,e);
                DoubleList_Delete(bulletList,b);
                grade += 10;
                planeCount++;
                return;
            }
        }
    }
}

//ʵ����ײ�߼����л����ҷ��ɻ�����ײ
bool PlaneBoom(Node*n1,Node*n2){
    //����x���y���ϵľ���
    int x = abs(n1->x - n2->x);
    int y = abs(n1->y - n2->y);
    return (x<=planeSize && y<=planeSize);
}

//��Ϸ�Ƿ����
bool IsGameOver(){
    for(Node*e = enemyList->Head;e!= nullptr;e=e->pNext){
        if(PlaneBoom(e,&player)){
            //˵����ʱ�ɻ���л��Ѿ���ײ����Ϸ������
            return true;
        }
    }
    return false;
}