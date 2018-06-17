#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H
//sdfpragma execution_character_set("utf-8")

#include <QDialog>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QMessageBox>
using namespace std;

namespace Ui {
class AccountDialog;
}

class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = 0);
    ~AccountDialog();
    void loadAccount();//读取文件秘钥信息

private slots:
    void on_pushButton_clicked();

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
