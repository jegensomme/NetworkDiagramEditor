#include "equipment.h"

Equipment::Equipment(QVector <Connector*> connector)
    : equipmentId(0)
{
    render = new EquipmentRender(connector);
}

Equipment::~Equipment()
{
    delete render;
}

void Equipment::set_id(const int &nextEquipmentId)
{
    int nextConnectorId = 1;
    equipmentId = nextEquipmentId;
    render->get_body()->set_id(equipmentId);
    int connectorSize = render->get_connectors().size();
    QVector<Connector*> connectors = render->get_connectors();
    for(int i = 0; i < connectorSize; ++i)
    {
        connectors[i]->set_equipmentId(equipmentId);
        connectors[i]->set_connectorId(nextConnectorId++);
    }
}

int Equipment::get_equipmentId() const
{
    return equipmentId;
}

void Equipment::set_name(const QString &name)
{
    this->name = name;
}

QString Equipment::get_name() const
{
    return name;
}

void Equipment::set_description(QString text)
{
    description = text;
}

QString Equipment::get_description()
{
    return description;
}

EquipmentRender* Equipment::get_render() const
{
    return render;
}

Equipment* Equipment::create_copy(Equipment *equipment)
{
    QVector <Connector*> connectors;
    QString name = equipment->name;
    int connectorSize = equipment->render->get_connectors().size();
    for(int i = 0; i < connectorSize; ++i)
    {
        Qt::GlobalColor color = equipment->render->get_connectors()[i]->get_color();
        connectors.push_back(Connector::set_color(color));
    }
    Equipment *copy = new Equipment(connectors);
    copy->name = equipment->name;
    copy->equipmentId = equipment->equipmentId;

    for(int i = 0; i < connectorSize; ++i)
    {
        connectors[i]->set_connectorId(equipment->render->get_connectors()[i]->get_connectorId());
        connectors[i]->set_equipmentId(copy->equipmentId);
        connectors[i]->set_name(equipment->render->get_connectors()[i]->get_name());
    }

    return copy;
}

bool Equipment::contains(const QVector <Equipment*> &equipments, const QString &name)
{
    foreach(Equipment *equipment, equipments)
    {
        if(equipment->name == name)
            return true;
    }

    return false;
}
