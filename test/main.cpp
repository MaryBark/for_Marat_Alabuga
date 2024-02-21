#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.resize(800, 600);

    // Создание стены
    QGraphicsRectItem *wall = new QGraphicsRectItem(200, 100, 10, 400); // x, y, width, height
    scene.addItem(wall);

    // Создание стены
    QGraphicsRectItem *wall1 = new QGraphicsRectItem(10, 400, 200, 100); // x, y, width, height
    scene.addItem(wall1);

    // Создание мяча
    QGraphicsEllipseItem *sword = new QGraphicsEllipseItem(50, 250, 20, 20); // x, y, width, height
    sword->setBrush(QColor(Qt::red));
    scene.addItem(sword);

    // Начальные параметры движения
    double x = 50; // Начальная позиция по x
    double y = 250; // Начальная позиция по y
    double vx = 5; // Скорость по x
    double vy = -1; // Скорость по y
    double g = 0.2; // Ускорение свободного падения

    // Создаем пунтирную траекторию в виде шара
    QPen pen(Qt::black);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        // Рассчитываем новое положение меча
        x += vx;
        y += vy;
        vy += g;

        // Проверяем отскок от стены
        if (x >= 200 && x <= 210 && y >= 100 && y <= 500)
        {
            x = 200; // При столкновении меняем координату x на позицию стены
            vx = -vx * 0.8; // Инвертируем скорость и замедляем
        }

//        if (x >= 10 && x <= 400 && y >= 200 && y <= 100)
//        {
//            x = 200; // При столкновении меняем координату x на позицию стены
//            vx = -vx * 0.8; // Инвертируем скорость и замедляем
//        }


        QGraphicsEllipseItem *trail = new QGraphicsEllipseItem(x, y, 20, 20); // Создаем след
        trail->setPen(pen); // Устанавливаем пунтирную линию
        scene.addItem(trail);

        // Обновляем координаты шарика
//        sword->setPos(x + 5, y + 5); // Двигаем шарик
        sword->setRect(x, y, 20, 20); // Обновляем позицию меча
        scene.update(); // Обновляем сцену
    });

    timer.start(30); // Устанавливаем частоту обновления экрана

    view.show();

    return a.exec();
}


