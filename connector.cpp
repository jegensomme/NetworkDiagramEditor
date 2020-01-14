#include "connector.h"

Connector::Connector(Qt::GlobalColor color)
    : color(color), link(nullptr), connectorId(0), equipmentId(0)
{
    setFlag(ItemIsSelectable);
}

Connector::~Connector()
{

}

Qt::GlobalColor Connector::get_color()
{
    return color;
}

void Connector::set_link(Connector *connector)
{
    link = connector;
}

Connector* Connector::get_link()
{
    return link;
}

void Connector::set_connectorId(int id)
{
    connectorId = id;
}

int Connector::get_connectorId()
{
    return connectorId;
}

void Connector::set_equipmentId(int id)
{
    equipmentId = id;
}

int Connector::get_equipmentId()
{
    return equipmentId;
}

void Connector::set_description(QString text)
{
    description = text;
}

QString Connector::get_description()
{
    return description;
}

void Connector::set_name(QString text)
{
    name = text;
}
QString Connector::get_name()
{
    return name;
}

bool Connector::contains(const QVector <Connector*> &connectors, Qt::GlobalColor color)
{
    foreach(Connector *connector_in, connectors)
    {
        if(connector_in->color == color)
            return true;
    }

    return false;
}

Connector* Connector::set_color(Qt::GlobalColor color)
{
    Connector *connector = nullptr;

    switch (color)
    {
    case Qt::red:
    {
        connector = new ConnectorRed();
        break;
    }
    case Qt::darkRed:
    {
        connector = new ConnectorDarkRed();
        break;
    }
    case Qt::blue:
    {
        connector = new ConnectorBlue();
        break;
    }
    case Qt::darkBlue:
    {
        connector = new ConnectorDarkBlue();
        break;
    }
    case Qt::green:
    {
        connector = new ConnectorGreen();
        break;
    }
    case Qt::darkGreen:
    {
        connector = new ConnectorDarkGreen();
        break;
    }
    case Qt::cyan:
    {
        connector = new ConnectorCyan();
        break;
    }
    case Qt::darkCyan:
    {
        connector = new ConnectorDarkCyan();
        break;
    }
    case Qt::yellow:
    {
        connector = new ConnectorYellow();
        break;
    }
    case Qt::darkYellow:
    {
        connector = new ConnectorDarkYellow();
        break;
    }
    case Qt::gray:
    {
        connector = new ConnectorGray();
        break;
    }
    case Qt::darkGray:
    {
        connector = new ConnectorDarkGray();
        break;
    }
    case Qt::magenta:
    {
        connector = new ConnectorMagenta();
        break;
    }
    case Qt::darkMagenta:
    {
        connector = new ConnectorDarkMagenta();
        break;
    }
    default:
    {
        return nullptr;
    }
    }

    return connector;
}

int Connector::Connector::type() const
{
    return Type;
}

QRectF Connector::boundingRect() const
{
    return QRectF (0,0,20,20);
}

void Connector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(isSelected() ? 4 : 0);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawRect(0,0,20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

ConnectorRed::ConnectorRed()
    : Connector (Qt::red)
{

}

ConnectorDarkRed::ConnectorDarkRed()
    : Connector (Qt::darkRed)
{

}

ConnectorBlue::ConnectorBlue()
    : Connector (Qt::blue)
{

}

ConnectorDarkBlue::ConnectorDarkBlue()
    : Connector (Qt::darkBlue)
{

}

ConnectorGreen::ConnectorGreen()
    : Connector (Qt::green)
{

}

ConnectorDarkGreen::ConnectorDarkGreen()
    : Connector (Qt::darkGreen)
{

}

ConnectorCyan::ConnectorCyan()
    : Connector (Qt::cyan)
{

}

ConnectorDarkCyan::ConnectorDarkCyan()
    : Connector (Qt::darkCyan)
{

}

ConnectorYellow::ConnectorYellow()
    : Connector (Qt::yellow)
{

}

ConnectorDarkYellow::ConnectorDarkYellow()
    : Connector (Qt::darkYellow)
{

}

ConnectorGray::ConnectorGray()
    : Connector (Qt::gray)
{

}

ConnectorDarkGray::ConnectorDarkGray()
    : Connector (Qt::darkGray)
{

}

ConnectorMagenta::ConnectorMagenta()
    : Connector (Qt::magenta)
{

}

ConnectorDarkMagenta::ConnectorDarkMagenta()
    : Connector (Qt::darkMagenta)
{

}
