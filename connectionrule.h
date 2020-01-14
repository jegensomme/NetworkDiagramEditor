#ifndef CONNECTIONRULE_H
#define CONNECTIONRULE_H

#include <Qt>

/**
 * Класс предназначен для создания правил соединений
 * При создании класса устанавливаются начальные правила.
 * Обработка возможности установки пользовательских правил и получения правила в зависимости от вида коннектора
 */

class ConnectionRule
{
public:
    ConnectionRule();// устанавливаются правила соединения для коннекторов одного типа

public:
    void set_rule(Qt::GlobalColor color1, Qt::GlobalColor color2, bool rule);// устанавливает правило
    bool get_rule(Qt::GlobalColor color1, Qt::GlobalColor color2) const;// возвращает правило

private:
    int get_index(Qt::GlobalColor color) const;// перевод из цвета в индекс строки/столбца, вспомогательная функция
    static const int size = 14;// 14 видов цвета
    bool rules[size][size];// таблица правил
};

#endif // CONNECTIONRULE_H

