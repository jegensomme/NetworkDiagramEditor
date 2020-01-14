#include "library.h"
#include "ui_library.h"
#include "QMessageBox"

Library::Library(QVector <Equipment*> &equipments_in_library,
                 QVector<Equipment*> &equipments_in_project,
                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Library),
    equipments_in_project(equipments_in_project),
    equipments_in_library(equipments_in_library)
{
    ui->setupUi(this);
    ui->pushAdd->setEnabled(false);
    ui->pushDelete->setEnabled(false);
    library_hasFocus = false;
    project_hasFocus = false;

    foreach(Equipment* equipment, equipments_in_library)
    {
        Equipment *copy = Equipment::create_copy(equipment);
        copy->setText(equipment->get_name());
        ui->ListWidgetsLibrary->addItem(copy);
    }
    foreach(Equipment* equipment, equipments_in_project)
    {
        Equipment *copy = Equipment::create_copy(equipment);
        copy->setText(equipment->get_name());
        ui->ListWidgetsProject->addItem(copy);
    }
}

Library::~Library()
{
    delete ui;
}

void Library::on_pushAdd_clicked()
{
    if(library_hasFocus)
    {
        int row = ui->ListWidgetsLibrary->currentRow();
        if(!Equipment::contains(equipments_in_project, equipments_in_library[row]->get_name()))
        {
            QListWidgetItem *item = new QListWidgetItem();
            *item = *ui->ListWidgetsLibrary->currentItem();
            ui->ListWidgetsProject->addItem(item);
            Equipment *copy = Equipment::create_copy(equipments_in_library[row]);
            copy->setText(equipments_in_library[row]->get_name());
            equipments_in_project.push_back(copy);
            ui->pushDelete->setEnabled(true);
        }
        else {
            QMessageBox::information(this, "Внимание!", "Оборудование уже в проекте");
        }
    }
    else if(project_hasFocus)
    {
        int row = ui->ListWidgetsProject->currentRow();
        if(!Equipment::contains(equipments_in_library, equipments_in_project[row]->get_name()))
        {
            QListWidgetItem *item = new QListWidgetItem();
            *item = *ui->ListWidgetsProject->currentItem();
            ui->ListWidgetsLibrary->addItem(item);
            Equipment *copy = Equipment::create_copy(equipments_in_project[row]);
            copy->setText(equipments_in_project[row]->get_name());
            equipments_in_library.push_back(copy);
            ui->pushDelete->setEnabled(true);
        }
        else {
            QMessageBox::information(this, "Внимание!", "Оборудование уже в библиотеке");
        }
    }
}

void Library::on_pushDelete_clicked()
{
    if(project_hasFocus)
    {
        int row = ui->ListWidgetsProject->currentRow();
        QListWidgetItem *item = ui->ListWidgetsProject->takeItem(ui->ListWidgetsProject->currentRow());
        delete item;
        delete equipments_in_project[row];
        equipments_in_project.remove(row);
        if(ui->ListWidgetsProject->count() == 0)
        {
            ui->pushDelete->setEnabled(false);
            ui->pushAdd->setEnabled(false);
            project_hasFocus = false;
        }
    }
    else if(library_hasFocus)
    {
        int row = ui->ListWidgetsLibrary->currentRow();
        QListWidgetItem *item = ui->ListWidgetsLibrary->takeItem(ui->ListWidgetsLibrary->currentRow());
        delete item;
        delete equipments_in_library[row];
        equipments_in_library.remove(row);
        if(ui->ListWidgetsLibrary->count() == 0)
        {
            ui->pushDelete->setEnabled(false);
            ui->pushAdd->setEnabled(false);
            project_hasFocus = false;
        }
    }
}

void Library::on_ListWidgetsLibrary_itemClicked()
{
    library_hasFocus = true;
    project_hasFocus = false;
    ui->pushAdd->setEnabled(true);
    ui->pushDelete->setEnabled(true);
}

void Library::on_ListWidgetsLibrary_itemDoubleClicked()
{
    Library::on_pushAdd_clicked();
}

void Library::on_ListWidgetsProject_itemClicked()
{
    library_hasFocus = false;
    project_hasFocus = true;
    ui->pushAdd->setEnabled(true);
    ui->pushDelete->setEnabled(true);
}

void Library::on_ListWidgetsProject_itemDoubleClicked()
{
    Library::on_pushAdd_clicked();
}

void Library::on_pushOk_clicked()
{
    Library::close();
}
