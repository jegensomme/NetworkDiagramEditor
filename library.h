#ifndef LIBRARY_H
#define LIBRARY_H

#include <QDialog>
#include "equipment.h"

/**
 * Класс описывающий библиотеку
 * Возможность добавления/удаления оборудования в/из библиотеки
 */

namespace Ui {
class Library;
}

class Library : public QDialog
{
    Q_OBJECT

public:
    /*
     * Добавление в виджеты WidgetsLibrary и WidgetsProject списки оборудований
     * инициализируются все необходимые данные для работы с библиотекой
     */
    explicit Library(QVector <Equipment*> &equipments_in_library,
                     QVector<Equipment*> &equipments_in_project,
                     QWidget *parent = nullptr);
    ~Library();

private slots: 
    void on_pushAdd_clicked();// добавить в виджет

    void on_pushDelete_clicked();// удалить из виджета

    void on_ListWidgetsLibrary_itemClicked();// реакция на нажатие на объект из виджета 1

    void on_ListWidgetsLibrary_itemDoubleClicked();// реакция на двойной клик по объекту из виджета 1

    void on_ListWidgetsProject_itemClicked();// реакция на нажатие на объект из виджета 2

    void on_ListWidgetsProject_itemDoubleClicked();// реакция на двойной клик по объекту из виджета 1

    void on_pushOk_clicked();// завершение работы с библиокой

private:
    Ui::Library *ui;
    bool library_hasFocus;
    bool project_hasFocus;
    QVector<Equipment*> &equipments_in_project;
    QVector<Equipment*> &equipments_in_library;
};

#endif // LIBRARY_H
