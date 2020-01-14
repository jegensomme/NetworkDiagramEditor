#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipment.h"
#include "filemanager.h"
#include "connectionrule.h"
#include "vepolyline.h"

namespace Ui {
class MainWindow;
}

/**
 * Основное окно проекта
 * При создании класса происходит иницализация объектов в MainWindow
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create_project_triggered();// создание прокта

    void on_open_project_triggered();// открытие проекта

    void on_save_project_triggered();// сохранение проекта

    void on_save_as_project_triggered();// сохранение проекта в соответсвии с выбранным путем

    void on_close_project_triggered();// закрыть приложение

    void on_open_equipmentCreator_triggered();// открыть редактор оборудования

    void on_open_library_triggered();// открыть библиотеку

    void on_add_rule_triggered();// добавить правило соединений

    void on_widget_equipments_clicked();// реакция на нажатие на объект из виджета widget_equipments

    void on_button_add_equipment_clicked();// добавить оборудование на схему

    void on_widget_equipments_itemDoubleClicked();// реакция на двойной клик по объекту из виджета widget_equipments

    void on_button_delete_object_clicked();// удалить объект из схемы

    void on_button_add_connection_clicked();// добавить соединение между коннекторами

    void check_sceneFocus();// действия в соответсвии с выделенным объектом

    void on_descriprion_textChanged();// реакция на изменение описания объекта

    void on_button_change_description_clicked();// изменить описание объекта

    void on_open_connectorCreator_triggered();// открыть редактор коннекторов

    void on_instruction_triggered();

private:
    void add_equipment_on_scene(Equipment *equipment);// добавление оборудования на сцену
    // добавить соединяющую линию на сцену
    void add_connection_on_scene(Equipment *firstEquipment, Equipment *endEquipment, Connector *first, Connector *end);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;// сцена
    QVector <Equipment*> equipments_in_project;// оборудование в проекте
    QVector <Equipment*> equipments_in_library;// оборудование в библиотеке
    QVector <Equipment*> equipments_in_scheme;// оборудование на схеме
    QVector <VEPolyline*> connections;// соединения
    QVector <Connector*> connectors_in_project;// коннекоры в прокте
    ConnectionRule *connectionRule = nullptr;// правила соединений
    FileManager *fileManager = nullptr;
    QString mainPath = nullptr;// путь из которого запускается приложение
    QString libraryPath = nullptr;// путь к библиотеке
    QString projectPath = nullptr;// путь к проекту
    QString projectName = nullptr;// название проекта
    int nextEquipmentId = 1;// определяет id нового оборудования
    int nextConnectionId = 1;// определяет id нового соединения
    int selectedEquipmentId = 0;// id выделенного оборудования
    int selectedConnectionId = 0;// id выделенного соединения
};

#endif // MAINWINDOW_H
