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
    void snake_update();//����ۺ���


private:
    Ui::snakeClass* ui;
    QVector<QRect> vsnake;
    QRect snakehead;
    void keyPressEvent(QKeyEvent* key);//��������¼�
    QTimer* timer;//��ʱ��
    bool blsRun = false;//�Ƿ�ʼ�ƶ�
    bool blsOver;
    QString sDisplay;
    QRect food;
    int nScore = 0;
    int speed = 500;
    QString scorelabel = "Current Score: ";
    int nDirection;//����
    int lastDirection = 1;

};
#endif // SNAKE_H
