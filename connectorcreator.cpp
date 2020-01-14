#include "connectorcreator.h"
#include "ui_connectorcreator.h"
#include <QMessageBox>
#include <QRegExpValidator>

ConnectorCreator::ConnectorCreator(const QVector<Connector*> &connectors_in_project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectorCreator),
    connectors_in_project(connectors_in_project)
{
    ui->setupUi(this);

    QListWidgetItem *item = nullptr;
    if(!Connector::contains(connectors_in_project, Qt::red))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/red.png"), "красный");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkRed))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkred.png"), "бордовый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::blue))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/blue.png"), "синий");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkBlue))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkblue.png"), "темно-синий");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::cyan))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/cyan.png"), "бирюзовый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkCyan))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkcyan.png"), "аквамарин");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::green))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/green.png"), "зеленый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkGreen))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkgreen.png"), "темно-зеленый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::yellow))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/yellow.png"), "желтый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkYellow))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkyellow.png"), "темно-желтый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::gray))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/gray.png"), "перламутровый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkGray))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkgray.png"), "серый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::magenta))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/magenta.png"), "лиловый");
        ui->listWidget_color->addItem(item);
    }
    if(!Connector::contains(connectors_in_project, Qt::darkMagenta))
    {
        item = new QListWidgetItem(QIcon(":/rec/img/connectors/darkmagenta.png"), "темно-лиловый");
        ui->listWidget_color->addItem(item);
    }

    ui->button_create->setEnabled(false);
}

ConnectorCreator::~ConnectorCreator()
{
    delete ui;
}

void ConnectorCreator::on_listWidget_color_itemClicked()
{
    color_isSelected = true;
    if(!ui->lineEdit->text().isEmpty())
        ui->button_create->setEnabled(true);
}

void ConnectorCreator::on_lineEdit_textChanged()
{
    if(color_isSelected && !ui->lineEdit->text().isEmpty())
        ui->button_create->setEnabled(true);
    else
        ui->button_create->setEnabled(false);
}

void ConnectorCreator::on_button_create_clicked()
{
    if(ui->listWidget_color->currentItem()->text() == "красный")
    {
        connector = new ConnectorRed();
    }
    else if (ui->listWidget_color->currentItem()->text() == "бордовый")
    {
        connector = new ConnectorDarkRed();
    }
    else if (ui->listWidget_color->currentItem()->text() == "синий")
    {
        connector = new ConnectorBlue();
    }
    else if (ui->listWidget_color->currentItem()->text() == "темно-синий")
    {
        connector = new ConnectorDarkBlue();
    }
    else if (ui->listWidget_color->currentItem()->text() == "зеленый")
    {
        connector = new ConnectorGreen();
    }
    else if (ui->listWidget_color->currentItem()->text() == "темно-зеленый")
    {
        connector = new ConnectorDarkGreen();
    }else if (ui->listWidget_color->currentItem()->text() == "бирюзовый")
    {
        connector = new ConnectorCyan();
    }
    else if (ui->listWidget_color->currentItem()->text() == "аквамарин")
    {
        connector = new ConnectorDarkCyan();
    }
    else if (ui->listWidget_color->currentItem()->text() == "желтый")
    {
        connector = new ConnectorYellow();
    }
    else if (ui->listWidget_color->currentItem()->text() == "темно-желтый")
    {
        connector = new ConnectorDarkYellow();
    }
    else if (ui->listWidget_color->currentItem()->text() == "перламутровый")
    {
        connector = new ConnectorGray();
    }
    else if (ui->listWidget_color->currentItem()->text() == "серый")
    {
        connector = new ConnectorDarkGray();
    }
    else if (ui->listWidget_color->currentItem()->text() == "лиловый")
    {
        connector = new ConnectorMagenta();
    }
    else if (ui->listWidget_color->currentItem()->text() == "темно-лиловый")
    {
        connector = new ConnectorDarkMagenta();
    }

    connector->set_name(ui->lineEdit->text());

    ConnectorCreator::close();
}

void ConnectorCreator::on_button_back_clicked()
{
    ConnectorCreator::close();
}

Connector* ConnectorCreator::get_connector()
{
    return connector;
}
