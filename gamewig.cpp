#include "gamewig.h"
#include "mainwindow.h"
#include <QPainter>
#include "ui_mainwindow.h"
const int gridSize = 5;
const int CEN_W = 401;
const int CEN_H = 361;

gameWig::gameWig(QWidget *parent) : QWidget(parent)
{
    hGrid = height()/gridSize;
    wGrid = width()/gridSize;
    for(int i=1;i<=1500;i++)
        for(int j=1;j<=1500;j++) {
            double tmp = rand() % 1000 * 1.0/ float(1000); //1000决定精度，三位小数
            if (tmp <= ratio) {
                // 生成细胞
                value[i][j] = 1;
            }
            else
                value[i][j] = 0;
        }
    cen_w = CEN_W;
    cen_h = CEN_H;
}

void gameWig::init() {
    for(int i=1;i<=1500;i++)
        for(int j=1;j<=1500;j++) {
            double tmp = rand() % 1000 * 1.0/ float(1000); //1000决定精度，三位小数
            if (tmp <= ratio) {
                // 生成细胞
                value[i][j] = 1;
            }
            else
                value[i][j] = 0;
        }
    Parent->ui->widget->setGeometry(cen_w-width()/2,cen_h-height()/2,width(),height());
}


void gameWig::paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::blue,1));
        for(int i=0;i<=height();i++)
        {
            painter.drawLine(i*gridSize,0,i*gridSize,height()*gridSize);
        }
        for(int j=0;j<=width();j++)
        {
            painter.drawLine(0,j*gridSize,width()*gridSize,j*gridSize);
        }
        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
        for(int i=1;i<=height();i++)
            for(int j=1;j<=width();j++)
                if(value[i][j])
                    painter.drawRect((i-1)*gridSize,(j-1)*gridSize,gridSize,gridSize);
}

int gameWig::sum(int i, int j) {
    int cnt = 0;
    if (value[i][j-1]) cnt++;
    if (value[i][j+1]) cnt++;
    if (value[i-1][j]) cnt++;
    if (value[i+1][j]) cnt++;
    if (value[i-1][j-1]) cnt++;
    if (value[i-1][j+1]) cnt++;
    if (value[i+1][j-1]) cnt++;
    if (value[i+1][j+1]) cnt++;

    return cnt;
}

void gameWig::evolve() {
    // copy
    for (int i = 0; i < 1505; ++i) {
        for (int j = 0; j < 1505; ++j) {
            tmpVal[i][j] = value[i][j];
        }
    }

    for (int i = 1; i <= 1500; ++i) {
        for (int j = 1; j <= 1500; ++j) {
            int tmp = sum(i,j);
            if (tmp <= few) {
                if (value[i][j]) tmpVal[i][j] = 0;
            }
            else if (tmp == born) {
                if (!value[i][j]) tmpVal[i][j] = 1;
            }
            else if (tmp >= many) {
                if (value[i][j]) tmpVal[i][j] = 0;
            }
        }
    }

    // copy back
    for (int i = 0; i < 1505; ++i) {
        for (int j = 0; j < 1505; ++j) {
            value[i][j] = tmpVal[i][j];
        }
    }
}
