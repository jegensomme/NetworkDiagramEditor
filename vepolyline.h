#ifndef VEPOLYLINE_H
#define VEPOLYLINE_H

#include <QObject>
#include <QGraphicsPathItem>
#include <body.h>

class DotSignal;
class QGraphicsSceneMouseEvent;

/**
 * Класс описывает ломанную линию
 * При создании класса инициализируется стандартными параметрами 1 и 2 коннекторы.
 * Класс работает с сигналами, чтобы происходило корректное перемещение объектов по рабочей области. Помимо этого используются функции устанавливающии текущую и предыдущую позицию вершины ломанной
 */

class VEPolyline : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    // Инициализация ломанной линии
    explicit VEPolyline(Body *first = nullptr, Body *end = nullptr, QObject *parent = nullptr);

    // инициализация типа объекта
    enum {
        Type = UserType + 10
    };
    int type() const override;// возвращает тип объекта

    QPointF previousPosition() const;// возвращает предыдущую позицию
    void setPreviousPosition(const QPointF previousPosition);// устанавливает предыдущую позицию
    void setPath(const QPainterPath &path);// установка пути ломанной
    QList<DotSignal *> listDotes;// возвращает массив вершин
    void set_connectionId(int id);// устанавливает id соединения
    int get_connectionId();// возвращает id соединения
    void set_connectorIdFirst(int id);// устанавливает id первого коннектора
    int get_connectorIdFirst();// возвращает id певрого коннектора
    void set_connectorIdEnd(int id);// устанавливает id второго коннектора
    int get_connectorIdEnd();// возвращает id второго коннекора
    void set_description(QString text);//  устанавливает описание соединения
    QString get_description();// возвращает описание соединения
    Body* get_first();// возвращает указатель на первый коннектор
    Body* get_end();// возвращает указатель на второй коннектор

signals:
    void previousPositionChanged();// предыдущая позиция изменилась
    void clicked(VEPolyline *rect);// клик по ломанной линии
    void signalMove(QGraphicsItem *item, qreal dx, qreal dy);// изменилась позиция веришны ломанной линии

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;// создание новой вершины ломанной
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;// выход курсора из области
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;// создание отображаемых вершин при наведении курсора мыши
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;// пересечение с курсором мыши

private slots:
    void slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy);//
    void checkForDeletePoints();//

private:
    Body *first;// указатель на первый коннектор
    Body *end;// указатель на первый коннектор
    int connectorIdFirst;
    int connectorIdEnd;
    int connectionId;
    QString description;
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    int m_pointForCheck = -1;

private:
    void updateDots();//
};

#endif // VEPOLYLINE_H
