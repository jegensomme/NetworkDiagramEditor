#ifndef EQUIPMENTCREATOR_H
#define EQUIPMENTCREATOR_H

#include <QDialog>
#include <equipment.h>

namespace Ui {
class EquipmentCreator;
}

/**
 * Класс описывает создание оборудования
 */

class EquipmentCreator : public QDialog
{
    Q_OBJECT

public:
    //добавляет в виджет созданные коннекторы
    explicit EquipmentCreator(const QVector<Connector*> &connectors_in_project, QWidget *parent = nullptr);
    ~EquipmentCreator();
    Equipment* CreateEquipment();// возвращает созданное оборудование

private slots:
    void on_pushButtonCreate_clicked();// действия при нажатии "создать"

    void on_pushButtonAdd_clicked();// добавление коннектора в оборудование

    void on_pushButtonDel_clicked();// удаление коннектора из оборудования

    void on_listWidgetConnectors_itemClicked();// действия при нажатии на объект виджета 1

    void on_listWidgetEquipment_itemClicked();// действия при нажатии на объект виджета 2

    void on_listWidgetConnectors_itemDoubleClicked();// действия при двойном клике на объект виджета 1

    void on_listWidgetEquipment_itemDoubleClicked();// действия при двойном клике на объект виджета 2

    void on_pushButtonExit_clicked();// выход из редактора

    void on_lineEditName_textChanged();// действия при изменении текста в названии оборудрвания

    void enable_pushButtonCreate();// действия при нажатии на "создать"
private:
    Ui::EquipmentCreator *ui;
    bool listWidgetEquipment_isEmpty = true;// добавлен ли хоть один коннектор
    Equipment *equipment = nullptr;
    const QVector<Connector*> &connectors_in_project;
};

#endif // EQUIPMENTCREATOR_H
