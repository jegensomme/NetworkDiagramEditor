#include "equipmentcreator.h"
#include "ui_equipmentcreator.h"
#include <QMessageBox>
#include <QRegExpValidator>

EquipmentCreator::EquipmentCreator(const QVector<Connector*> &connectors_in_project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentCreator),
    connectors_in_project(connectors_in_project)
{
    ui->setupUi(this);

    foreach(Connector *connector, this->connectors_in_project)
    {
        switch(connector->get_color())
        {
        case Qt::red:
        {
            if(Connector::contains(connectors_in_project, Qt::red))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/red.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkRed:
        {
            if(Connector::contains(connectors_in_project, Qt::darkRed))
            {
               ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkred.png"), connector->get_name()));
            }
            break;
        }
        case Qt::blue:
        {
            if(Connector::contains(connectors_in_project, Qt::blue))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/blue.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkBlue:
        {
            if(Connector::contains(connectors_in_project, Qt::darkBlue))
            {
               ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkblue.png"), connector->get_name()));
            }
            break;
        }
        case Qt::cyan:
        {
            if(Connector::contains(connectors_in_project, Qt::cyan))
            {

               ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/cyan.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkCyan:
        {
            if(Connector::contains(connectors_in_project, Qt::darkCyan))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkcyan.png"), connector->get_name()));
            }
            break;
        }
        case Qt::green:
        {
            if(Connector::contains(connectors_in_project, Qt::green))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/green.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkGreen:
        {
            if(Connector::contains(connectors_in_project, Qt::darkGreen))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkgreen.png"), connector->get_name()));
            }
            break;
        }
        case Qt::yellow:
        {
            if(Connector::contains(connectors_in_project, Qt::yellow))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/yellow.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkYellow:
        {
            if(Connector::contains(connectors_in_project, Qt::darkYellow))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkyellow.png"), connector->get_name()));
            }
            break;
        }
        case Qt::gray:
        {
            if(Connector::contains(connectors_in_project, Qt::gray))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/gray.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkGray:
        {
            if(Connector::contains(connectors_in_project, Qt::darkGray))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkgray.png"), connector->get_name()));
            }
            break;
        }
        case Qt::magenta:
        {
            if(Connector::contains(connectors_in_project, Qt::magenta))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/magenta.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkMagenta:
        {
            if(Connector::contains(connectors_in_project, Qt::darkMagenta))
            {
                ui->listWidgetConnectors->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkmagenta.png"), connector->get_name()));
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }

    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonDel->setEnabled(false);
    ui->pushButtonCreate->setEnabled(false);
}

EquipmentCreator::~EquipmentCreator()
{
    delete ui;
}

Equipment* EquipmentCreator::CreateEquipment()
{
    return equipment;
}

void EquipmentCreator::on_pushButtonCreate_clicked()
{
    QVector <Connector*> connectors;

    while (QListWidgetItem *item = ui->listWidgetEquipment->takeItem(0))
    {
        foreach(Connector *connector, connectors_in_project)
        {
            if(item->text() == connector->get_name())
            {
                connectors.push_back(Connector::set_color(connector->get_color()));
                connectors.last()->set_name(item->text());
            }
        }
    }
    QString name = ui->lineEditName->text();
    equipment = new Equipment(connectors);
    equipment->set_name(name);

    EquipmentCreator::close();
}

void EquipmentCreator::on_pushButtonAdd_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    *item = *ui->listWidgetConnectors->currentItem();
    ui->listWidgetEquipment->addItem(item);
    listWidgetEquipment_isEmpty = false;
    enable_pushButtonCreate();
}

void EquipmentCreator::on_pushButtonDel_clicked()
{
    QListWidgetItem *item = ui->listWidgetEquipment->takeItem(ui->listWidgetEquipment->currentRow());
    delete item;
    if(ui->listWidgetEquipment->count() == 0)
    {
        ui->pushButtonDel->setEnabled(false);
        listWidgetEquipment_isEmpty = true;
        enable_pushButtonCreate();
    }
}

void EquipmentCreator::on_listWidgetConnectors_itemClicked()
{
    ui->pushButtonAdd->setEnabled(true);
}

void EquipmentCreator::on_listWidgetEquipment_itemClicked()
{
    ui->pushButtonDel->setEnabled(true);
}

void EquipmentCreator::on_listWidgetConnectors_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonAdd_clicked();
}

void EquipmentCreator::on_listWidgetEquipment_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonDel_clicked();
}

void EquipmentCreator::on_pushButtonExit_clicked()
{
    EquipmentCreator::close();
}

void EquipmentCreator::on_lineEditName_textChanged()
{
    enable_pushButtonCreate();
}

void EquipmentCreator::enable_pushButtonCreate()
{
    if(!listWidgetEquipment_isEmpty && !ui->lineEditName->text().isEmpty())
        ui->pushButtonCreate->setEnabled(true);
    else {
        ui->pushButtonCreate->setEnabled(false);
    }
}
