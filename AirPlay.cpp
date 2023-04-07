//
// Created by 12744 on 2023/4/6.
//

#include "AirPlay.h"
/*
 * 全局变量
 */
//画布的宽与高
int hei = 600;
int wid = 360;
//敌机双链表
DoubleList* enemyList;
//子弹链表
DoubleList* bulletList;
//子弹的大小
#define bulletSize 10
//飞机与敌机的大小
#define planeSize 40
//子弹和敌机的最大数量（同一张画布上）
#define enemyBulletSize 20
//定义image数组，保存我们要贴图的图片资源
IMAGE image[4];
//定义飞机结构体
Node player = {0,0};
//分数
int grade = 0;
//设置在击落飞机一定架数时，敌机移动速度加快
static int planeCount = 0;
int planeCount1 = 20;//设置击落20架速度加快
static int planeSpeed = 10;//增加速度为10
int bulletPlaneSpeed = 5;//敌机与子弹的初始速度

//飞机函数的初始化函数：加载图片资源，
void Init(){
    initgraph(wid,hei);
    //需要使用c语言提供的随机函数
    srand((unsigned )time(nullptr));
    //加载图片资源，方便后面贴图使用
    loadimage(&image[background],R"(E:\CC++\Project\AirBattle_Clion\res\5.jpg)",
              wid,hei,false);
    loadimage(&image[plane],R"(E:\CC++\Project\AirBattle_Clion\res\2.jpg)",
              planeSize,planeSize, false);
    loadimage(&image[enemy],R"(E:\CC++\Project\AirBattle_Clion\res\1.jpg)",
              planeSize,planeSize, false);
    loadimage(&image[bullet],R"(E:\CC++\Project\AirBattle_Clion\res\3.jpg)",
              bulletSize,bulletSize, false);
    //初始化飞机的位置
    player = {(wid/2)-(planeSize/2),hei-planeSize};
    //初始化子弹链表和敌机链表
    bulletList = DoubleList_Init();
    enemyList = DoubleList_Init();
}

//绘制游戏背景、飞机与敌机等
void Draw(){
    //使用批量绘图
    BeginBatchDraw();
    //贴图：将Init函数中加载的图片资源贴在画布上
    putimage(0,0,&image[background]);//贴背景图
    //贴出所有的敌机
    for(Node*temp=enemyList->Head;temp!= nullptr;temp=temp->pNext){
        putimage(temp->x,temp->y,&image[enemy]);
    }
    //贴出所有的子弹
    for(Node*temp=bulletList->Head;temp!= nullptr;temp=temp->pNext){
        putimage(temp->x, temp->y,&image[bullet]);
    }
    putimage(player.x,player.y,&image[plane]);//贴飞机

    //在界面左上角显示当前得分
    setbkmode(TRANSPARENT);//显示透明文字
    settextcolor(RED);
    settextstyle(20,0,"宋体");
    TCHAR str[10];
    wsprintf(str,"得分：%d",grade);
    outtextxy(0,0,str);
    //结束批量绘图
    EndBatchDraw();
}

//游戏逻辑
void Start(){
    Init();
    Draw();
    while(1){
        PlaneControl();//控制飞机移动
        Update();//更新敌机和子弹的位置
        Draw();
        if(IsGameOver()){
            //此时游戏已经结束，需要使用弹窗函数
            TCHAR str[50];
            wsprintf(str,"游戏已经结束，您的得分为：%d",grade);
            if(MessageBox(GetHWnd(),str,"提示！",MB_YESNO) == IDYES){
                //此时选择的是继续游戏
                //销毁子弹链表和敌机链表
                //在销毁前需要判断：当前界面中子弹链表和敌机链表中是否有节点
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

//飞机的移动
void PlaneControl(){
    //通过键盘上的按键控制飞机的移动
    int speed = 5;//飞机每次按键移动的像素点
    //GetAsyncKeyState获取键盘上的按键
    if(GetAsyncKeyState(VK_UP)){
        //此时按下的是键盘上的上键
        if(player.y > 0){
            player.y -= speed;//每按一次，则会向上移动8个像素点
        }
    }
    if(GetAsyncKeyState(VK_DOWN)){
        //此时按下的是键盘上的下键
        if(player.y < hei-planeSize){
            player.y += speed;//每按一次，则会向上移动8个像素点
        }
    }
    if(GetAsyncKeyState(VK_LEFT)){
        //此时按下的是键盘上的左键
        if(player.x > 0){
            player.x -= speed;//每按一次，则会向上移动8个像素点
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        //此时按下的是键盘上的右键
        if(player.x < wid-planeSize){
            player.x += speed;//每按一次，则会向上移动8个像素点
        }
    }
    if(_kbhit()){//按下空格，生成子弹
        int key = getch();
        if(key == ' '){
            SpawnBullet();
        }
    }
}

//子弹生成
void SpawnBullet(){
    //通过按下键盘上的空格键，在飞机中间生成子弹
    if(bulletList->length < enemyBulletSize){//首先需要判断当前页面上有多少子弹
        int x = player.x + planeSize/2-bulletSize/2;
        int y = player.y;
        Node*temp = DoubleListNode_Init(x,y);
        DoubleList_Insert(bulletList,temp);
    }
}

//敌机的生成
void SpawnEnemy(){
    //敌机从画布的最上面随机出现
    static int count = 0;
    if(count >= 30){
        //每30次产生一个敌机
        //此时需要判断敌机的个数是否小于最大数量
        if(enemyList->length < enemyBulletSize){
            //此时产生敌机
            Node*temp = DoubleListNode_Init(rand()%(wid-planeSize),0-planeSize);
            DoubleList_Insert(enemyList,temp);
        }
        count = 0;
    }
    count++;
}

//敌机与子弹的移动:更新数据,每次移动后需要判断是否越界以及是否碰撞
void Update(){
    //遍历链表中每一个节点，移动其数据
    //移动敌机
    if(planeCount  >= planeCount1){
        for(Node*temp = enemyList->Head;temp!= nullptr;temp=temp->pNext){
            temp->y += planeSpeed;//每次刷新，敌机移动5个像素点
        }
        planeCount = 0;
        planeSpeed += 10;
    } else {
        for(Node*temp = enemyList->Head;temp!= nullptr;temp=temp->pNext){
            temp->y += bulletPlaneSpeed;//每次刷新，敌机移动5个像素点
        }
    }

    //移动子弹
    for(Node*temp=bulletList->Head;temp!= nullptr;temp=temp->pNext){
        temp->y -= bulletPlaneSpeed;
    }
    SpawnEnemy();//生成敌机
    Destroy();//判断是否有越界，是否需要销毁
    BoomCollide();//判断移动完子弹和敌机后有没有碰撞
}

//子弹和敌机的越界销毁
void Destroy(){
    //敌机的越界销毁
    Node*e = enemyList->Head;
    while(e!= nullptr){
        if(e->y >= hei){
            Node*temp = e;//定义临时指针，指向被删除节点
            e = e->pNext;
            DoubleList_Delete(enemyList,temp);
        } else {
            e = e->pNext;
        }
    }

    //子弹的越界销毁
    Node*b=bulletList->Head;
    while(b!= nullptr){
        if(b->y <= 0){
            Node*temp = b;//定义临时指针，指向被删除节点
            b = b->pNext;
            DoubleList_Delete(bulletList,temp);
        } else {
            b = b->pNext;
        }
    }
}

//实现碰撞逻辑：子弹与敌机的碰撞
bool BulletBoom(Node*n1,Node*n2){//n1是子弹   n2是敌机
    //定义两个临时变量保存这两个节点x和y轴上的距离
    int x = abs((n1->x+bulletSize/2)-(n2->x+planeSize/2));//使用中心点来判断
    //子弹中心点坐标 - 敌机中心点坐标
    int y = abs(n1->y - n2->y);
    return (x <= (bulletSize/2+planeSize/2)) && (y <= planeSize);
    //如果子弹和节点碰撞返回true，否则返回false
}

//碰撞后的处理：敌机和子弹
void BoomCollide(){
    for(Node*b=bulletList->Head;b!= nullptr;b=b->pNext){
        for(Node*e=enemyList->Head;e!= nullptr;e=e->pNext){
            if(BulletBoom(b,e)){
                //如果发生碰撞，则需要删除碰撞的节点
                DoubleList_Delete(enemyList,e);
                DoubleList_Delete(bulletList,b);
                grade += 10;
                planeCount++;
                return;
            }
        }
    }
}

//实现碰撞逻辑：敌机和我方飞机的碰撞
bool PlaneBoom(Node*n1,Node*n2){
    //保存x轴和y轴上的距离
    int x = abs(n1->x - n2->x);
    int y = abs(n1->y - n2->y);
    return (x<=planeSize && y<=planeSize);
}

//游戏是否结束
bool IsGameOver(){
    for(Node*e = enemyList->Head;e!= nullptr;e=e->pNext){
        if(PlaneBoom(e,&player)){
            //说明此时飞机与敌机已经相撞，游戏结束！
            return true;
        }
    }
    return false;
}