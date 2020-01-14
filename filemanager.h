#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#define SUCCSESS 0
#define ERROR_1 1
#define ERROR_2 2
#define ERROR_3 3
#define ERROR_4 4

#include "equipment.h"
#include "QDir"
#include "QFile"
#include "connectionrule.h"
#include "vepolyline.h"

/**
 * Класс отвечает за работу с файлами
 * При создании класса происходит инициализация имени проекта, пути проекта, пути библиотеки, главного пути, из которого запускается приложение.
 * Возможность создания/открытия проекта. Возможность удаления и добавления оборудование в проект/библиотеку/схему
 */

class FileManager : public QDir
{
public:
    //инициализация имени проекта, пути проекта, пути библиотеки, главного пути, из которого запускается приложение
    FileManager(QString &projectPath,
                const QString &mainPath,
                const QString &libraryPath,
                QString &projectName,
                QVector <Equipment*> &equipments_in_project,
                QVector <Connector*> &connectors_in_project,
                QVector <Equipment*> &equipments_in_library,
                QVector <Equipment*> &equipments_in_scheme,
                QVector <VEPolyline*> &connections,
                ConnectionRule *connectionRule
                );
    ~FileManager();

    int create_project();// создание проекта(создание необходимых файлов и открытие библиотеки)
    int open_project();// открытие проекта(считывание всей информации о проекте)
    bool add_to_project(Equipment *equipment);// добавление оборудования в файл проекта
    bool add_to_library(Equipment *equipment);// добавление оборудования в файл библиотеки
    bool save_project();// созранение проекта
    int save_as_project(QString newProjectPath);// сохрание проекта в соответсвии с выбранным путем

private:
    bool add_equipment(const Equipment *equipment, const QString &path);// сохранение информации об оборудовании в файл xml
    bool read_equipments();// считывание информации об оборудованиях из проекта
    bool read_scheme(); // // считывание информации об схеме
    bool read_library();// считывание информации об оборудованиях из библиотеки

private:
    const QString &mainPath;// путь из которого запускается приложение
    QString &projectName;// название проекта
    QString &projectPath;// путь проекта
    const QString &libraryPath;// путь библиотеки
    QVector <Equipment*> &equipments_in_project;
    QVector <Connector*> &connectors_in_project;
    QVector <Equipment*> &equipments_in_library;
    QVector <Equipment*> &equipments_in_scheme;
    QVector <VEPolyline*> &connections;// информация о связях между оборудованиями
    ConnectionRule *connectionRule;// правила соединений
};

#endif // FILEMANAGER_H
