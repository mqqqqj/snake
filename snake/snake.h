#ifndef SNAKE_H
#define SNAKE_H
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "ui_snake.h"
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include<QKeyEvent>
#include<vector>
#include<QString>
namespace Ui { class snakeClass; }

class snake : public QMainWindow
{
    Q_OBJECT

public:
    snake(QWidget* parent = nullptr);
    ~snake();
    void paintEvent(QPaintEvent* event);
    void Initsnake();
    QRect creatRect();
    void iseat();
    void ishit();
private slots:
    void snake_update();//定义槽函数


private:
    Ui::snakeClass* ui;
    QVector<QRect> vsnake;
    QRect snakehead;
    void keyPressEvent(QKeyEvent* key);//定义键盘事件
    QTimer* timer;//定时器
    bool blsRun = false;//是否开始移动
    bool blsOver;
    QString sDisplay;
    QRect food;
    int nScore = 0;
    int speed = 500;
    QString scorelabel = "Current Score: ";
    int nDirection;//方向
    int lastDirection = 1;

};
#endif // SNAKE_H
