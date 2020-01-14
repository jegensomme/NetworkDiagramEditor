#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QDialog>

namespace Ui {
class CreateProject;
}

class CreateProject : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProject(QWidget *parent = nullptr);
    ~CreateProject();

signals:
    void projectName(const QString &str);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_nameProject_textChanged();

private:
    Ui::CreateProject *ui;
};

#endif // CREATEPROJECT_H
