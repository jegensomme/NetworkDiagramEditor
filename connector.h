#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>


/**
 * Класс для описания коннектора
 */

class Connector : public QObject, public QGraphicsItem
{
public:
    Connector(Qt::GlobalColor color);// инициализация стандартного цвета и флага.
    ~Connector() override;

    // инициализация типа объекта
    enum {
        Type = UserType + 12
    };
    int type() const override;// возвращает тип объекта

    Qt::GlobalColor get_color();// возвращает тип коннектора
    void set_link(Connector *connector);// утанавливает связь с другим коннектором
    Connector* get_link();// возвращает соединенный коннектор
    void set_connectorId(int id);// утанавливает id
    int get_connectorId();// возвращает id
    void set_equipmentId(int id);// устанавливает id оборудования
    int get_equipmentId();// возвращает id оборудования
    void set_description(QString text);// устанавливает описание
    QString get_description();// возвращает описание
    void set_name(QString text);// устанавливает название
    QString get_name();// возвращает название

    static Connector* set_color(Qt::GlobalColor color);// устанавливает тип коннектора
    static bool contains(const QVector <Connector*> &connectors, Qt::GlobalColor color);// проверка на наличие данного типа коннектора

private:
    Qt::GlobalColor color;// тип коннектора
    QString name = nullptr;
    Connector *link;// связанный коннектор
    int connectorId;
    int equipmentId ;
    QString description = nullptr;
    QRectF boundingRect() const override;// рабочая область (квадрат)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;// отрисовка коннектора
};

//классы в соответствии с типами отвечают за создание коннекторов
class ConnectorRed : public Connector
{
public:
    ConnectorRed();
};

class ConnectorDarkRed : public Connector
{
public:
    ConnectorDarkRed();
};

class ConnectorBlue : public Connector
{
public:
    ConnectorBlue();
};

class ConnectorDarkBlue : public Connector
{
public:
    ConnectorDarkBlue();
};

class ConnectorGreen : public Connector
{
public:
    ConnectorGreen();
};

class ConnectorDarkGreen : public Connector
{
public:
    ConnectorDarkGreen();
};

class ConnectorCyan : public Connector
{
public:
    ConnectorCyan();
};

class ConnectorDarkCyan : public Connector
{
public:
    ConnectorDarkCyan();
};

class ConnectorYellow : public Connector
{
public:
    ConnectorYellow();
};

class ConnectorDarkYellow : public Connector
{
public:
    ConnectorDarkYellow();
};

class ConnectorGray : public Connector
{
public:
    ConnectorGray();
};

class ConnectorDarkGray : public Connector
{
public:
    ConnectorDarkGray();
};

class ConnectorMagenta : public Connector
{
public:
    ConnectorMagenta();
};

class ConnectorDarkMagenta : public Connector
{
public:
    ConnectorDarkMagenta();
};

#endif // CONNECTOR_H
