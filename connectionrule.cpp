#include "connectionrule.h"
#include <QDebug>

ConnectionRule::ConnectionRule()
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(i == j)
            {
                rules[i][j] = true;
            }
            else
            {
                rules[i][j] = false;
            }
        }
    }
}

void ConnectionRule::set_rule(Qt::GlobalColor color1, Qt::GlobalColor color2, bool rule)
{
    int col = get_index(color1);
    int row = get_index(color2);
    if (col != -1 && row != -1)
    {
        rules[row][col] = rule;
        rules[col][row] = rule;
    }
}

bool ConnectionRule::get_rule(Qt::GlobalColor color1, Qt::GlobalColor color2) const
{
    int col = get_index(color1);
    int row = get_index(color2);
    return rules[row][col];
}

int ConnectionRule::get_index(Qt::GlobalColor color) const
{
    int ind;
    switch (color)
    {
    case Qt::red:
    {
        ind = 0;
        break;
    }
    case Qt::darkRed:
    {
        ind = 1;
        break;
    }
    case Qt::blue:
    {
        ind = 2;
        break;
    }
    case Qt::darkBlue:
    {
        ind = 3;
        break;
    }
    case Qt::green:
    {
        ind = 4;
        break;
    }
    case Qt::darkGreen:
    {
        ind = 5;
        break;
    }
    case Qt::cyan:
    {
        ind = 6;
        break;
    }
    case Qt::darkCyan:
    {
        ind = 7;
        break;
    }
    case Qt::yellow:
    {
        ind = 8;
        break;
    }
    case Qt::darkYellow:
    {
        ind = 9;
        break;
    }
    case Qt::magenta:
    {
        ind = 10;
        break;
    }
    case Qt::darkMagenta:
    {
        ind = 11;
        break;
    }
    case Qt::gray:
    {
        ind = 12;
        break;
    }
    case Qt::darkGray:
    {
        ind = 13;
        break;
    }
    default:
        ind = -1;
        break;
    }
    return ind;
}
