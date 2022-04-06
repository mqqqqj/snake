#include "snake.h"

snake::snake(QWidget* parent)//构造函数
    : QMainWindow(parent)
    , ui(new Ui::snakeClass)
{
    ui->setupUi(this);
    this->setGeometry(QRect(600, 300, 290, 310));//设置窗体显示位置
}

snake::~snake()
{
    delete ui;
}

void snake::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (!blsRun) {
        Initsnake();
    }
    //draw background
    //outside
    painter.setPen(Qt::black);//set the color of the pen
    painter.setBrush(Qt::gray);
    painter.drawRect(15, 15, 260, 260);//start point(compare to the window),width,height
    //inside
    painter.setPen(Qt::black);//set the color of the pen
    painter.setBrush(Qt::white);
    painter.drawRect(20, 20, 250, 250);//start point(compare to the window),width,height
    painter.drawPixmap(20, 20, 250, 250, QPixmap(":/snake/bg.jpg"));

    //draw pane 10*10
    painter.setPen(Qt::black);
    for (int i = 2; i <= 27; i++) {
        painter.drawLine(20, 10 * i, 270, 10 * i);
        painter.drawLine(10 * i, 20, 10 * i, 270);
    }
    //显示游戏开始和结束
    QFont font1("楷体", 20);
    painter.setFont(font1);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    //painter.drawRect(food);
    painter.drawPixmap(food, QPixmap(":/snake/apple.png"));
    painter.drawText(40, 150, sDisplay);
    //得分显示
    QFont font2("楷体", 10);
    painter.setFont(font2);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawText(50, 300, scorelabel);
    painter.drawText(220, 300, QString::number(nScore));
    //draw snake
    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    //:/snake/C:/Users/Lenovo/Desktop/snake1/img/bg.jpg
    painter.drawRects(&vsnake[0], vsnake.size());
    if (blsOver) {
        timer->stop();
    }
}

void snake::Initsnake() {
    nDirection = 2;
    blsRun = true;
    blsOver = false;
    sDisplay = "START";
    food = creatRect();
    vsnake.resize(5);
    //用一个for循环初始化蛇
    for (int i = 0; i < vsnake.size(); i++) {
        QRect rect(100, 70 + 10 * i, 10, 10);
        vsnake[vsnake.size() - 1 - i] = rect;
    }
    snakehead = vsnake.first();
    timer = new QTimer(this);//设定定时器
    timer->start(500);//计时器时间是500ms
    connect(timer, SIGNAL(timeout()), SLOT(snake_update()));//信号连接槽，发出信号的是timer，信号是timeout，执行的槽是snake_update
}


void snake::keyPressEvent(QKeyEvent* event) {
    QKeyEvent* key = (QKeyEvent*)event;
    switch (key->key()) {
    case Qt::Key_Up: nDirection = 1;//上
        break;
    case Qt::Key_Down: nDirection = 2;//下
        break;
    case Qt::Key_Left: nDirection = 3;//左
        break;
    case Qt::Key_Right: nDirection = 4;//右
        break;
    default:;
    }
}


void snake::snake_update() {
    sDisplay = "";
    snakehead = vsnake.first();//获取蛇头
    iseat();
    ishit();
    for (int j = 0; j < vsnake.size() - 1; j++)
        vsnake[vsnake.size() - 1 - j] = vsnake[vsnake.size() - 2 - j];
    if (nDirection == lastDirection)
        if (speed > 150)
            speed -= 10;
    switch (nDirection) {
    case 1:
        snakehead.setTop(snakehead.top() - 10);
        snakehead.setBottom(snakehead.bottom() - 10);
        break;
    case 2:
        snakehead.setTop(snakehead.top() + 10);
        snakehead.setBottom(snakehead.bottom() + 10);
        break;
    case 3:
        snakehead.setLeft(snakehead.left() - 10);
        snakehead.setRight(snakehead.right() - 10);
        break;
    case 4:
        snakehead.setLeft(snakehead.left() + 10);
        snakehead.setRight(snakehead.right() + 10);
    default:;
    }
    lastDirection = nDirection;
    vsnake[0] = snakehead;
    if (snakehead.left() < 20 || snakehead.right() > 270 || snakehead.top() < 20 || snakehead.bottom() > 270) {
        sDisplay = "Snake died...";
        blsOver = true;
    }
    update();
}

QRect snake::creatRect() {//写一个判断生成的苹果是否在蛇内部
    while (true) {
        int x = qrand() % 25;
        int y = qrand() % 25;
        QRect rect(20 + x * 10, 20 + y * 10, 10, 10);
        bool flag = true;
        for (int i = 0; i < vsnake.size(); i++) {
            if (rect == vsnake[i])flag = false;
        }
        if (flag)return rect;
    }
}


void snake::iseat() {
    if (snakehead == food) {
        snakehead = food;
        vsnake.push_back(vsnake.last());
        food = creatRect();
        nScore += 10;
        if (speed >= 150) {
            speed -= 10;
            timer->stop();
            timer->start(speed);
        }
    }
}

void snake::ishit() {
    for (int i = 1; i < vsnake.size(); i++) {
        if (snakehead == vsnake[i]) {
            sDisplay = "Snake died...";
            blsOver = true;
            update();
        }
    }
}
