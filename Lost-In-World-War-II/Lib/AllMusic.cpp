#include "AllMusic.h"

AllMusic::AllMusic()
{
    BackMuisc.setMedia(QUrl("qrc:/sounds/sounds/BattleMusic1.mp3"));
    FireMusic.setMedia(QUrl("qrc:/sounds/sounds/fire.mp3"));
}

AllMusic::~AllMusic(){
    delete HitMusic;
    delete Hit2Music;
    delete RedZoneMusic;
}

void AllMusic::PlayBackMusic(int x){
    if(BackMuisc.state()==QMediaPlayer::PlayingState)
        return;
    BackMuisc.setVolume(x);
    BackMuisc.play();
}

void AllMusic::AddHitMusic(){
    HitMusic=new QMediaPlayer[MEDIA_MAX];
    int i;
    for(i=0;i<MEDIA_MAX;i++){
        switch (QRandomGenerator::global()->bounded(1,6)) {
        case 1:HitMusic[i].setMedia(QUrl("qrc:/sounds/sounds/hit1.mp3"));break;
        case 2:HitMusic[i].setMedia(QUrl("qrc:/sounds/sounds/hit2.mp3"));break;
        case 3:HitMusic[i].setMedia(QUrl("qrc:/sounds/sounds/hit3.mp3"));break;
        case 4:HitMusic[i].setMedia(QUrl("qrc:/sounds/sounds/hit4.mp3"));break;
        default:HitMusic[i].setMedia(QUrl("qrc:/sounds/sounds/hit5.mp3"));break;
        }

    }
}
void AllMusic::PlayHitMusic(int x){
    int i;
    for(i=0;i<MEDIA_MAX;i++){
        if(HitMusic[i].state()==QMediaPlayer::PlayingState) continue;
        HitMusic[i].setVolume(x);
        HitMusic[i].play();
        break;
    }
}
void AllMusic::AddHit2Music(){
    Hit2Music=new QMediaPlayer[MEDIA_MAX];
    int i;
    for(i=0;i<MEDIA_MAX;i++){
        switch (QRandomGenerator::global()->bounded(1,6)) {
        case 1:Hit2Music[i].setMedia(QUrl("qrc:/sounds/sounds/explo1.mp3"));break;
        case 2:Hit2Music[i].setMedia(QUrl("qrc:/sounds/sounds/explo2.mp3"));break;
        case 3:Hit2Music[i].setMedia(QUrl("qrc:/sounds/sounds/explo3.mp3"));break;
        case 4:Hit2Music[i].setMedia(QUrl("qrc:/sounds/sounds/explo4.mp3"));break;
        default:Hit2Music[i].setMedia(QUrl("qrc:/sounds/sounds/explo5.mp3"));break;
        }
    }
}
void AllMusic::PlayHit2Music(int x){
    int i;
    for(i=0;i<MEDIA_MAX;i++){
        if(Hit2Music[i].state()==QMediaPlayer::PlayingState) continue;
        Hit2Music[i].setVolume(x);
        Hit2Music[i].play();
        break;
    }
}
void AllMusic::AddRedZoneMusic(){
    RedZoneMusic=new QMediaPlayer[MEDIA_MAX];
    int i;
    for(i=0;i<MEDIA_MAX;i++){
        RedZoneMusic[i].setMedia(QUrl("qrc:/sounds/sounds/RedZone.mp3"));
    }
}
void AllMusic::PlayRedZoneMusic(int x){
    int i;
    for(i=0;i<MEDIA_MAX;i++){
        if(RedZoneMusic[i].state()==QMediaPlayer::PlayingState) continue;
        RedZoneMusic[i].setVolume(x);
        RedZoneMusic[i].play();
        break;
    }
}
void AllMusic::PlayFireMusic(int x){
    if(FireMusic.state()==QMediaPlayer::PlayingState)
        return;
    FireMusic.setVolume(x);
    FireMusic.play();
}
