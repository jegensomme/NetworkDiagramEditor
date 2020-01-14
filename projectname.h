#ifndef PROJECTNAME_H
#define PROJECTNAME_H

#include <QDialog>

namespace Ui {
class ProjectName;
}

/**
 * Класс отвечает за ввод названия проекта
 */

class ProjectName : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectName(QWidget *parent = nullptr);
    ~ProjectName();
public:
    QString get_projectName();// возвращает название проекта

private slots:
    void on_buttonBox_accepted();// принять название

    void on_buttonBox_rejected();// отмена

    void on_projectName_textChanged();// действия при изменении текста в названии оборудрвания

private:
    Ui::ProjectName *ui;
    QString projectName = nullptr;
};

#endif // PROJECTNAME_H
