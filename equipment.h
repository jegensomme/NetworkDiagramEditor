#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include<QVector>
#include<QString>
#include<equipmentrender.h>
#include <QListWidgetItem>
#include <QLabel>
#include <QGraphicsProxyWidget>

/**
 * Класс описывает оборудование
 */

class Equipment : public QListWidgetItem
{
public:
    /*инициализация стандартными значениями переменных и
      создание нового экземляра EguipmentRender, в котором содержится тело и коннекторы.*/
    Equipment(QVector <Connector*> connectors);
    ~Equipment();

public:
    void set_id(const int &nextEquipmentId);// устанавливает id оборудования
    int get_equipmentId() const;// возвращает id оборудования
    void set_name(const QString &name);// устанавливает название оборудования
    QString get_name() const;// возвращает название оборудования
    void set_description(QString text);// устанавливает описание оборудования
    QString get_description();// возвращает описание оборудования
    EquipmentRender* get_render() const;// возвращает "render"

    static Equipment* create_copy(Equipment *equipment);// создает копию оборудования
    // вспомогательная функция, которыя проверяет наличие элемента в векторе
    static bool contains(const QVector <Equipment*> &equipments, const QString &name);

private:
    QString name;
    QString description;
    int equipmentId;
    EquipmentRender *render;// экземляр EguipmentRender, в котором содержится тело и коннекторы
};

#endif // EQUIPMENT_H
