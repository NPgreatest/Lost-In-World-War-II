#include"All.h"
extern QImage SetAlpha(QImage img, int alpha){
    QPixmap pix = QPixmap::fromImage(img);
    QPixmap tmpPix(pix.size());
    tmpPix.fill(Qt::transparent);
    QPainter p1(&tmpPix);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, pix);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(tmpPix.rect(), QColor(0, 0, 0, alpha));
    p1.end();
    img= tmpPix.toImage();
    return img;
}

extern QImage Image_Transparent(QImage image,int x){
    if(x>255)x=255;
    image = image.convertToFormat(QImage::Format_ARGB32);
    union myrgb
    {
        uint rgba;
        uchar rgba_bits[4];
    };
        myrgb* mybits =(myrgb*) image.bits();
        int len = image.width()*image.height();
    while(len --> 0)
    {
        mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:x;
        mybits++;
    }
    return image;
}
extern HEAD AI1(QRect Player,QRect Enemy){
    int d[5],i,n=0;
    d[0]=(Enemy.y()-Player.y())*(Enemy.y()-Player.y())+(Enemy.x()-Player.x())*(Enemy.x()-Player.x());
    d[1]=(Enemy.y()+10-Player.y())*(Enemy.y()+10-Player.y())+(Enemy.x()-Player.x())*(Enemy.x()-Player.x());
    d[2]=(Enemy.y()-10-Player.y())*(Enemy.y()-10-Player.y())+(Enemy.x()-Player.x())*(Enemy.x()-Player.x());
    d[3]=(Enemy.y()+-Player.y())*(Enemy.y()-Player.y())+(Enemy.x()-10-Player.x())*(Enemy.x()-10-Player.x());
    d[4]=(Enemy.y()-Player.y())*(Enemy.y()-Player.y())+(Enemy.x()+10-Player.x())*(Enemy.x()+10-Player.x());
    for(i=1;i<5;i++){
            if(d[n]>d[i])n=i;
    }
    switch (n) {
        case 2:return UP;break;
        case 1:return DOWN;break;
        case 3:return LEFT;break;
        case 4:return RIGHT;break;
        default:return UP;
    }
}
