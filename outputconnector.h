#ifndef OUTPUTCONNECTOR_H
#define OUTPUTCONNECTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class InputConnector;

class OutputConnector : public QObject, public QGraphicsItem
{
public:
    OutputConnector(Qt::GlobalColor color);
    ~OutputConnector();
    Qt::GlobalColor GetColor();
    int connectorId;
    int equipmentId;
private:
    Qt::GlobalColor color;
    InputConnector *link;
    /* Данные методы виртуальные, поэтому их необходимо реализовать
     * в случае наследования от QGraphicsItem
     * */
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class OutputConnectorRed : public OutputConnector
{
public:
    OutputConnectorRed();
};

class OutputConnectorBlue : public OutputConnector
{
public:
    OutputConnectorBlue();
};

class OutputConnectorGreen : public OutputConnector
{
public:
    OutputConnectorGreen();
};

class OutputConnectorCyan : public OutputConnector
{
public:
    OutputConnectorCyan();
};

class OutputConnectorYellow : public OutputConnector
{
public:
    OutputConnectorYellow();
};

#endif // OUTPUTCONNECTOR_H
