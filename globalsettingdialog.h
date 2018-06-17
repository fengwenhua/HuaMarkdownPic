#ifndef GLOBALSETTINGDIALOG_H
#define GLOBALSETTINGDIALOG_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <iostream>
#include <sstream>
#include <fstream>
#include <QMessageBox>

using namespace std;


namespace Ui {
class GlobalSettingDialog;
}

class GlobalSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalSettingDialog(QWidget *parent = 0);
    ~GlobalSettingDialog();
    void loadSettings();//读取设置
private slots:
    void on_changeDirButton_clicked();

    void on_enableRandomCheckBox_stateChanged(int arg1);

    void on_saveSettingButton_clicked();

private:
    Ui::GlobalSettingDialog *ui;
};

#endif // GLOBALSETTINGDIALOG_H
