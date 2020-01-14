#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDir>

namespace Ui {
class SelectPath;
}

/**
 * Класс описывает файловый проводник
 */

class SelectPath : public QDialog
{
    Q_OBJECT

public:
    //Инициализация окна
    explicit SelectPath(QWidget *parent = nullptr);
    ~SelectPath();

    QString get_projectPath();// возвращает путь

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);// реакция на двойной клик

    void on_buttonBox_accepted();// принять

    void on_buttonBox_rejected();// отмена

    void on_listView_clicked(const QModelIndex &index);// реакция на клик

private:
    QString projectPath = nullptr;
    Ui::SelectPath *ui;
    QFileSystemModel *model;
    QModelIndex current;
};

#endif // SELECTPATH_H
