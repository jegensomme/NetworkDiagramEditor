#ifndef ADDRULE_H
#define ADDRULE_H

#include <QDialog>
#include "connector.h"

// Класс для создания правил соединения коннекторов

namespace Ui {
class AddRule;
}

/**
 * Класс служит для добавления правил соединения
 * Пользователь может добавить правила соединения: устанавить разрешающее правило или запрещающее правило.
 */

class AddRule : public QDialog
{
    Q_OBJECT

public:
    //добавление видов коннекторов в List Widget's. Происходит обработка List Widget's на выбор коннектора.
    explicit AddRule(const QVector<Connector*> &connectors_in_project, QWidget *parent = nullptr);
    ~AddRule();

public:
    Qt::GlobalColor get_color1();// Возвращает тип первого коннекора
    Qt::GlobalColor get_color2();// Возвращает тип второго коннекора
    bool get_rule();// Возвращает правило
    bool isReject();// Проверка на нажание "отмена"
private slots:
    void on_listWidget_itemClicked();// реакция на нажатие первого виджета
    void on_listWidget_2_itemClicked();// реакция на нажатие второго виджета
    void add_rule();// добавить правило"
    void on_reject_clicked();// реакция на нажатие "отмена"
    void on_allow_clicked();// разрешить соединение
    void on_ban_clicked();// запертить соединеие

private:
    Ui::AddRule *ui;
    bool listWidget_1_clicked;
    bool listWidget_2_clicked;
    QString color1_text;
    QString color2_text;
    bool reject = false;
    Qt::GlobalColor color1;
    Qt::GlobalColor color2;
    bool rule;
    const QVector<Connector*> &connectors_in_project;
};

#endif // ADDRULE_H
