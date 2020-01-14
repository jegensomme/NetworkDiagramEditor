#ifndef BODY_H
#define BODY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

/**
 * Класс предназначен для работы с "телом" оборудования
 * В классе происходит инициализация всех необходимых данных для работы с "телом" оборудования.
 * Инициализируется количество пар слотов (портов коннекторов) в высоту, высота в пикселях, id оборудования.
 * Также в классе происходит обработка событий перемещения тела, нажатия (отжатия) левой кнопки мыши по телу объекта, координат предшевствующего положения мыши.
 * Для коммуникации между объектами в классе присутвуют 2 сигнала: сигнал выбора тела, сигнал движения тела.
 */

class Body  : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Body(int size);// инициализируются размеры и устанавлвается флаг

public:
    // инициализация типа объекта
    enum {
        Type = UserType + 11
    };
    int type() const override;// возвращает тип объекта

    void set_id(int id);// устанавливает id объекта
    int get_id();// вохвращает id объекта

private:
    int id;
    int size;// количество пар слотов в высоту
    int height;// высота в пикселях
    QPointF m_shiftMouseCoords;// координаты точки нажатия по body
    QRectF boundingRect() const override;// рабочая область (в виде прямоугольника)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;// отрисовка тела оборудования
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;// реакция на перемещение тела
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;// реакция на нажатие на тело
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;// реакция на отпускание кнопки мыши
    QPointF m_previousPosition;// координаты предшевствующего положения мыши

signals:
    void signalMove(QGraphicsItem *signalOwner, qreal dx, qreal dy);
};

#endif // BODY_H
