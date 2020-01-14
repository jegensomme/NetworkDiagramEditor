#include "addrule.h"
#include "ui_addrule.h"
#include "QDebug"

AddRule::AddRule(const QVector<Connector*> &connectors_in_project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRule),
    connectors_in_project(connectors_in_project)
{
    ui->setupUi(this);
    ui->allow->setEnabled(false);
    ui->ban->setEnabled(false);

    listWidget_1_clicked = false;
    listWidget_2_clicked = false;

    foreach(Connector *connector, this->connectors_in_project)
    {
        switch(connector->get_color())
        {
        case Qt::red:
        {
            if(Connector::contains(connectors_in_project, Qt::red))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/red.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/red.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkRed:
        {
            if(Connector::contains(connectors_in_project, Qt::darkRed))
            {
               ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkred.png"), connector->get_name()));
               ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkred.png"), connector->get_name()));
            }
            break;
        }
        case Qt::blue:
        {
            if(Connector::contains(connectors_in_project, Qt::blue))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/blue.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/blue.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkBlue:
        {
            if(Connector::contains(connectors_in_project, Qt::darkBlue))
            {
               ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkblue.png"), connector->get_name()));
               ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkblue.png"), connector->get_name()));
            }
            break;
        }
        case Qt::cyan:
        {
            if(Connector::contains(connectors_in_project, Qt::cyan))
            {

               ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/cyan.png"), connector->get_name()));
               ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/cyan.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkCyan:
        {
            if(Connector::contains(connectors_in_project, Qt::darkCyan))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkcyan.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkcyan.png"), connector->get_name()));
            }
            break;
        }
        case Qt::green:
        {
            if(Connector::contains(connectors_in_project, Qt::green))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/green.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/green.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkGreen:
        {
            if(Connector::contains(connectors_in_project, Qt::darkGreen))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkgreen.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkgreen.png"), connector->get_name()));
            }
            break;
        }
        case Qt::yellow:
        {
            if(Connector::contains(connectors_in_project, Qt::yellow))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/yellow.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/yellow.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkYellow:
        {
            if(Connector::contains(connectors_in_project, Qt::darkYellow))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkyellow.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkyellow.png"), connector->get_name()));
            }
            break;
        }
        case Qt::gray:
        {
            if(Connector::contains(connectors_in_project, Qt::gray))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/gray.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/gray.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkGray:
        {
            if(Connector::contains(connectors_in_project, Qt::darkGray))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkgray.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkgray.png"), connector->get_name()));
            }
            break;
        }
        case Qt::magenta:
        {
            if(Connector::contains(connectors_in_project, Qt::magenta))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/magenta.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/magenta.png"), connector->get_name()));
            }
            break;
        }
        case Qt::darkMagenta:
        {
            if(Connector::contains(connectors_in_project, Qt::darkMagenta))
            {
                ui->listWidget->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkmagenta.png"), connector->get_name()));
                ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/rec/img/connectors/darkmagenta.png"), connector->get_name()));
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

AddRule::~AddRule()
{
    delete ui;
}

void AddRule::on_listWidget_itemClicked()
{
    listWidget_1_clicked = true;
    if(listWidget_2_clicked)
    {
        ui->allow->setEnabled(true);
        ui->ban->setEnabled(true);
    }
    color1_text = ui->listWidget->currentItem()->text();
}

void AddRule::on_listWidget_2_itemClicked()
{
    listWidget_2_clicked = true;
    if(listWidget_1_clicked)
    {
        ui->allow->setEnabled(true);
        ui->ban->setEnabled(true);
    }
    color2_text = ui->listWidget_2->currentItem()->text();
}

void AddRule::add_rule()
{
    foreach(Connector *connector, connectors_in_project)
    {
        if(color1_text == connector->get_name())
            color1 = connector->get_color();
        if(color2_text == connector->get_name())
            color2 = connector->get_color();
    }
}

Qt::GlobalColor AddRule::get_color1()
{
    return color1;
}

Qt::GlobalColor AddRule::get_color2()
{
    return color2;
}

bool AddRule::get_rule()
{
    return rule;
}

bool AddRule::isReject()
{
    return reject;
}

void AddRule::on_reject_clicked()
{
    reject = true;
    AddRule::close();
}

void AddRule::on_allow_clicked()
{
    rule = true;
    add_rule();
    AddRule::close();
}

void AddRule::on_ban_clicked()
{
    rule = false;
    add_rule();
    AddRule::close();
}
