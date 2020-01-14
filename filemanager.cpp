#include "filemanager.h"
#include "QFile"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include "QMessageBox"
#include <Qt>

FileManager::FileManager(QString &projectPath,
                         const QString &mainPath,
                         const QString &libraryPath,
                         QString &projectName,
                         QVector <Equipment*> &equipments_in_project,
                         QVector <Connector*> &connectors_in_project,
                         QVector <Equipment*> &equipments_in_library,
                         QVector <Equipment*> &equipments_in_scheme,
                         QVector <VEPolyline*> &connections,
                         ConnectionRule *connectionRule)
    :mainPath(mainPath),
     projectName(projectName),
     projectPath(projectPath),
     libraryPath(libraryPath),
     equipments_in_project(equipments_in_project),
     connectors_in_project(connectors_in_project),
     equipments_in_library(equipments_in_library),
     equipments_in_scheme(equipments_in_scheme),
     connections(connections),
     connectionRule(connectionRule)
{
}

FileManager::~FileManager()
{
    foreach(Equipment *equipment, equipments_in_project)
        delete equipment;
    equipments_in_project.clear();
    foreach(Equipment *equipment, equipments_in_library)
        delete equipment;
    equipments_in_library.clear();
    equipments_in_scheme.clear();
    connections.clear();
    foreach(Connector *connector, connectors_in_project)
        delete connector;
    connectors_in_project.clear();
    delete connectionRule;
}

int FileManager::create_project()
{
    this->setPath(mainPath);
    if(!this->exists())
        return ERROR_3;

    if(!this->exists("library"))
        this->mkdir("library");

    this->setPath(projectPath);
    if(this->exists(projectName))
        return ERROR_1;

    this->mkdir(projectName);
    projectPath = projectPath + "/" + projectName;
    this->setPath(projectPath);
    this->mkdir("equipments");

    QFile file(projectPath + "/scheme.xml");
    if (!file.open(QIODevice::WriteOnly))
        return ERROR_3;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("scheme");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    if(!read_library())
        return ERROR_2;

    return SUCCSESS;
}


int FileManager::open_project()
{
    this->setPath(mainPath);
    if(!this->exists())
        return ERROR_1;

    if(!this->exists("library"))
        this->mkdir("library");

    this->setPath(projectPath);
    if(!this->exists())
        return ERROR_1;

    projectName = this->dirName();
    if(!(this->exists("equipments") && this->exists("scheme.xml")))
        return ERROR_1;

    if(!read_equipments())
        return ERROR_2;

    if(!read_library())
        return ERROR_3;

    if(!read_scheme())
        return ERROR_4;

    return SUCCSESS;
}

bool FileManager::add_equipment(const Equipment *equipment, const QString &path)
{
    FileManager::setCurrent(path);
    QFile file(equipment->get_name() + ".xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("equipment");
    xmlWriter.writeStartElement("name");
    xmlWriter.writeCharacters(equipment->get_name());
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("connectors");
    foreach(Connector* connector, equipment->get_render()->get_connectors())
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(connector->get_color()));
        xmlWriter.writeStartElement("type");
        xmlWriter.writeCharacters(connector->get_name());
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();

    return true;
}

bool FileManager::add_to_project(Equipment *equipment)
{
    if(!add_equipment(equipment, projectPath + "/equipments"))
        return false;

    return true;
}

bool FileManager::add_to_library(Equipment *equipment)
{
    if(!add_equipment(equipment, libraryPath))
            return false;

    return true;
}

bool FileManager::save_project()
{
    this->setPath(projectPath + "/equipments");
    QStringList entryList = this->entryList();
    for(int i = 2; i < entryList.size(); i++)
    {
        if(!this->remove(entryList[i]))
            return false;
    }
    this->setPath(libraryPath);
    entryList = this->entryList();
    for(int i = 2; i < entryList.size(); i++)
    {
        if(!this->remove(entryList[i]))
            return false;
    }

    foreach(Equipment* equipment, equipments_in_project)
    {
        if(!add_to_project(equipment))
            return false;
    }

    foreach(Equipment* equipment, equipments_in_library)
    {
        if(!add_to_library(equipment))
            return false;
    }

    FileManager::setCurrent(projectPath);
    QFile file("scheme.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("scheme");
    xmlWriter.writeStartElement("equipments");
    foreach(Equipment* equipment, this->equipments_in_scheme)
    {
        xmlWriter.writeStartElement("equipment");
        xmlWriter.writeAttribute("id", QString::number(equipment->get_equipmentId()));
        xmlWriter.writeAttribute("x", QString::number(equipment->get_render()->get_body()->x()));
        xmlWriter.writeAttribute("y", QString::number(equipment->get_render()->get_body()->y()));
        xmlWriter.writeStartElement("name");
        xmlWriter.writeCharacters(equipment->get_name());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("description");
        xmlWriter.writeCharacters(equipment->get_description());
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("connectors");
        foreach(Connector* connector, equipment->get_render()->get_connectors())
        {
            xmlWriter.writeStartElement("connector");
            xmlWriter.writeAttribute("id", QString::number(connector->get_connectorId()));
            xmlWriter.writeAttribute("color", QString::number(connector->get_color()));

            xmlWriter.writeStartElement("link");
            if(connector->get_link() != nullptr)
            {
                xmlWriter.writeAttribute("eq_id", QString::number(connector->get_link()->get_equipmentId()));
                xmlWriter.writeAttribute("conn_id", QString::number(connector->get_link()->get_connectorId()));
            }
            else {
                xmlWriter.writeAttribute("eq_id", QString::number(0));
                xmlWriter.writeAttribute("conn_id", QString::number(0));
            }
            xmlWriter.writeStartElement("name");
            xmlWriter.writeCharacters(connector->get_name());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("description");
            xmlWriter.writeCharacters(connector->get_description());
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("connections");
    foreach(VEPolyline *connection, connections)
    {
        xmlWriter.writeStartElement("connection");
        xmlWriter.writeAttribute("id", QString::number(connection->get_connectionId()));
        xmlWriter.writeAttribute("eqId_first", QString::number(connection->get_first()->get_id()));
        xmlWriter.writeAttribute("eqId_end", QString::number(connection->get_end()->get_id()));
        xmlWriter.writeAttribute("connId_first", QString::number(connection->get_connectorIdFirst()));
        xmlWriter.writeAttribute("connId_end", QString::number(connection->get_connectorIdEnd()));
        for(int i = 0; i < connection->path().elementCount(); i++)
        {
            xmlWriter.writeStartElement("point");
            xmlWriter.writeAttribute("x", QString::number(connection->path().elementAt(i).x));
            xmlWriter.writeAttribute("y", QString::number(connection->path().elementAt(i).y));
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeStartElement("description");
        xmlWriter.writeCharacters(connection->get_description());
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("connectorTypes");
    foreach(Connector *connector, connectors_in_project)
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(connector->get_color()));
        xmlWriter.writeStartElement("name");
        xmlWriter.writeCharacters(connector->get_name());
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("rules");
    for(int i = 0; i < connectors_in_project.size(); i++)
    {
        for(int j = i; j < connectors_in_project.size(); j++)
        {
            xmlWriter.writeStartElement("rule");
            xmlWriter.writeAttribute("color1", QString::number(connectors_in_project[i]->get_color()));
            xmlWriter.writeAttribute("color2", QString::number(connectors_in_project[j]->get_color()));
            xmlWriter.writeAttribute("bool", connectionRule->get_rule(connectors_in_project[i]->get_color(),
                                                                      connectors_in_project[j]->get_color()) ? "true" : "false");
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();

    return true;
}

int FileManager::save_as_project(QString newProjectPath)
{
    this->setPath(newProjectPath);
    if(!this->exists())
        return ERROR_3;

    if(newProjectPath == projectPath)
        return ERROR_1;

    this->setPath(projectPath);
    QString name = this->dirName();
    this->setPath(newProjectPath);
    if(this->exists(name))
        return ERROR_2;

    if(!save_project())
        return ERROR_3;

    this->setPath(newProjectPath);
    this->mkdir(name);
    newProjectPath = newProjectPath + "/" + name;
    this->setPath(newProjectPath);
    this->mkdir("equipments");

    if(!QFile::copy(projectPath + "/scheme.xml", newProjectPath + "/scheme.xml"))
        return ERROR_3;

    this->setPath(projectPath + "/equipments");
    QStringList entryList = this->entryList();
    for(int i = 2; i < entryList.size(); i++)
    {
        if(!QFile::copy(projectPath + "/equipments/" + entryList[i], newProjectPath + "/equipments/" + entryList[i]))
            return ERROR_3;
    }

    this->setPath(projectPath);
    this->removeRecursively();
    projectPath = newProjectPath;

    return SUCCSESS;
}

bool FileManager::read_equipments()
{
    FileManager::setCurrent(projectPath + "/equipments");
    this->setPath(projectPath);
    if(!this->exists("equipments"))
        return false;

    this->setPath(projectPath + "/equipments");
    QStringList entryList = this->entryList();
    for(int i = 2; i < entryList.size(); i++)
    {
        QFile file(entryList[i]);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return false;
        else{
             QString name;
             QVector <Connector*> connectors;

             QXmlStreamReader xmlReader;
             xmlReader.setDevice(&file);
             while(!(xmlReader.name() == "equipment" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                 xmlReader.readNext();
             if(xmlReader.isEndDocument())
                 continue;

             while(!(xmlReader.name() == "name" && xmlReader.isStartElement()))
                 xmlReader.readNext();

             if(xmlReader.name() == "name" && xmlReader.isStartElement())
                 name = xmlReader.readElementText();

             while(xmlReader.name() != "connectors")
                 xmlReader.readNext();

             while(!(xmlReader.name() == "connectors" && xmlReader.isEndElement()))
             {
                 if(xmlReader.name() == "connector" && xmlReader.isStartElement())
                 {
                     foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                     {
                         connectors.push_back(Connector::set_color((Qt::GlobalColor)attr.value().toInt()));
                     }
                     while(!(xmlReader.name() == "type" && xmlReader.isStartElement()))
                         xmlReader.readNext();

                     if(xmlReader.name() == "type" && xmlReader.isStartElement())
                         connectors.last()->set_name(xmlReader.readElementText());
                 }
                 xmlReader.readNext();
             }
             Equipment* equipment = new Equipment(connectors);
             equipment->set_name(name);
             equipments_in_project.push_back(equipment);
        }
        file.close();
    }

    return true;
}

bool FileManager::read_library()
{
    FileManager::setCurrent(libraryPath);
    this->setPath(mainPath);
    if(!this->exists("library"))
        return false;

    this->setPath(libraryPath);
    QStringList entryList = this->entryList();
    for(int i = 2; i < entryList.size(); i++)
    {
        QFile file(entryList[i]);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            continue;
        else{
            QString name;
            QVector <Connector*> connectors;

            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&file);
            while(!(xmlReader.name() == "equipment" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                xmlReader.readNext();
            if(xmlReader.isEndDocument())
                continue;

            while(xmlReader.name() != "name")
                xmlReader.readNext();
            name = xmlReader.readElementText();
            while(xmlReader.name() != "connectors")
                xmlReader.readNext();
            while(!(xmlReader.name() == "connectors" && xmlReader.isEndElement()))
            {
                if(xmlReader.name() == "connector" && xmlReader.isStartElement())
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        connectors.push_back(Connector::set_color((Qt::GlobalColor)attr.value().toInt()));
                    }
                    while(!(xmlReader.name() == "type" && xmlReader.isStartElement()))
                        xmlReader.readNext();

                    if(xmlReader.name() == "type" && xmlReader.isStartElement())
                        connectors.last()->set_name(xmlReader.readElementText());
                }
                xmlReader.readNext();
            }

            Equipment* equipment = new Equipment(connectors);
            equipment->set_name(name);
            equipments_in_library.push_back(equipment);
        }
        file.close();
    }

    return true;
}

bool FileManager::read_scheme()
{
    FileManager::setCurrent(projectPath);
    this->setPath(projectPath);
    if(!this->exists("scheme.xml"))
        return false;

    QFile file("scheme.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    else {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        while(!(xmlReader.name() == "scheme" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
            xmlReader.readNext();
        if(xmlReader.isEndDocument())
            return false;

        QVector <QVector <int>> linkConnectorId_list_list;
        QVector <QVector <int>> linkEquipmentId_list_list;
        while(!xmlReader.atEnd())
        {
            if(xmlReader.name() == "equipments" && xmlReader.isStartElement())
            {
                while(!(xmlReader.name() == "equipments" && xmlReader.isEndElement()))
                {
                    if(xmlReader.name() == "equipment" && xmlReader.isStartElement())
                    {
                        QVector <Connector*> connectors;
                        QVector <int> id_list;
                        QVector <int> linkConnectorId_list;
                        QVector <int> linkEquipmentId_list;
                        QVector <QString> connectorDescription_list;
                        QVector <QString> connectorName_list;
                        int equipmentId = 0;
                        int x = 0, y = 0;
                        QString name;
                        QString description;
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if(attr.name() == "id")
                                equipmentId = attr.value().toInt();
                            else if(attr.name() == "x")
                                x = attr.value().toInt();
                            else if(attr.name() == "y")
                                y = attr.value().toInt();
                        }

                        while(!(xmlReader.name() == "name" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                            xmlReader.readNext();
                        if(xmlReader.isEndDocument())
                            return false;

                        if(xmlReader.name() == "name" && xmlReader.isStartElement())
                            name = xmlReader.readElementText();

                        while(!(xmlReader.name() == "description" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                            xmlReader.readNext();
                        if(xmlReader.isEndDocument())
                            return false;

                        if(xmlReader.name() == "description" && xmlReader.isStartElement())
                            description = xmlReader.readElementText();

                        while(!(xmlReader.name() == "connectors" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                            xmlReader.readNext();
                        if(xmlReader.isEndDocument())
                            return false;

                        if(xmlReader.name() == "connectors" && xmlReader.isStartElement())
                        {
                            linkEquipmentId_list.clear();
                            linkConnectorId_list.clear();
                            connectorDescription_list.clear();
                            connectorName_list.clear();
                            id_list.clear();
                            while(!(xmlReader.name() == "connectors" && xmlReader.isEndElement()))
                            {
                                if(xmlReader.name() == "connector" && xmlReader.isStartElement())
                                {
                                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                                    {
                                        if(attr.name().toString() == "id")
                                            id_list.push_back(attr.value().toInt());
                                        else if(attr.name().toString() == "color")
                                            connectors.push_back(Connector::set_color((Qt::GlobalColor)attr.value().toInt()));
                                    }
                                    while(!(xmlReader.name() == "link" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                                        xmlReader.readNext();
                                    if(xmlReader.isEndDocument())
                                        return false;

                                    if(xmlReader.name() == "link" && xmlReader.isStartElement())
                                    {
                                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                                        {
                                            if(attr.name().toString() == "conn_id")
                                                linkConnectorId_list.push_back(attr.value().toInt());
                                            else if(attr.name().toString() == "eq_id")
                                                linkEquipmentId_list.push_back(attr.value().toInt());
                                        }
                                    }
                                    while(!(xmlReader.name() == "name" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                                        xmlReader.readNext();
                                    if(xmlReader.isEndDocument())
                                        return false;

                                    if(xmlReader.name() == "name" && xmlReader.isStartElement())
                                    {
                                        connectorName_list.push_back(xmlReader.readElementText());
                                    }

                                    while(!(xmlReader.name() == "description" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                                        xmlReader.readNext();
                                    if(xmlReader.isEndDocument())
                                        return false;

                                    if(xmlReader.name() == "description" && xmlReader.isStartElement())
                                    {
                                        connectorDescription_list.push_back(xmlReader.readElementText());
                                    }
                                }
                                xmlReader.readNext();
                            }
                        }
                        Equipment* equipment = new Equipment(connectors);
                        equipment->set_id(equipmentId);
                        equipment->set_name(name);
                        equipment->set_description(description);
                        equipment->get_render()->get_body()->setPos(x, y);
                        for(int i = 0; i < id_list.size(); i++)
                        {
                            connectors[i]->set_connectorId(id_list[i]);
                            connectors[i]->set_equipmentId(equipmentId);
                            connectors[i]->set_description(connectorDescription_list[i]);
                            connectors[i]->set_name(connectorName_list[i]);
                        }
                        equipments_in_scheme.push_back(equipment);
                        linkEquipmentId_list_list.push_back(linkEquipmentId_list);
                        linkConnectorId_list_list.push_back(linkConnectorId_list);
                    }
                xmlReader.readNext();
                }
            }
            else if(xmlReader.name() == "connections" && xmlReader.isStartElement())
            {
                while(!(xmlReader.name() == "connections" && xmlReader.isEndElement()))
                {
                    if(xmlReader.name() == "connection" && xmlReader.isStartElement())
                    {
                        QPainterPath path;
                        int eqId_first = 0;
                        int eqId_end = 0;
                        int connId_first = 0;
                        int connId_end = 0;
                        int id = 0;
                        QVector <int> xCoord;
                        QVector <int> yCoord;
                        QString description;
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if(attr.name().toString() == "id")
                                id = attr.value().toInt();
                            else if(attr.name().toString() == "eqId_first")
                                eqId_first = attr.value().toInt();
                            else if(attr.name().toString() == "eqId_end")
                                eqId_end = attr.value().toInt();
                            else if(attr.name().toString() == "connId_first")
                                connId_first = attr.value().toInt();
                            else if(attr.name().toString() == "connId_end")
                                connId_end = attr.value().toInt();
                        }
                        while(!(xmlReader.name() == "connection" && xmlReader.isEndElement()))
                        {
                            if(xmlReader.name() == "point" && xmlReader.isStartElement())
                            {
                                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                                {
                                    if(attr.name().toString() == "x")
                                        xCoord.push_back(attr.value().toInt());
                                    else if(attr.name().toString() == "y")
                                        yCoord.push_back(attr.value().toInt());
                                }
                            }
                            else if(xmlReader.name() == "description" && xmlReader.isStartElement())
                                description = xmlReader.readElementText();
                            xmlReader.readNext();
                        }            
                        path.moveTo(xCoord[0], yCoord[0]);
                        for(int i = 1; i < xCoord.size() - 1; i++)
                        {
                            path.lineTo(xCoord[i], yCoord[i]);
                            path.moveTo(xCoord[i], yCoord[i]);
                        }
                        path.lineTo(xCoord[xCoord.size() - 1], yCoord[yCoord.size() - 1]);

                        Body *bodyFirst = equipments_in_scheme[eqId_first - 1]->get_render()->get_body();
                        Body *bodyEnd = equipments_in_scheme[eqId_end - 1]->get_render()->get_body();
                        VEPolyline *polyline = new VEPolyline(bodyFirst, bodyEnd);
                        polyline->set_connectorIdFirst(connId_first);
                        polyline->set_connectorIdEnd(connId_end);
                        polyline->set_connectionId(id);
                        polyline->setPath(path);
                        QPen pen;
                        pen.setWidth(2);
                        polyline->setPen(pen);
                        polyline->setZValue(-1);
                        polyline->set_description(description);
                        connections.push_back(polyline);
                    }
                    xmlReader.readNext();
                }
            }
            else if(xmlReader.name() == "connectorTypes" && xmlReader.isStartElement())
            {
                while(!(xmlReader.name() == "connectorTypes" && xmlReader.isEndElement()))
                {
                    if(xmlReader.name() == "connector" && xmlReader.isStartElement())
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if(attr.name().toString() == "color")
                                connectors_in_project.push_back(Connector::set_color((Qt::GlobalColor)attr.value().toInt()));
                        }
                        while(!(xmlReader.name() == "name" && xmlReader.isStartElement()) && !xmlReader.isEndDocument())
                            xmlReader.readNext();
                        if(xmlReader.isEndDocument())
                            return false;

                        if(xmlReader.name() == "name" && xmlReader.isStartElement())
                            connectors_in_project.last()->set_name(xmlReader.readElementText());
                    }
                    xmlReader.readNext();
                }
            }
            else if(xmlReader.name() == "rules" && xmlReader.isStartElement())
            {
                while(!(xmlReader.name() == "rules" && xmlReader.isEndElement()))
                {
                    if(xmlReader.name() == "rule" && xmlReader.isStartElement())
                    {
                        int color1 = 0;
                        int color2 = 0;
                        bool rule = false;
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if(attr.name().toString() == "color1")
                                color1 = attr.value().toInt();
                            else if(attr.name().toString() == "color2")
                                color2 = attr.value().toInt();
                            else if(attr.name().toString() == "bool")
                               rule = attr.value().toString() == "true" ? true : false;
                        }
                        connectionRule->set_rule((Qt::GlobalColor)color1, (Qt::GlobalColor)color2, rule);
                    }
                    xmlReader.readNext();
                }
            }
            xmlReader.readNext();
        }
        file.close();

        for(int i = 0; i < equipments_in_scheme.size(); i++)
        {
            for(int j = 0; j < linkEquipmentId_list_list[i].size(); j++)
            {
                if(linkEquipmentId_list_list[i][j] != 0)
                {
                    int connId = linkConnectorId_list_list[i][j] - 1;
                    int eqId = linkEquipmentId_list_list[i][j] - 1;
                    Connector *link = equipments_in_scheme[eqId]->get_render()->get_connectors()[connId];
                    QVector<Connector*> connectors = equipments_in_scheme[i]->get_render()->get_connectors();
                    connectors[j]->set_link(link);
                }
            }
        }
    }

    return true;
}
