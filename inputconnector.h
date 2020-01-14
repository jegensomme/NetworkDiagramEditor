#ifndef INPUTCONNECTOR_H
#define INPUTCONNECTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class OutputConnector;

class InputConnector : public QObject, public QGraphicsItem
{
public:
    InputConnector(Qt::GlobalColor color);
    ~InputConnector();
    Qt::GlobalColor GetColor();
    int connectorId;
    int equipmentId;
private:
    Qt::GlobalColor color;
    OutputConnector *link;
    /* Данные методы виртуальные, поэтому их необходимо реализовать
     * в случае наследования от QGraphicsItem
     * */
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class InputConnectorRed : public InputConnector
{
public:
    InputConnectorRed();
};

class InputConnectorBlue : public InputConnector
{
public:
    InputConnectorBlue();
};

class InputConnectorGreen : public InputConnector
{
public:
    InputConnectorGreen();
};

class InputConnectorCyan : public InputConnector
{
public:
    InputConnectorCyan();
};

class InputConnectorYellow : public InputConnector
{
public:
    InputConnectorYellow();
};

#endif // INPUTCONNECTOR_H
