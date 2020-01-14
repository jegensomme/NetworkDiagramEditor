#include "createproject.h"
#include "ui_createproject.h"
#include "QPushButton"
#include "QString"
#include <QRegExpValidator>

CreateProject::CreateProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProject)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegExp exp("[a-zA-Z]{1,9}[1-9]{0,2}");
    ui->nameProject->setValidator(new QRegExpValidator(exp, this));
}

CreateProject::~CreateProject()
{
    delete ui;
}

void CreateProject::on_buttonBox_accepted()
{
    emit projectName(ui->nameProject->text());
    CreateProject::close();
}

void CreateProject::on_buttonBox_rejected()
{
    CreateProject::close();
}

void CreateProject::on_nameProject_textChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->nameProject->hasAcceptableInput());
}
