#include "body.h"

Body::Body(int size)
    : size(size), height((2 * size + 1) * 20)
{
    setFlag(ItemIsSelectable);
}

int Body::type() const
{
    return Type;
}

void Body::set_id(int id)
{
    this->id = id;
}

int Body::get_id()
{
    return id;
}

QRectF Body::boundingRect() const
{
    return QRectF (0,0,80,height);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(QGraphicsItem::isSelected() ? 4 : 2);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRect(0,0,80,height);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Body::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
    auto dx = event->pos().x() - m_previousPosition.x();
    auto dy = event->pos().y() - m_previousPosition.y();
    emit signalMove(this, dx, dy);
}

void Body::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_shiftMouseCoords = this->pos() - mapToScene(event->pos());
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    m_previousPosition = event->pos();
    qDebug() << "234";
    Q_UNUSED(event);
    QGraphicsItem::mousePressEvent(event);
}

void Body::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
