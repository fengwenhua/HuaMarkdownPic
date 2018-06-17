#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <fstream>
#include <QFileDialog>

using namespace std;
namespace Ui {
class renameDialog;
}

class renameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit renameDialog(QWidget *parent = 0);
    ~renameDialog();
    bool getSureChangeName();
    void setSureChangeName(bool b);
    QString getUserRename();
    QString getDir();
    void setDir(QString dir);

private slots:


    void on_sureSaveButton_clicked();

    void on_changeDirButton_clicked();

private:
    Ui::renameDialog *ui;
    bool sureChangeName;
};

#endif // RENAMEDIALOG_H
