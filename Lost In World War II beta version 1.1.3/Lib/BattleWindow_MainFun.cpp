#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"



void BattleWindow::Flash(){//1秒刷新一次


    int i,j;
    if(Mission!=0)Total_Time++;
    if(Total_Time%5==4)this->Enemy_Generate();//5秒兵营生成敌人

    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate()) continue;
        if(P1[i].GetProcess()<100) FinalWeapon.start(100);
    }

    Play_BackMusic();
    MissionTick();

    for(i=0;i<OBJECT_NUMBER;i++){//物体动画
        if(!object[i]->GetAlive())continue;
        object[i]->Flash();
        for(j=0;j<PLAYER_NUMBER_MAX;j++){
            if(!P1[j].GetActivate()) continue;
        if(object[i]->GetType()==10&&P1[j].GetRect().intersects(object[i]->GetRect())&&object[i]->GetOther()==1){//地刺
            P1[j].Player_UnderAttack(1);
            object[i]->Flash();
            CreatePartical(P1[j].GetRect(),Type::Player_Damage);//地刺
        }
        }
    }


    for(i=0;i<ENEMY_NUMBER;i++){//敌人AI
        if(enemy[i].GetAlive()==false)continue;
        if(enemy[i].GetSkin()==2||enemy[i].GetSkin()==3||enemy[i].GetSkin()==4){
            enemy[i].Enemy_ChangeHead(AI1(P1[0].GetRect(),enemy[i].GetRect()));
        }
    }
    if(boss1->GetAlive()&&boss1->GetBullet3Flash()==0)boss1->Boss1_ChangeHead(AI1(P1[0].GetRect(),boss1->GetRect()));//boss AI


     if(QRandomGenerator::global()->generate()%2==0&&boss1->GetAlive()&&boss1->GetB3().GetFlash()==0){//boss子弹
         boss1->Boss1_B3Fire();
         QRect temp;
         switch (boss1->GetHead()) {
         case UP:temp.setRect(boss1->GetRect().x(),0,150,boss1->GetRect().y());CreatePartical(temp,Type::Boss_Fire_D);break;
         case DOWN:temp.setRect(boss1->GetRect().x(),boss1->GetRect().y(),150,1000-boss1->GetRect().y());CreatePartical(temp,Type::Boss_Fire_D);break;
         case LEFT:temp.setRect(0,boss1->GetRect().y(),boss1->GetRect().x(),150);CreatePartical(temp,Type::Boss_Fire);break;
         case RIGHT:temp.setRect(boss1->GetRect().x()+150,boss1->GetRect().y(),2000-boss1->GetRect().y(),150);CreatePartical(temp,Type::Boss_Fire);break;
         }
     }

     if(P1[0].GetHP()<0){//死亡判定
         if(Mission==1&&LevelB==4){MissionTechEnd();return;}
         QMessageBox::information(nullptr,tr("提示"),tr("您失败了"), tr("好"));
         this->~BattleWindow();
         backto=new MainWindow;
         backto->setMouseTracking(true);
         backto->show();
     }

     //判断敌人是否全部被歼灭
    Win=true;
    for(i=0;i<ENEMY_NUMBER;i++)
        if(enemy[i].GetAlive())Win=false;
    for(i=0;i<OBJECT_NUMBER;i++)
        if(object[i]->GetAlive()&&object[i]->GetType()==5)Win=false;

    //判断敌人是否全部被歼灭

    //胜利之后的操作
    if(Win){
        switch (Mission) {
        case 1:MissionTeach_Win();break;
        case 2:MissionRougueLike_Continue();return;
        case 100:
            if(Total_Time<=20)return;
            QMessageBox::information(nullptr,tr("提示"),tr("您赢了"), tr("好"));
            this->~BattleWindow();
            backto=new MainWindow;
            backto->setMouseTracking(true);
            backto->show();
            break;
        }
        }
   //胜利之后的操作
}


void BattleWindow::Flash2(){//毫秒Tick
    qDebug()<<Key[0];
    int i;
    this->Mist_Generate();
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate()) continue;
        P1[i].GetB3().Flash();
    }
    boss1->GetB3().Flash();
    for(i=0;i<PARTICAL_NUMBER;i++){
        if(!partical[i].GetAlive())continue;
        partical[i].FLash();
    }

    for(i=0;i<REDZONE_NUMBER;i++){//轰炸区动画
        if(redzone[i].GetAlive()==false)continue;
        if(redzone[i].GetFlash()==-1)continue;
        if(redzone[i].GetFlash()==70)Play_RedZone(redzone[i].GetR()/10);
        if(redzone[i].GetFlash()==70)RedZoneBoom(i);
        redzone[i].Flash();
    }

    //ui->label->setText(QString::number(P1.GetHP(),10));
    //ui->label_2->setText(QString::number(P1.GetMP(),10));
    //ui->label_3->setText(QString::number(P1.GetWeaponLv(),10));
    //ui->label_5->setText(QString::number(P1.GetProcess(),10));

}//毫秒Tick


void BattleWindow::RedZoneBoom(int x){//轰炸区实现

    int i;
    for(i=0;i<OBJECT_NUMBER;i++){
    if(!object[i]->GetAlive())continue;
    if(redzone[x].Object_Hit(object[i]->GetRect())){
        object[i]->Dead();
        }
    }
    for(i=0;i<ENEMY_NUMBER;i++){
    if(!enemy[i].GetAlive())continue;
    if(redzone[x].Object_Hit(enemy[i].GetRect())){
        enemy[i].Dead();
        }
    }
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate()) continue;
        if(redzone[x].Object_Hit(P1[i].GetRect())){
            P1[i].Player_UnderAttack(100);
        }
    }
}//轰炸区实现


void BattleWindow::Bullet_Fly(){//子弹

    //this->Write_Sql();//暂时用这个笨拙算法

    int i,k;
    for(k=0;k<PLAYER_NUMBER_MAX;k++){
        if(!P1[k].GetActivate()) continue;
    for(i=0;i<PLAYER_B1_NUMBER;i++){
        if(!P1[k].GetB1(i).GetAlive())continue;
        P1[k].GetB1(i).PlayerBullet1_Move(10);
    }
    for(i=0;i<PLAYER_B2_NUMBER;i++){
        if(!P1[k].GetB2(i).GetAlive())continue;
        P1[k].GetB2(i).PlayerBullet2_Move(10);
    }
    for(i=0;i<ENEMY_NUMBER;i++){
        enemy[i].Enemy_B1_Move();
    }
    if(boss1->GetAlive()){
        for(i=0;i<Edit_Min;i++){
        if(!boss1->GetB2(i).GetAlive())continue;
        boss1->GetB2(i).PlayerBullet2_Move(4);
        }
    }
    }
    Bullet_HitCheck();
}







void BattleWindow::Player_HitCheck(int k){
    int i;


    if(P1[k].GetRect().x()<0||P1[k].GetRect().y()+40>Y_Max||P1[k].GetRect().y()<0||P1[k].GetRect().x()+40>X_Max){//玩家边界判断
        P1[k].Player_Move(-1);
        Player_HitCheck(k);//递归处理
    }//玩家边界判断

    //P1[k].Player_UnSlow();//墙判断
    for(i=0;i<OBJECT_NUMBER;i++){//墙判断
        if(!object[i]->GetAlive())continue;
        if(P1[k].GetRect().intersects(object[i]->GetRect())&&object[i]->Contact()){
            switch (object[i]->GetType()) {
            case 4:MissionRougueLike_Win();break;//传送门功能
            case 6:
                switch (object[i]->GetSkin()) {
                case 1:P1[k].Strengthen(2,10,0,0);return;
                case 2:P1[k].Strengthen(10,10,0,0);return;
                case 3:P1[k].Strengthen(50,50,0,0);return;
                }break;
            case 7:switch (object[i]->GetSkin()) {
                case 1:P1[k].Strengthen(0,100,0,0);return;
                case 2:P1[k].Strengthen(0,200,0,0);return;
                case 3:P1[k].Strengthen(0,300,1,0);return;

            }break;
            case 11:P1[k].Player_Slow();break;
            case 10:
                if(object[i]->GetOther()==0)break;
                P1[k].Player_UnderAttack(1);
                CreatePartical(P1[k].GetRect(),Type::Player_Damage);
                object[i]->Flash();
                break;
            default:
                P1[k].Player_Move(-1);
                Player_HitCheck(k);break;
            }
        }
    }//墙end

}//dunction end

void BattleWindow::Boss_Move(){
    if(boss1->GetAlive()==false||boss1->GetBullet3Flash()!=0)return;
    int i;bool hit=false;
    boss1->Boss1_Move(5);
   while(boss1->GetRect().x()<0||boss1->GetRect().y()+40>Y_Max||boss1->GetRect().y()<0||boss1->GetRect().x()+40>X_Max){
       boss1->Boss1_Move(-1);
       hit=true;
    }
   //边界碰撞
    for(i=0;i<OBJECT_NUMBER;i++){
        if(object[i]->GetAlive()==false)continue;

    b:    if(boss1->GetRect().intersects(object[i]->GetRect())){
            switch (object[i]->GetType()){
            case 2:boss1->Boss1_Move(-1);hit=true;goto b;break;
            default: object[i]->Dead();CreatePartical(object[i]->GetRect(),Type::Object_Hit);break;
            }
        }
    }
    if(hit )boss1->Boss1_RndChangeHead();
}


void BattleWindow::Enemy_Move(){
    int i,k;//i敌人编号，i物体编号

    for(i=0;i<ENEMY_NUMBER;i++){
        bool ice=false,hit=false;
        if(!enemy[i].GetAlive())continue;//敌人死了就跳出

        enemy[i].Enemy_Move(enemy[i].GetMoveSpeed());//敌人移动

        a:if(enemy[i].GetRect().x()<0||enemy[i].GetRect().x()+enemy[i].GetRect().width()>X_Max||  //边界碰撞
          enemy[i].GetRect().y()<0||enemy[i].GetRect().y()+enemy[i].GetRect().height()>Y_Max){//边界碰撞
            enemy[i].Enemy_Move(-1);
            hit=true;
            goto a;
        }//边界碰撞

        for(k=0;k<OBJECT_NUMBER;k++){//物体碰撞检测 k代表物体，i代表敌人
            if(object[k]->GetAlive()==false||
                    object[k]->GetType()==5||object[k]->GetType()==6||object[k]->GetType()==7)continue;
            b:if(enemy[i].GetRect().intersects(object[k]->GetRect())&&object[k]->Contact()){
                hit=true;
                switch (object[k]->GetType()){
                case 4:
                case 6:
                case 7:hit=false;break;
                case 11:enemy[i].Enemy_Slow();ice=true;break;
                default:
                    enemy[i].Enemy_Move(-1);
                    hit=true;
                    goto b;
                }
            }
        }

        if(!ice)enemy[i].Enemy_UnSlow();//效果实现
        if(hit && !ice)enemy[i].Enemy_RndChangeHead();//效果实现

    }

}//function end

void BattleWindow::Enemy_Generate(){//兵营生成敌人
    int i,x,y;
    for(i=0;i<OBJECT_NUMBER;i++){
        if(object[i]->GetType()!=5||object[i]->GetAlive()==false)continue;
        x = QRandomGenerator::global()->generate();
        y = QRandomGenerator::global()->generate();
        QRect t1;

        t1=object[i]->GetRect();
        if(x%2==1)t1.adjust(-50,0,-50,0);//随机生成位置
        else t1.adjust(50,0,50,0);
        if(y%2==1)t1.adjust(0,50,0,50);
        else t1.adjust(0,-50,0,-50);//随机生成位置

        switch (object[i]->GetSkin()) {
            case 1:
                if(object[i]->GetOther()>=10){
                    CreatePartical(object[i]->GetRect(),Type::Object_Hit);
                    object[i]->Dead();
                    break;
                    }
                object[i]->SetOther();
                CreateEnemy(t1,2,5,3,2);
                CreatePartical(t1,Type::Object_Hit);
            break;
            case 2:
                if(object[i]->GetOther()>=15){
                    CreatePartical(object[i]->GetRect(),Type::Object_Hit);
                    object[i]->Dead();
                    break;
                 }
                 object[i]->SetOther();
                 CreateEnemy(t1,10,6,3,3);
                 CreatePartical(t1,Type::Object_Hit);
                break;
            case 3:
                if(object[i]->GetOther()>=20){
                    CreatePartical(object[i]->GetRect(),Type::Object_Hit);
                    object[i]->Dead();
                    break;
                 }
                object[i]->SetOther();
                CreateEnemy(t1,50,7,3,4);
                CreatePartical(t1,Type::Object_Hit);
                break;
            default:break;
        }

    }
}//end function

void BattleWindow::P1_Weapon(){//技能
    int i;
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate())continue;
    switch (P1[i].GetChoose()) {
    case 0:
        if(P1[i].GetProcess()<100)
        P1[i].Player_ProcessOn(1);
        break;
    case 1:
        P1[i].Player_ProcessOn(-1);
        if(P1[i].GetProcess()<=0){
            P1[i].SetChoose(0);
            P1[i].Player_UnSlow();
        }
        break;
    case 2:
        P1[i].Player_ProcessOn(-100);
        P1[i].SetChoose(0);
    default:break;
    }
    P1[i].Strengthen(0,2,0,0);
    if(P1[i].GetMP()>=100){
        P1[i].Strengthen(0,100-P1[i].GetMP(),0,0);
    }
    }
}

void BattleWindow::Enemy_All(){//敌人转向和开火
    int i,x;
    for ( i=0 ; i<ENEMY_NUMBER ; i++ ){
        if(!enemy[i].GetAlive()) continue;
        x = QRandomGenerator::global()->generate();
        if(x%6==0){
           enemy[i].Enemy_RndChangeHead();
        }
        x = QRandomGenerator::global()->generate();
        switch (enemy[i].GetSkin()) {
        case 1:if(x%4==0)enemy[i].Enemy_B1Fire();break;
        case 2:if(x%10==0)enemy[i].Enemy_B1Fire();break;
        case 3:if(x%10==0)enemy[i].Enemy_B1Fire();break;
        case 4:if(x%10==0)enemy[i].Enemy_B1Fire();break;
        case 5:if(x%2==0)enemy[i].Enemy_B1Fire();break;
        }
}
    x = QRandomGenerator::global()->generate();

    if(boss1->GetAlive()&& x%10==0 )
         boss1->Boss1_B2Fire();

}//function end



void BattleWindow::Mist_Generate(){
    int k;
    for(k=0;k<PLAYER_NUMBER_MAX;k++){
        if(!P1[k].GetActivate()||P1[k].GetChoose()==1)continue;
    int i;
    for(i=0;i<5;i++){
        switch (P1[k].GetHead()) {
        case UP:
            CreatePartical(QRect(QRandomGenerator::global()->bounded(P1[k].GetRect().x()-10,P1[k].GetRect().x()+40),
                              QRandomGenerator::global()->bounded(P1[k].GetRect().y()+30,P1[k].GetRect().y()+50),
                           20,20),Type::Mist);
            break;
        case DOWN:
            CreatePartical(QRect(QRandomGenerator::global()->bounded(P1[k].GetRect().x()-10,P1[k].GetRect().x()+40),
                              QRandomGenerator::global()->bounded(P1[k].GetRect().y()-20,P1[k].GetRect().y()),
                           20,20),Type::Mist);
            break;
        case LEFT:
            CreatePartical(QRect(QRandomGenerator::global()->bounded(P1[k].GetRect().x()+30,P1[k].GetRect().x()+50),
                              QRandomGenerator::global()->bounded(P1[k].GetRect().y()-10,P1[k].GetRect().y()+40),
                           20,20),Type::Mist);
            break;
        case RIGHT:
            CreatePartical(QRect(QRandomGenerator::global()->bounded(P1[k].GetRect().x()-20,P1[k].GetRect().x()),
                              QRandomGenerator::global()->bounded(P1[k].GetRect().y()-10,P1[k].GetRect().y()+40),
                           20,20),Type::Mist);
            break;
        }

    }
    }
}

void BattleWindow::Command(QString command){
    int i;
    if(command=="/help"){
        QMessageBox::information(nullptr,tr("帮助"),tr("指令：\n"
                                                     "/CreatePartical x坐标 y坐标 长度 宽度 种类\n"
                                                     "/CreateEnemy x坐标 y坐标 长度 宽度 HP 移速 子弹速度 皮肤\n"
                                                     "/CreateObject x坐标 y坐标 长度 宽度 种类 皮肤\n"
                                                     "/CreateRedZone x坐标 y坐标 爆炸半径 种类\n"
                                                     "/CreateBoss x坐标 y坐标 血量\n"
                                                     "/skip 跳到的关卡\n"
                                                     "/Str HP MP 武器等级 速度\n"
                                                     "/help 帮助\n"
                                                     "CPlayer x坐标 y坐标 血量 武器等级 速度"), tr("好"));
        return;
    }
    int mode;
    QStringList commandlist;
    if(command[0]=="/"){
        command.replace(0,1," ");
        commandlist=command.split(" ");
        if(commandlist[1]=="CreatePartical"){
            mode=1;
        }
        if(commandlist[1]=="CreateEnemy"){
            mode=2;
        }
        if(commandlist[1]=="CreateObject"){
            mode=3;
        }
        if(commandlist[1]=="CreateRedZone"){
            mode=4;
        }
        if(commandlist[1]=="CreateBoss"){
            mode=5;
        }
        if(commandlist[1]=="skip"){
            mode=6;
        }
        if(commandlist[1]=="Str"){
            mode=7;
        }
        if(commandlist[1]=="CPlayer"){
            mode=8;
        }
    }else{
        QMessageBox::information(nullptr,tr("帮助"),tr("指令错误"), tr("好"));
        return;
    }
    switch (mode) {
    case 1:
        CreatePartical(QRect(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10),commandlist[4].toInt(nullptr,10),commandlist[5].toInt(nullptr,10)),Type(commandlist[6].toInt(nullptr,10)));
        break;
    case 2:
        CreateEnemy(QRect(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10),commandlist[4].toInt(nullptr,10),commandlist[5].toInt(nullptr,10)),
                commandlist[6].toInt(nullptr,10),
                commandlist[7].toInt(nullptr,10),
                commandlist[8].toInt(nullptr,10),
                commandlist[9].toInt(nullptr,10));
        break;
    case 3:
        CreateObject(QRect(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10),commandlist[4].toInt(nullptr,10),commandlist[5].toInt(nullptr,10)),
                commandlist[6].toInt(nullptr,10),
                commandlist[7].toInt(nullptr,10),10
                );
        break;
    case 4:
        CreateRedZone(QRect(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10),0,0),commandlist[4].toInt(nullptr,10),1);
        break;
    case 5:
        new(boss1)Boss1(QRect(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10),150,150),
                commandlist[4].toInt(nullptr,10),1);
        break;
    case 6:
        ClearMap(QRect(0,0,40,40));
        Win=true;
        LevelB=commandlist[2].toInt(nullptr,10);
        this->MissionRougueLike_Win();
        break;
    case 7:
        for(i=0;i<PLAYER_NUMBER_MAX;i++){
            if(!P1[i].GetActivate())continue;
        P1[i].Strengthen(commandlist[2].toInt(nullptr,10),
                commandlist[3].toInt(nullptr,10),
                commandlist[4].toInt(nullptr,10),
                commandlist[5].toInt(nullptr,10));
        }
        break;
    case 8:
        for(i=0;i<PLAYER_NUMBER_MAX;i++){
            if(P1[i].GetActivate())continue;
            new(&P1[i])Player(QRect(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10),40,40)
                    ,commandlist[4].toInt(nullptr,10),100,commandlist[5].toInt(nullptr,10));
            break;
        }
    }


}

void BattleWindow::mousePressEvent(QMouseEvent *a){
    int i;
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(P1[i].GetActivate())continue;
        new(&P1[i])Player(QRect(a->x(),a->y(),40,40)
                ,99999,100,3);
        break;
    }
}





