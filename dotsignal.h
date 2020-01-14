#ifndef DOTSIGNAL_H
#define DOTSIGNAL_H

#include <QObject>
#include <QGraphicsRectItem>

class QGraphicsSceneHoverEventPrivate;
class QGraphicsSceneMouseEvent;

/**
 * Класс описывает вершины ломанной
 *
 * При создании класса происходит создание вершины со стандартными параметрами.
 * Класс работает с флагами состояний и сигналами, позволяющими двигать объект согласовано с другими объектами.
 */

class DotSignal : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    /*
     * DotSignal - создание вершины ломанной
     * parentItem - родительский предмет
     * parent - объект
     */
    explicit DotSignal(QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);
    /*
     * DotSignal - создание вершины ломанной с определенной позицией
     * pos - позиция
     * parentItem - родительский предмет
     * parent - объект
     */
    explicit DotSignal(QPointF pos, QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);
    ~DotSignal() override;

    // стандартный флаг, позволяющий двигать объекты
    enum Flags {
        Movable = 0x01
    };

    QPointF previousPosition() const;// возвращает предыдущую позицию
    void setPreviousPosition(const QPointF previousPosition);// устанавливает предыдущую позицию

    void setDotFlags(unsigned int flags);// устанавливает флаги

signals:
    void previousPositionChanged();// сигнал при изменении позиции
    void signalMouseRelease();// сигнал при отпускании кнопки мыши
    void signalMove(QGraphicsItem *signalOwner, qreal dx, qreal dy);// сигнал при перемещении

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;// действия при перемещении
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;// действия при нажатии
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;// действия при отпускании
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event ) override;// дейсвтия при наведении курсора
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;// действия при выходе курсора из рабочей области

private:
    unsigned int m_flags;
    QPointF m_previousPosition;
};

#endif // DOTSIGNAL_H
