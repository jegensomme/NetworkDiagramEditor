#include "selectpath.h"
#include "ui_selectpath.h"
#include "QPushButton"

SelectPath::SelectPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPath)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    model = new QFileSystemModel;
    model->setFilter(QDir::Dirs);
    model->setRootPath("");
    ui->listView->setModel(model);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

SelectPath::~SelectPath()
{
    delete ui;
}

void SelectPath::on_listView_doubleClicked(const QModelIndex &index)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QListView *listView = ui->listView;
    QFileInfo fileInfo = model->fileInfo(index);
    if(fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if(fileInfo.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));
    }
    else if(fileInfo.isDir())
    {
        listView->setRootIndex(index);
    }


}

void SelectPath::on_buttonBox_accepted()
{
    projectPath = model->filePath(current);
    SelectPath::close();
}

void SelectPath::on_buttonBox_rejected()
{
    projectPath.clear();
    SelectPath::close();
}

void SelectPath::on_listView_clicked(const QModelIndex &index)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    current = index;
}

QString SelectPath::get_projectPath()
{
    return projectPath;
}
