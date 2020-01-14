#ifndef CONNECTORCREATOR_H
#define CONNECTORCREATOR_H

#include <QDialog>
#include <connector.h>

namespace Ui {
class ConnectorCreator;
}

/**
 * Класс предназначен для создания коннектора
 * выбирается цвет и присваивается имя
 */

class ConnectorCreator : public QDialog
{
    Q_OBJECT

public:
    //В виджет добавляются еще не использованные цвета коннекторов
    explicit ConnectorCreator(const QVector<Connector*> &connectors_in_project ,QWidget *parent = nullptr);
    ~ConnectorCreator();

    Connector* get_connector();// возвращает коннектор

private slots:
    void on_listWidget_color_itemClicked();// реакция на клик по объекту из виджета

    void on_lineEdit_textChanged();// реакция на изменение текста в поле для названия коннектора

    void on_button_back_clicked();// при нажатии закрывается окно"

    void on_button_create_clicked();// при нажатии создается новый коннектор"

private:
    Ui::ConnectorCreator *ui;
    bool color_isSelected = false;// выбран ли цвет
    Connector *connector = nullptr;
    const QVector<Connector*> &connectors_in_project;
};

#endif // CONNECTORCREATOR_H
