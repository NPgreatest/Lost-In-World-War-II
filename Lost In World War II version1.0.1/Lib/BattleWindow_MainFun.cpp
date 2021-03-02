#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

void BattleWindow::Flash(){//1秒刷新一次
    int i;
    Total_Time++;

    Play_BackMusic();
    MissionTick(this->Mission);

    for(i=0;i<Edit_Max;i++){//物体动画
        if(!object[i]->GetAlive())continue;
        object[i]->Flash();
        if(object[i]->GetType()==10&&P1.Player_Hit(object[i]->GetPos(),object[i]->GetArea())==true&&object[i]->GetOther()==1){//地刺
            P1.Player_UnderAttack(1);
            object[i]->Flash();
            CreatePartical(P1.GetPos(),P1.GetArea(),Type::Player_Damage);//地刺
        }
    }


    for(i=0;i<Edit_Min;i++){//敌人AI
        if(enemy[i].GetAlive()==false)continue;
        if(enemy[i].GetSkin()==2||enemy[i].GetSkin()==3||enemy[i].GetSkin()==4){
            enemy[i].Enemy_ChangeHead(AI1(P1.GetPos(),enemy[i].GetPos()));
        }
    }
    if(boss1->GetAlive()==true&&boss1->GetBullet3Flash()==0)boss1->Boss1_ChangeHead(AI1(P1.GetPos(),boss1->GetPos()));//boss AI

     if(QRandomGenerator::global()->generate()%5==0&&boss1->GetAlive()==true&&boss1->GetBullet3Flash()==0){//boss子弹
         boss1->Boss1_B3Fire();
         XY t1=boss1->GetPos();XY t2=boss1->GetPos();
         switch (boss1->GetHead()) {
         case UP:t1.y=0;t2={150,boss1->GetPos().y}; CreatePartical(t1,t2,Type::Boss_Fire_D);break;
         case DOWN:t2={150,1000};CreatePartical(t1,t2,Type::Boss_Fire_D);break;
         case LEFT:t1.x=0;t2={boss1->GetPos().x,150};CreatePartical(t1,t2,Type::Boss_Fire);break;
         case RIGHT:t2={10000,150};CreatePartical(t1,t2,Type::Boss_Fire);break;
         }
     }

     if(P1.GetHP()<0){//死亡判定
         if(Mission==1&&LevelB==4){MissionTechEnd();return;}
         QMessageBox::information(nullptr,tr("提示"),tr("您失败了"), tr("好"));
         this->~BattleWindow();
         backto=new MainWindow;
         backto->setMouseTracking(true);
         backto->show();
     }

     //判断敌人是否全部被歼灭
    Win=true;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==true)Win=false;
        if(object[i]->GetAlive()==true&&object[i]->GetType()==5)Win=false;
    }
    //判断敌人是否全部被歼灭

    //胜利之后的操作
    if(Win==true){
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

    int i;
    this->Mist_Generate();
    P1.GetB3().Flash();
    boss1->Boss1_Bullet3Flash();
    for(i=0;i<Edit_Max;i++){
        if(partical[i].GetAlive()==false)continue;
        partical[i].FLash();
    }

    for(i=0;i<Edit_Min;i++){//轰炸区动画
        if(redzone[i].GetAlive()==false)continue;
        if(redzone[i].GetFlash()==-1)continue;
        if(redzone[i].GetFlash()==70)Play_RedZone(redzone[i].GetR()/10);
        if(redzone[i].GetFlash()==70)RedZoneBoom(i);
        redzone[i].Flash();
    }

    ui->label->setText(QString::number(P1.GetHP(),10));
    ui->label_2->setText(QString::number(P1.GetMP(),10));
    ui->label_3->setText(QString::number(P1.GetWeaponLv(),10));
    ui->label_4->setText(QString::number(P1.GetMaterial(),10));
    ui->label_5->setText(QString::number(P1.GetProcess(),10));

}//毫秒Tick


void BattleWindow::RedZoneBoom(int x){//轰炸区实现

    int i;
    for(i=0;i<Edit_Max;i++){
    if(object[i]->GetAlive()==false)continue;
    if(redzone[x].Object_Hit(object[i]->GetPos(),object[i]->GetArea())==true){
        object[i]->Dead();
        }
    }
    for(i=0;i<Edit_Max;i++){
    if(enemy[i].GetAlive()==false)continue;
    if(redzone[x].Object_Hit(enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Dead();
        }
    }
    if(redzone[x].Object_Hit(P1.GetPos(),P1.GetArea())==true){
        P1.Player_UnderAttack(100);
    }
}//轰炸区实现


void BattleWindow::bulletfly(){//子弹
    int i;
    for(i=0;i<Edit_Max;i++){
    if(!P1.GetB1(i).GetAlive())continue;
    P1.GetB1(i).PlayerBullet1_Move(10);
    }
    P1.GetB2().PlayerBullet2_Move(10);
    for(i=0;i<Edit_Max;i++){
        enemy[i].Enemy_B1_Move();
    }
    if(boss1->GetAlive()==true){
        boss1->Boss1_B1_Move();
    }
    Bullet_HitCheck();
}


void BattleWindow::Bullet_HitCheck(){
    int i,k,j;
    bool B3=false;

    //子弹命中敌人
    for(i=0;i<Edit_Max;i++){
    if(!enemy[i].GetAlive())continue;
    for(k=0;k<Edit_Max;k++){//B1
    if(P1.GetB1(k).GetAlive()&&P1.GetB1(k).PlayerBullet1_Hit(enemy[i].GetPos(),enemy[i].GetArea())){
        enemy[i].Enemy_UnderAttack(P1.Damage(SkillName::MainWeapon));
        P1.GetB1(k).PlayerBullet1_Dead();
        Play_PlayerHit();
            if(enemy[i].GetAlive()==false)CreatePartical(enemy[i].GetPos()-50,enemy[i].GetArea()+100,Type::Object_Hit);
            else {CreatePartical(enemy[i].GetPos(),enemy[i].GetArea(),Type::Object_Hit);}
        }
    }//B1
    if(P1.GetB2().PlayerBullet2_Hit(enemy[i].GetPos(),enemy[i].GetArea())){//B2
        enemy[i].Enemy_UnderAttack(P1.Damage(SkillName::SubWeapon));
            if(enemy[i].GetAlive()==false)CreatePartical(enemy[i].GetPos()-50,enemy[i].GetArea()+100,Type::Object_Hit);
            else {CreatePartical(enemy[i].GetPos(),enemy[i].GetArea(),Type::Object_Hit);}

        }//B2
    if(P1.GetB3().GetFlash()==3&&P1.GetB3().GetAlive()){
        if(P1.GetB3().PlayerBullet3_Hit(enemy[i].GetPos(),enemy[i].GetArea())){
            enemy[i].Enemy_UnderAttack(P1.Damage(SkillName::Fire));
            CreatePartical(enemy[i].GetPos(),enemy[i].GetArea(),Type::Player_Damage);
            B3=true;
            }
        }
    }
    //子弹命中敌人


    for(i=0;i<Edit_Max;i++){//玩家打中boss判定
        if(P1.GetB1(i).GetAlive() && boss1->GetAlive()==true && P1.GetB1(i).PlayerBullet1_Hit(boss1->GetPos(),boss1->GetArea())){
            P1.GetB1(i).PlayerBullet1_Dead();
            boss1->Boss1_UnderAttack(P1.Damage(SkillName::MainWeapon));
            CreatePartical(boss1->GetPos(),boss1->GetArea(),Type::Object_Hit);
        }
    }
    if(boss1->GetAlive()&&P1.GetB2().PlayerBullet2_Hit(boss1->GetPos(),boss1->GetArea())){
        boss1->Boss1_UnderAttack(P1.Damage(SkillName::SubWeapon));
        CreatePartical(boss1->GetPos(),boss1->GetArea(),Type::Object_Hit);
    }
    if(boss1->GetAlive()&&P1.GetB3().GetFlash()==3&&
                             P1.GetB3().GetAlive()&&
            P1.GetB3().PlayerBullet3_Hit(boss1->GetPos(),boss1->GetArea())){
       boss1->Boss1_UnderAttack(P1.Damage(SkillName::Fire));
        CreatePartical(boss1->GetPos(),boss1->GetArea(),Type::Player_Damage);
        B3=true;
    }//玩家打中boss判定
    if(B3==true)P1.GetB3().PlayerBullet3_Dead();



    for(i=0;i<Edit_Max;i++){//子弹打方块判定
    if(object[i]->GetAlive()==false)continue;
    for(k=0;k<Edit_Max;k++){
    if(P1.GetB1(k).PlayerBullet1_Hit(object[i]->GetPos(),object[i]->GetArea())){
        if(object[i]->Hit()){
            CreatePartical(object[i]->GetPos(),object[i]->GetArea(),Type::Object_Hit);
            P1.GetB1(k).PlayerBullet1_Dead();
            Play_PlayerHit();
        }
    }
    }
    }//子弹打方块判定

    for(i=0;i<Edit_Max;i++){
        if(object[i]->GetAlive()==false||object[i]->GetType()==5)continue;
    for(j=0;j<Edit_Max;j++){//敌人子弹打方块
        if(enemy[j].GetAlive()==false)continue;
        for(k=0;k<5;k++){
         if(enemy[j].Enemy_BulletHit(k,object[i]->GetPos(),object[i]->GetArea())==true&&object[i]->Hit()==true){
             enemy[j].Enemy_B1_Hit(k);
             CreatePartical(object[i]->GetPos(),object[i]->GetArea(),Type::Object_Hit);

         }
        }
    }
    }//子弹打方块




    for(i=0;i<Edit_Min;i++){//Boss子弹命中玩家
        if(P1.Player_Hit(boss1->GetBulletPos(i),XY(10,10))==true&&boss1->GetAlive()==true){
            P1.Player_UnderAttack(10);
            CreatePartical(P1.GetPos(),P1.GetArea(),Type::Player_Damage);
            boss1->Boss1_B1_Hit(i);
        }
    }
    if(P1.Player_Hit(boss1->GetBullet3Pos(),boss1->GetBullet3Area())==true&&boss1->GetBullet3Flash()>=50&&boss1->GetAlive()==true){//boss技能判定
        P1.Player_UnderAttack(100);
        CreatePartical(P1.GetPos(),P1.GetArea(),Type::Player_Damage);
        boss1->Boss1_B3_Hit();
    }//Boss子弹命中玩家


    for(i=0;i<Edit_Max;i++){//敌人子弹命中玩家
        if(enemy[i].GetAlive()==false)continue;
        for(k=0;k<5;k++){
            if(enemy[i].Enemy_BulletHit(k,P1.GetPos(),P1.GetArea())==true){
                P1.Player_UnderAttack(1);
                CreatePartical(P1.GetPos(),P1.GetArea(),Type::Player_Damage);
                enemy[i].Enemy_B1_Hit(k);
                Play_PlayerHit_2();
            }
        }
    }//敌人子弹命中玩家f


}//function end



void BattleWindow::Player_HitCheck(){
    int i;

    if(P1.GetPos().x<0||P1.GetPos().x+50>X_Max||P1.GetPos().y<0||P1.GetPos().y+50>Y_Max){//玩家边界判断
        P1.Player_Move(-1);
        Player_HitCheck();//递归处理
    }//玩家边界判断

    //P1.Player_UnSlow();//墙判断
    for(i=0;i<Edit_Max;i++){//墙判断
        if(object[i]->GetAlive()==false)continue;
        if(P1.Player_Hit(object[i]->GetPos(),object[i]->GetArea())==true&&object[i]->Contact()==true){
            switch (object[i]->GetType()) {
            case 4:MissionRougueLike_Win();break;//传送门功能
            case 6:
                switch (object[i]->GetSkin()) {
                case 1:P1.Strengthen(2,0,0,0,0,0);return;
                case 2:P1.Strengthen(10,0,0,0,0,0);return;
                case 3:P1.Strengthen(50,0,0,0,0,0);return;
                }break;
            case 7:switch (object[i]->GetSkin()) {
                case 1:P1.Strengthen(0,20,0,20,0,0);return;
                case 2:P1.Strengthen(0,50,0,50,0,0);return;
                case 3:P1.Strengthen(0,0,1,0,0,0);return;

            }break;
            case 11:P1.Player_Slow();break;
            case 10:
                if(object[i]->GetOther()==0)break;
                P1.Player_UnderAttack(1);
                CreatePartical(P1.GetPos(),P1.GetArea(),Type::Player_Damage);
                object[i]->Flash();
                break;
            default:
                P1.Player_Move(-1);
                Player_HitCheck();break;
            }
        }
    }//墙end

}//dunction end

void BattleWindow::Boss_Move(){
    if(boss1->GetAlive()==false||boss1->GetBullet3Flash()!=0)return;
    int i;bool hit=false;
    boss1->Boss1_Move(5);
a:   if(boss1->GetPos().x<0||boss1->GetPos().x+boss1->GetArea().x>X_Max||  //边界碰撞
           boss1->GetPos().y<0||boss1->GetPos().y+boss1->GetArea().y>Y_Max){
       boss1->Boss1_Move(-1);hit=true;goto a;
   }//边界碰撞
    for(i=0;i<Edit_Max;i++){
        if(object[i]->GetAlive()==false)continue;

    b:    if(boss1->Boss1_Hit(object[i]->GetPos(),object[i]->GetArea())==true){
            switch (object[i]->GetType()){
            case 2:boss1->Boss1_Move(-1);hit=true;goto b;break;
            default: object[i]->Dead();CreatePartical(object[i]->GetPos(),object[i]->GetArea(),Type::Object_Hit);break;
            }
        }
    }
    if(hit==true)boss1->Boss1_RndChangeHead();
}


void BattleWindow::Enemy_Move(){
    int i,k;//i敌人编号，i物体编号

    for(i=0;i<Edit_Max;i++){
        bool ice=false,hit=false;
        if(!enemy[i].GetAlive())continue;//敌人死了就跳出

        enemy[i].Enemy_Move(enemy[i].GetMoveSpeed());//敌人移动

        a:if(enemy[i].GetPos().x<0||enemy[i].GetPos().x+enemy[i].GetArea().x>X_Max||  //边界碰撞
          enemy[i].GetPos().y<0||enemy[i].GetPos().y+enemy[i].GetArea().y>Y_Max){//边界碰撞
            enemy[i].Enemy_Move(-1);
            hit=true;
            goto a;
        }//边界碰撞

        for(k=0;k<Edit_Max;k++){//物体碰撞检测 k代表物体，i代表敌人
            if(object[k]->GetAlive()==false||
                    object[k]->GetType()==5||object[k]->GetType()==6||object[k]->GetType()==7)continue;
            b:if(enemy[i].Enemy_Hit(object[k]->GetPos(),object[k]->GetArea())==true&&object[k]->Contact()==true){
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

        if(ice==false)enemy[i].Enemy_UnSlow();//效果实现
        if(hit==true&&ice==false)enemy[i].Enemy_RndChangeHead();//效果实现

    }

}//function end

void BattleWindow::Enemy_Generate(){//兵营生成敌人
    int i,x,y;
    XY t1;
    for(i=0;i<Edit_Max;i++){
        if(object[i]->GetType()!=5||object[i]->GetAlive()==false)continue;
        x = QRandomGenerator::global()->generate();
        y = QRandomGenerator::global()->generate();

        t1=object[i]->GetPos();
        if(x%2==1)t1.x-=50;//随机生成位置
        else t1.x+=50;
        if(y%2==1)t1.y-=50;
        else t1.y+=50;//随机生成位置

        switch (object[i]->GetSkin()) {
            case 1:
                if(object[i]->GetOther()>=10){
                    CreatePartical(object[i]->GetPos(),object[i]->GetArea(),Type::Object_Hit);
                    object[i]->Dead();
                    break;
                    }
                object[i]->SetOther();
                CreateEnemy(t1,XY(50,50),2,5,3,2);
                CreatePartical(t1,XY(50,50),Type::Object_Hit);
            break;
            case 2:
                if(object[i]->GetOther()>=15){
                    CreatePartical(object[i]->GetPos(),object[i]->GetArea(),Type::Object_Hit);
                    object[i]->Dead();
                    break;
                 }
                 object[i]->SetOther();
                 CreateEnemy(t1,XY(50,50),10,6,3,3);
                 CreatePartical(t1,XY(50,50),Type::Object_Hit);
                break;
            case 3:
                if(object[i]->GetOther()>=20){
                    CreatePartical(object[i]->GetPos(),object[i]->GetArea(),Type::Object_Hit);
                    object[i]->Dead();
                    break;
                 }
                object[i]->SetOther();
                CreateEnemy(t1,XY(50,50),50,7,3,4);
                CreatePartical(t1,XY(50,50),Type::Object_Hit);
                break;
            default:break;
        }

    }
}//end function

void BattleWindow::P1_Fix(){//特殊能力
    if(P1.GetMaterial()<=0){
        P1.Strengthen(0,0,0,-P1.GetMaterial(),0,0);
        Fix_Mod=0;
        fix.stop();return;
    }
    P1.Player_ProcessOn(1);

    if(Fix_Mod==1&&fix.isActive()){
    P1.Player_Slow();
    }

    if(P1.GetProcess()>=100){
        switch (Fix_Mod) {
        case 1:P1.Strengthen(0,0,0,-1,0,0);P1.Player_ProcessOn(-P1.GetProcess());return;
        case 15:P1.Strengthen(0,10,0,-10,0,0);P1.Player_ProcessOn(-P1.GetProcess());break;
        case 10:P1.Strengthen(1,0,0,-10,0,0);P1.Player_ProcessOn(-P1.GetProcess());break;
        }
        fix.stop();
    }
}

void BattleWindow::Enemy_All(){//敌人转向和开火
    int i,x;
    for (i=0;i<Edit_Max ;i++ ){
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
    if(boss1->GetAlive()==true&&x%10==0)boss1->Boss1_B1Fire();
}//function end

HEAD BattleWindow::AI1(XY player,XY enemy){
    int d[5],i,n=0;
    d[0]=(enemy.y-player.y)*(enemy.y-player.y)+(enemy.x-player.x)*(enemy.x-player.x);
    d[1]=(enemy.y+10-player.y)*(enemy.y+10-player.y)+(enemy.x-player.x)*(enemy.x-player.x);
    d[2]=(enemy.y-10-player.y)*(enemy.y-10-player.y)+(enemy.x-player.x)*(enemy.x-player.x);
    d[3]=(enemy.y+-player.y)*(enemy.y-player.y)+(enemy.x-10-player.x)*(enemy.x-10-player.x);
    d[4]=(enemy.y-player.y)*(enemy.y-player.y)+(enemy.x+10-player.x)*(enemy.x+10-player.x);
    for(i=1;i<5;i++){
            if(d[n]>d[i])n=i;
    }
    switch (n) {
    case 2:return UP;break;
    case 1:return DOWN;break;
    case 3:return LEFT;break;
    case 4:return RIGHT;break;
    default:qDebug()<<"wrong";return UP;
    }
}

void BattleWindow::Mist_Generate(){
    if(fix.isActive())return;
    int i;
    for(i=0;i<5;i++){
        switch (P1.GetHead()) {
        case UP:
            CreatePartical(XY(QRandomGenerator::global()->bounded(P1.GetPos().x-10,P1.GetPos().x+40),
                              QRandomGenerator::global()->bounded(P1.GetPos().y+30,P1.GetPos().y+50)),
                           XY(20,20),Type::Mist);
            break;
        case DOWN:
            CreatePartical(XY(QRandomGenerator::global()->bounded(P1.GetPos().x-10,P1.GetPos().x+40),
                              QRandomGenerator::global()->bounded(P1.GetPos().y-20,P1.GetPos().y)),
                           XY(20,20),Type::Mist);
            break;
        case LEFT:
            CreatePartical(XY(QRandomGenerator::global()->bounded(P1.GetPos().x+30,P1.GetPos().x+50),
                              QRandomGenerator::global()->bounded(P1.GetPos().y-10,P1.GetPos().y+40)),
                           XY(20,20),Type::Mist);
            break;
        case RIGHT:
            CreatePartical(XY(QRandomGenerator::global()->bounded(P1.GetPos().x-20,P1.GetPos().x),
                              QRandomGenerator::global()->bounded(P1.GetPos().y-10,P1.GetPos().y+40)),
                           XY(20,20),Type::Mist);
            break;
        }

    }
    /*for(i=0;i<Edit_Max;i++){
        if(!enemy[i].GetAlive())continue;
        for(k=0;k<2;k++)
            CreatePartical(XY(QRandomGenerator::global()->bounded(enemy[i].GetPos().x-10,enemy[i].GetPos().x+enemy[i].GetArea().x+10),
                              QRandomGenerator::global()->bounded(enemy[i].GetPos().y-10,enemy[i].GetPos().y+enemy[i].GetArea().y+10)),
                           XY(20,20),Type::Mist);
    }*/
}

void BattleWindow::Command(QString command){
    if(command=="/help"){
        QMessageBox::information(nullptr,tr("帮助"),tr("指令：\n"
                                                     "/CreatePartical x坐标 y坐标 长度 宽度 种类\n"
                                                     "/CreateEnemy x坐标 y坐标 长度 宽度 HP 移速 子弹速度 皮肤\n"
                                                     "/CreateObject x坐标 y坐标 长度 宽度 种类 皮肤\n"
                                                     "/CreateRedZone x坐标 y坐标 爆炸半径 种类\n"
                                                     "/CreateBoss x坐标 y坐标 血量\n"
                                                     "/skip 跳到的关卡\n"
                                                     "/Strengthen HP MP 武器等级 原材料 速度 子弹上限\n"
                                                     "/help 帮助\n"), tr("好"));
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
        if(commandlist[1]=="Strengthen"){
            mode=7;
        }
    }else{
        QMessageBox::information(nullptr,tr("帮助"),tr("指令错误"), tr("好"));
        return;
    }
    switch (mode) {
    case 1:
        CreatePartical(XY(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10)),
                XY(commandlist[4].toInt(nullptr,10),commandlist[5].toInt(nullptr,10)),Type(commandlist[6].toInt(nullptr,10)));
        break;
    case 2:
        CreateEnemy(XY(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10)),
                XY(commandlist[4].toInt(nullptr,10),commandlist[5].toInt(nullptr,10)),
                commandlist[6].toInt(nullptr,10),
                commandlist[7].toInt(nullptr,10),
                commandlist[8].toInt(nullptr,10),
                commandlist[9].toInt(nullptr,10));
        break;
    case 3:
        CreateObject(XY(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10)),
                XY(commandlist[4].toInt(nullptr,10),commandlist[5].toInt(nullptr,10)),
                commandlist[6].toInt(nullptr,10),
                commandlist[7].toInt(nullptr,10),10
                );
        break;
    case 4:
        CreateRedZone(XY(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10)),commandlist[4].toInt(nullptr,10),1);
        break;
    case 5:
        new(boss1)Boss1(XY(commandlist[2].toInt(nullptr,10),commandlist[3].toInt(nullptr,10)),
                commandlist[4].toInt(nullptr,10),1);
        break;
    case 6:
        ClearMap(XY(0,0));
        Win=true;
        LevelB=commandlist[2].toInt(nullptr,10);
        this->MissionRougueLike_Win();
        break;
    case 7:
        P1.Strengthen(commandlist[2].toInt(nullptr,10),
                commandlist[3].toInt(nullptr,10),
                commandlist[4].toInt(nullptr,10),
                commandlist[5].toInt(nullptr,10),
                commandlist[6].toInt(nullptr,10),
                commandlist[7].toInt(nullptr,10));
        break;
    }


}
