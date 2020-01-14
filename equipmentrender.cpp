#include "equipmentrender.h"

EquipmentRender::EquipmentRender(QVector <Connector*> connectors)
    : connectors(connectors)
{
    body = new Body(connectors.size() % 2 == 0 ? connectors.size() / 2 : connectors.size() / 2 + 1);
    for(int i = 0, j = 0; i < connectors.size() - 1; i += 2, ++j)
    {
        connectors[i]->setParentItem(body);
        connectors[i]->setPos(60, 20 + j * 40);
        connectors[i+1]->setParentItem(body);
        connectors[i+1]->setPos(0, 20 + j * 40);
    }
    if(connectors.size() % 2 == 1)
    {
        connectors.last()->setParentItem(body);
        connectors.last()->setPos(60, 20 + (connectors.size() / 2) * 40);
    }
}

EquipmentRender::~EquipmentRender()
{
    foreach(Connector *connector, connectors)
        delete connector;

    delete body;
}

Body* EquipmentRender::get_body()
{
    return body;
}
QVector <Connector*> EquipmentRender::get_connectors()
{
    return connectors;
}
