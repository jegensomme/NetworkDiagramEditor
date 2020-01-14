#include "inputconnector.h"

InputConnector::InputConnector(Qt::GlobalColor color)
    : connectorId(0), equipmentId(0), color(color), link(nullptr)
{

}

InputConnector::~InputConnector()
{

}

Qt::GlobalColor InputConnector::GetColor()
{
    return color;
}

QRectF InputConnector::boundingRect() const
{
    return QRectF (0,0,20,20);
}

void InputConnector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
    // Помещаем координаты точек в полигональную модель
    polygon << QPoint(0,0) << QPoint(0,20) << QPoint(20,10);
    painter->setBrush(color);     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon);  // Рисуем треугольник по полигональной модели
    Q_UNUSED(option);
    Q_UNUSED(widget);
}



InputConnectorRed::InputConnectorRed()
    : InputConnector (Qt::red)
{

}

InputConnectorBlue::InputConnectorBlue()
    : InputConnector (Qt::blue)
{

}

InputConnectorGreen::InputConnectorGreen()
    : InputConnector (Qt::green)
{

}

InputConnectorCyan::InputConnectorCyan()
    : InputConnector (Qt::cyan)
{

}

InputConnectorYellow::InputConnectorYellow()
    : InputConnector (Qt::yellow)
{

}
