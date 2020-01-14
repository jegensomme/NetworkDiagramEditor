#include "outputconnector.h"

OutputConnector::OutputConnector(Qt::GlobalColor color)
    : connectorId(0), equipmentId(0), color(color), link(nullptr)
{

}

OutputConnector::~OutputConnector()
{

}

Qt::GlobalColor OutputConnector::GetColor()
{
    return color;
}

QRectF OutputConnector::boundingRect() const
{
    return QRectF (0,0,20,20);
}

void OutputConnector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(0);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawRect(0,0,20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


OutputConnectorRed::OutputConnectorRed()
    : OutputConnector (Qt::red)
{

}

OutputConnectorBlue::OutputConnectorBlue()
    : OutputConnector (Qt::blue)
{

}

OutputConnectorGreen::OutputConnectorGreen()
    : OutputConnector (Qt::green)
{

}

OutputConnectorCyan::OutputConnectorCyan()
    : OutputConnector (Qt::cyan)
{

}

OutputConnectorYellow::OutputConnectorYellow()
    : OutputConnector (Qt::yellow)
{

}
