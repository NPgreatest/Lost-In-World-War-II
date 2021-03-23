#ifndef ALLMUSIC_H
#define ALLMUSIC_H
#include<QMediaPlayer>
#include<QRandomGenerator>
#include"All.h"


class AllMusic
{
private:
    QMediaPlayer BackMuisc;
    QMediaPlayer FireMusic;
    QMediaPlayer *HitMusic;
    QMediaPlayer *Hit2Music;
    QMediaPlayer *RedZoneMusic;
public:
    AllMusic();
    ~AllMusic();
    void PlayBackMusic(int x);
    void AddHitMusic();
    void PlayHitMusic(int x);
    void AddHit2Music();
    void PlayHit2Music(int x);
    void AddRedZoneMusic();
    void PlayRedZoneMusic(int x);
    void PlayFireMusic(int x);
};

#endif // ALLMUSIC_H
