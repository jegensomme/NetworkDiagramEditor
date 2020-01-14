#include "projectname.h"
#include "ui_projectname.h"
#include "QPushButton"
#include <QRegExpValidator>

ProjectName::ProjectName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectName)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegExp exp("[a-zA-Z]{1,9}[0-9]{0,2}");
    ui->projectName->setValidator(new QRegExpValidator(exp, this));
}

ProjectName::~ProjectName()
{
    delete ui;
}


void ProjectName::on_buttonBox_accepted()
{
    projectName = ui->projectName->text();
    ProjectName::close();
}

void ProjectName::on_buttonBox_rejected()
{
    projectName.clear();
    ProjectName::close();
}


void ProjectName::on_projectName_textChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->projectName->hasAcceptableInput());
}

QString ProjectName::get_projectName()
{
    return projectName;
}
