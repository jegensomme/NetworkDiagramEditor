#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "connectorcreator.h"
#include "library.h"
#include "projectname.h"
#include "selectpath.h"
#include "projectname.h"
#include "addrule.h"
#include <QGraphicsScene>
#include "QMessageBox"
#include "connector.h"
#include "vepolyline.h"
#include "dotsignal.h"
#include "body.h"
#include "instruction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->open_equipmentCreator->setEnabled(false);
    ui->open_library->setEnabled(false);
    ui->open_connectorCreator->setEnabled(false);
    ui->button_add_equipment->setEnabled(false);
    ui->button_delete_object->setEnabled(false);
    ui->button_add_connection->setEnabled(false);
    ui->button_change_description->setEnabled(false);
    ui->add_rule->setEnabled(false);
    ui->save_project->setEnabled(false);
    ui->save_as_project->setEnabled(false);
    ui->descriprion->setEnabled(false);

    scene = new QGraphicsScene();    
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(check_sceneFocus()));
    ui->graphicsView->setScene(scene);

    mainPath = FileManager::currentPath();
    libraryPath = mainPath + "/library";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_project_triggered()
{
    ui->statusBar->showMessage("Создать проект");
    ProjectName windowProjectName;
    windowProjectName.setModal(true);
    windowProjectName.exec();
    if(!windowProjectName.get_projectName().isEmpty())
    {
        projectName = windowProjectName.get_projectName();

        SelectPath windowSelectPath;
        windowSelectPath.setModal(true);
        windowSelectPath.exec();
        if(!windowSelectPath.get_projectPath().isEmpty())
        {
            projectPath = windowSelectPath.get_projectPath();

            nextEquipmentId = 1;
            nextConnectionId = 1;

            ui->open_equipmentCreator->setEnabled(false);
            ui->open_library->setEnabled(false);
            ui->open_connectorCreator->setEnabled(false);
            ui->button_add_equipment->setEnabled(false);
            ui->button_delete_object->setEnabled(false);
            ui->button_add_connection->setEnabled(false);
            ui->button_change_description->setEnabled(false);
            ui->descriprion->setEnabled(false);
            ui->add_rule->setEnabled(false);
            ui->save_project->setEnabled(false);
            ui->save_as_project->setEnabled(false);

            ui->widget_equipments->clear();
            scene->clear();
            ui->descriprion->clear();

            delete fileManager;
            connectionRule = new ConnectionRule;
            fileManager = new FileManager(projectPath,
                                          mainPath,
                                          libraryPath,
                                          projectName,
                                          equipments_in_project,
                                          connectors_in_project,
                                          equipments_in_library,
                                          equipments_in_scheme,
                                          connections,
                                          connectionRule);

            switch(fileManager->create_project())
            {
            case 0:
            {
                QMessageBox::information(this, "Успех", "Проект успешно создан:)");

                ui->save_project->setEnabled(true);
                ui->save_as_project->setEnabled(true);
                ui->open_library->setEnabled(true);
                ui->open_connectorCreator->setEnabled(true);
                ui->open_equipmentCreator->setEnabled(true);
                ui->button_change_description->setEnabled(false);
                ui->descriprion->setEnabled(false);
                ui->add_rule->setEnabled(true);

                break;
            }
            case 1:
            {
                QMessageBox::warning(this, "Упс:(", "Проект с таким именем уже существует");
                break;
            }
            case 2:
            {
                QMessageBox::warning(this, "Упс:(", "Библиотека не загружена");
                break;
            }
            case 3:
            {
                QMessageBox::warning(this, "Упс:(", "Проект не удалось создать");
                break;
            }
            }
        }
    } 
    ui->statusBar->clearMessage();
}

void MainWindow::on_open_project_triggered()
{
    ui->statusBar->showMessage("Открыть проект");
    SelectPath windowSelectPath;
    windowSelectPath.setModal(true);
    windowSelectPath.exec();
    if(!windowSelectPath.get_projectPath().isEmpty())
    {
        projectPath = windowSelectPath.get_projectPath();

        nextEquipmentId = 1;
        nextConnectionId = 1;

        ui->open_equipmentCreator->setEnabled(false);
        ui->open_library->setEnabled(false);
        ui->open_connectorCreator->setEnabled(false);
        ui->button_add_equipment->setEnabled(false);
        ui->button_delete_object->setEnabled(false);
        ui->button_add_connection->setEnabled(false);
        ui->button_change_description->setEnabled(false);
        ui->descriprion->setEnabled(false);
        ui->add_rule->setEnabled(false);
        ui->save_project->setEnabled(false);
        ui->save_as_project->setEnabled(false);

        ui->widget_equipments->clear();
        scene->clear();
        ui->descriprion->clear();

        delete fileManager;
        connectionRule = new ConnectionRule;
        fileManager = new FileManager(projectPath,
                                      mainPath,
                                      libraryPath,
                                      projectName,
                                      equipments_in_project,
                                      connectors_in_project,
                                      equipments_in_library,
                                      equipments_in_scheme,
                                      connections,
                                      connectionRule);
        switch(fileManager->open_project())
        {
        case 0:
        {
            QMessageBox::information(this, "Ура:)", "Проект успешно открыт");

            ui->save_project->setEnabled(true);
            ui->save_as_project->setEnabled(true);
            ui->open_library->setEnabled(true);
            ui->open_connectorCreator->setEnabled(true);
            ui->open_equipmentCreator->setEnabled(true);
            ui->add_rule->setEnabled(true);
            ui->button_change_description->setEnabled(false);
            ui->descriprion->setEnabled(false);

            foreach(Equipment *equipment, equipments_in_project)
            {
                Equipment *copy = Equipment::create_copy(equipment);
                copy->setText(equipment->get_name());
                ui->widget_equipments->addItem(copy);
            }

            if(!equipments_in_scheme.isEmpty())
            {
                foreach(Equipment *equipment, equipments_in_scheme)
                {
                    add_equipment_on_scene(equipment);
                }
                nextEquipmentId = equipments_in_scheme.last()->get_equipmentId() + 1;
            }
            if(!connections.isEmpty())
            {
                nextConnectionId = connections.last()->get_connectionId() + 1;
                foreach(VEPolyline *connection, connections)
                {
                    scene->addItem(connection);
                }
            }

            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Упс:(", "Проект не найден");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Упс:(", "Оборудование не удалось загрузить");
            break;
        }
        case 3:
        {
            QMessageBox::warning(this, "Упс:(", "Библиотеку не удалось загрузить");
            break;
        }
        case 4:
        {
            QMessageBox::warning(this, "Упс:(", "Схему не удалось загрузить");
            break;
        }
        default:
        {
            QMessageBox::warning(this, "Упс:(", "Неизвестная ошибка:(");
            break;
        }
        }
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_save_project_triggered()
{
    ui->statusBar->showMessage("Сохранить");
    if(fileManager->save_project())
        QMessageBox::information(this, "Сохранение", "Проект успешно сохранен");
    else
        QMessageBox::warning(this, "Сохранение", "Проект не удалось сохранить");

    ui->statusBar->clearMessage();
}

void MainWindow::on_save_as_project_triggered()
{
    ui->statusBar->showMessage("Сохранить как");
    SelectPath window;
    window.setModal(true);
    window.exec();
    if(!window.get_projectPath().isEmpty())
    {
        switch(fileManager->save_as_project(window.get_projectPath()))
        {
        case 0:
        {
            QMessageBox::information(this, "Сохранение", "Проект успешно сохранен");
            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Сохранение", "Вы указали текущую директорию");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Сохранение", "Проект с таким именем уже существует");
            break;
        }
        case 3:
        {
            QMessageBox::warning(this, "Сохранение", "Проект не удалось сохранить");
            break;
        }
        }
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_close_project_triggered()
{
    QApplication::quit();
}

void MainWindow::on_open_equipmentCreator_triggered()
{
    ui->statusBar->showMessage("Создать оборудование");
    EquipmentCreator window(connectors_in_project);
    window.setModal(true);
    window.exec();
    if(window.CreateEquipment() != nullptr)
    {
        int counter = 0;
        QString name = window.CreateEquipment()->get_name();
        while(Equipment::contains(equipments_in_project, window.CreateEquipment()->get_name()) || Equipment::contains(equipments_in_library, window.CreateEquipment()->get_name()))
            window.CreateEquipment()->set_name(name + QString::number(++counter));

        equipments_in_project.push_back(window.CreateEquipment());
        Equipment *copy = Equipment::create_copy(equipments_in_project.last());
        copy->setText(equipments_in_project.last()->get_name());
        ui->widget_equipments->addItem(copy);
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_open_library_triggered()
{
    ui->statusBar->showMessage("Открыть библиотеку");
    Library window(equipments_in_library, equipments_in_project);
    window.setModal(true);
    window.exec();
    ui->widget_equipments->clear();

    foreach(Equipment *equipment, equipments_in_project)
    {
        Equipment *copy = Equipment::create_copy(equipment);
        copy->setText(equipment->get_name());
        ui->widget_equipments->addItem(copy);
    }

    if(ui->widget_equipments->count() == 0)
        ui->button_add_equipment->setEnabled(false);

    ui->statusBar->clearMessage();
}

void MainWindow::on_add_rule_triggered()
{
    ui->statusBar->showMessage("Добавить соединение");
    AddRule window(connectors_in_project);
    window.setModal(true);
    window.exec();
    if(!window.isReject())
        connectionRule->set_rule(window.get_color1(), window.get_color2(), window.get_rule());
    ui->statusBar->clearMessage();
}

void MainWindow::on_open_connectorCreator_triggered()
{
    ui->statusBar->showMessage("Создать коннектор");
    ConnectorCreator window(connectors_in_project);
    window.setModal(true);
    window.exec();

    if(window.get_connector() != nullptr)
    {
        int counter = 0;
        QString name = window.get_connector()->get_name();
        foreach(Connector *connector, connectors_in_project)
        {
            if(connector->get_name() == window.get_connector()->get_name())
                window.get_connector()->set_name(name + QString::number(++counter));
        }
        connectors_in_project.push_back(window.get_connector());
    }
    ui->statusBar->clearMessage();
}

void MainWindow::on_instruction_triggered()
{
    ui->statusBar->showMessage("Инструкция");
    Instruction window;
    window.setModal(true);
    window.exec();
    ui->statusBar->clearMessage();
}

void MainWindow::on_widget_equipments_clicked()
{
    ui->button_add_equipment->setEnabled(true);
}

void MainWindow::on_widget_equipments_itemDoubleClicked()
{
    MainWindow::on_button_add_equipment_clicked();
}

void MainWindow::on_button_add_equipment_clicked()
{    
    int row = ui->widget_equipments->currentRow();
    Equipment *copy = Equipment::create_copy(equipments_in_project[row]);
    copy->set_id(nextEquipmentId++);
    QString text;
    foreach(Connector *connector, copy->get_render()->get_connectors())
    {
        connector->set_description(connector->get_name());
        text = text + "тип: " + connector->get_description() + ", id: " + QString::number(connector->get_connectorId()) + '\n';
    }
    text = "Название: " + copy->get_name() + '\n' +
            "ID: " + QString::number(copy->get_equipmentId()) + '\n' +
            "Коннекторы:\n" + text;
    copy->set_description(text);
    equipments_in_scheme.push_back(copy);
    add_equipment_on_scene(copy);
}

void MainWindow::add_equipment_on_scene(Equipment *equipment)
{
    QString text = QString(equipment->get_name());
    QLabel *label = new QLabel(text);
    equipment->get_render()->get_body()->set_id(equipment->get_equipmentId());
    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(equipment->get_render()->get_body());
    proxyWidget->setWidget(label);
    QVector <Connector*> connectors = equipment->get_render()->get_connectors();
    scene->addItem(equipment->get_render()->get_body());
}

void MainWindow::on_button_add_connection_clicked()
{
        Connector *first = qgraphicsitem_cast<Connector*>(scene->selectedItems().first());
        Connector *end = qgraphicsitem_cast<Connector*>(scene->selectedItems().last());
        if (first->get_equipmentId() != end->get_equipmentId())
        {
            if (first->get_link() == nullptr && end->get_link() == nullptr)
            {
                if (connectionRule->get_rule(first->get_color(), end->get_color()))
                {
                    Equipment *firstEq = nullptr;
                    Equipment *endEq = nullptr;
                    first->set_link(end);
                    end->set_link(first);
                    foreach(Equipment *equipment, equipments_in_scheme)
                    {
                        if(equipment->get_equipmentId() == first->get_equipmentId())
                        {
                            firstEq = equipment;
                        }
                        else if(equipment->get_equipmentId() == end->get_equipmentId())
                        {
                            endEq = equipment;
                        }

                    }

                    add_connection_on_scene(firstEq, endEq, first, end);
                }
                else
                {
                    QMessageBox::warning(this, "Внимание", "Данное соединение запрещено");
                }
            }
            else
            {
                QMessageBox::warning(this, "Внимание", "Один из коннекторов уже соединен");
            }
        }
        else
        {
            QMessageBox::warning(this, "Внимание", "Данное соединение запрещено");
        }
}

void MainWindow::add_connection_on_scene(Equipment *firstEquipment, Equipment *endEquipment, Connector *first, Connector *end)
{
    VEPolyline *polyline = new VEPolyline(firstEquipment->get_render()->get_body(), endEquipment->get_render()->get_body());
    QPainterPath path;
    polyline->set_connectorIdFirst(first->get_connectorId());
    polyline->set_connectorIdEnd(end->get_connectorId());
    polyline->set_connectionId(nextConnectionId++);

    QPointF fixPos;
    fixPos.setX(10);
    fixPos.setY(10);
    path.moveTo(firstEquipment->get_render()->get_body()->pos() + first->pos() + fixPos);
    path.lineTo(endEquipment->get_render()->get_body()->pos() + end->pos() + fixPos);
    polyline->setPath(path);
    QPen pen;
    pen.setWidth(2);
    polyline->setPen(pen);
    polyline->setZValue(-1);

    QString text;
    text = "ID: " + QString::number(polyline->get_connectionId()) + '\n' +
            "Начало: "  + '\n' +
            "Название: " + equipments_in_scheme[polyline->get_first()->get_id() - 1]->get_name() + '\n' +
            "ID оборудования: " + QString::number(polyline->get_first()->get_id()) + '\n' +
            "Тип коннектора: " + equipments_in_scheme[polyline->get_first()->get_id() - 1]->get_render()->get_connectors()[polyline->get_connectorIdFirst() - 1]->get_name() + '\n' +
            "ID коннектора: " + QString::number(polyline->get_connectorIdFirst()) + '\n' +
            "Конец: "  + '\n' +
            "Название: " + equipments_in_scheme[polyline->get_end()->get_id() - 1]->get_name() + '\n' +
            "ID оборудования: " + QString::number(polyline->get_end()->get_id()) + '\n' +
            "Тип коннектора: " + equipments_in_scheme[polyline->get_end()->get_id() - 1]->get_render()->get_connectors()[polyline->get_connectorIdEnd() - 1]->get_name() + '\n' +
            "ID коннектора: " + QString::number(polyline->get_connectorIdEnd());
    polyline->set_description(text);

    scene->addItem(polyline);
    connections.push_back(polyline);
}

void MainWindow::on_button_delete_object_clicked()
{
    if(scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == Body::Type)
    {
        int n = connections.size();
        int j = 0;
        for(int i = 0; i < n; i++)
        {
            int firstId = connections[i - j]->get_first()->get_id();
            int endId = connections[i - j]->get_end()->get_id();
            if(firstId == selectedEquipmentId || endId == selectedEquipmentId)
            {
                QVector <Connector*> connectors_first = equipments_in_scheme[firstId - 1]->get_render()->get_connectors();
                QVector <Connector*> connectors_end = equipments_in_scheme[endId - 1]->get_render()->get_connectors();
                connectors_first[connections[i - j]->get_connectorIdFirst() - 1]->set_link(nullptr);
                connectors_end[connections[i - j]->get_connectorIdEnd() - 1]->set_link(nullptr);
                scene->removeItem(connections[i - j]);
                connections.remove(i - j);
                j++;
            }
        }
        nextConnectionId = 1;
        foreach(VEPolyline *connection, connections)
        {
            connection->set_connectionId(nextConnectionId++);
        }
        scene->removeItem(scene->selectedItems().first());
        equipments_in_scheme.remove(selectedEquipmentId - 1);
        nextEquipmentId = 1;
        foreach(Equipment *equipment, equipments_in_scheme)
        {
            equipment->set_id(nextEquipmentId);
            equipment->get_render()->get_body()->set_id(nextEquipmentId++);
        }
    }
    else if(scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == VEPolyline::Type)
    {
        int firstId = connections[selectedConnectionId - 1]->get_first()->get_id();
        int endId = connections[selectedConnectionId - 1]->get_end()->get_id();

        QVector <Connector*> connectors_first = equipments_in_scheme[firstId - 1]->get_render()->get_connectors();
        QVector <Connector*> connectors_end = equipments_in_scheme[endId - 1]->get_render()->get_connectors();
        connectors_first[connections[selectedConnectionId - 1]->get_connectorIdFirst() - 1]->set_link(nullptr);
        connectors_end[connections[selectedConnectionId - 1]->get_connectorIdEnd() - 1]->set_link(nullptr);
        scene->removeItem(scene->selectedItems().first());
        connections.remove(selectedConnectionId - 1);
        nextConnectionId = 1;
        foreach(VEPolyline *connection, connections)
        {
            connection->set_connectionId(nextConnectionId++);
        }
    }
}

void MainWindow::check_sceneFocus()
{
    if (scene->selectedItems().size() == 2 &&
            scene->selectedItems().first()->type() == Connector::Type &&
            scene->selectedItems().last()->type() == Connector::Type)
    {
        ui->button_add_connection->setEnabled(true);
        ui->button_delete_object->setEnabled(false);
        ui->descriprion->clear();
        ui->button_change_description->setEnabled(false);
        ui->descriprion->setEnabled(false);
    }

    else if(scene->selectedItems().size() == 1 &&
            scene->selectedItems().first()->type() == VEPolyline::Type)
    {
        ui->button_delete_object->setEnabled(true);
        ui->descriprion->clear();
        int connectionId = qgraphicsitem_cast<VEPolyline*>(scene->selectedItems().first())->get_connectionId();
        selectedConnectionId = connectionId;
        ui->descriprion->setText(connections[connectionId - 1]->get_description());
        ui->descriprion->setEnabled(true);
        ui->button_change_description->setEnabled(false);
    }
    else if(scene->selectedItems().size() == 1 &&
            scene->selectedItems().first()->type() == Body::Type)
    {
        ui->descriprion->clear();
        ui->button_delete_object->setEnabled(true);
        int equipmentId = qgraphicsitem_cast<Body*>(scene->selectedItems().first())->get_id();
        selectedEquipmentId = equipmentId;
        ui->descriprion->setText(equipments_in_scheme[equipmentId - 1]->get_description());
        ui->descriprion->setEnabled(true);
        ui->button_change_description->setEnabled(false);
    }
    else if(scene->selectedItems().size() == 1 &&
            scene->selectedItems().first()->type() == Connector::Type)
    {
        ui->descriprion->clear();
        ui->button_delete_object->setEnabled(false);
        ui->descriprion->setText(qgraphicsitem_cast<Connector*>(scene->selectedItems().first())->get_description());
        ui->descriprion->setEnabled(true);
        ui->button_change_description->setEnabled(false);
    }
    else
    {
        ui->button_add_connection->setEnabled(false);
        ui->button_delete_object->setEnabled(false);
        ui->button_change_description->setEnabled(false);
        ui->descriprion->setEnabled(false);
        ui->descriprion->clear();
    }
}

void MainWindow::on_descriprion_textChanged()
{
    if((scene->selectedItems().size() == 1 &&
            scene->selectedItems().first()->type() == Body::Type) ||
       (scene->selectedItems().size() == 1 &&
           scene->selectedItems().first()->type() == VEPolyline::Type) ||
       (scene->selectedItems().size() == 1 &&
           scene->selectedItems().first()->type() == Connector::Type))
        ui->button_change_description->setEnabled(true);
}

void MainWindow::on_button_change_description_clicked()
{
    if(scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == Body::Type)
    {
        int id = qgraphicsitem_cast<Body*>(scene->selectedItems().first())->get_id();
        equipments_in_scheme[id - 1]->set_description(ui->descriprion->toPlainText());
    }
    else if(scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == VEPolyline::Type)
    {
        qgraphicsitem_cast<VEPolyline*>(scene->selectedItems().first())->set_description(ui->descriprion->toPlainText());
    }
    else if(scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == Connector::Type)
    {
        qgraphicsitem_cast<Connector*>(scene->selectedItems().first())->set_description(ui->descriprion->toPlainText());
    }
    ui->button_change_description->setEnabled(false);
}
