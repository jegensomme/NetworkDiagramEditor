#ifndef EQUIPMENTRENDER_H
#define EQUIPMENTRENDER_H

#include<QVector>
#include<body.h>
#include<connector.h>

/**
 * Класс содержит тело и коннекторы оборудования
 */

class EquipmentRender
{
public:
    EquipmentRender(QVector <Connector*> connectors);// инициализация тела и коннекторов
    ~EquipmentRender();

    Body* get_body();// возвращает тело
    QVector <Connector*> get_connectors();// возвращает коннекторы

private:
    Body *body;// тело
    QVector <Connector*> connectors;// коннекторы
};

#endif // EQUIPMENTRENDER_H
