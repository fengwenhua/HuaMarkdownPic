#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//sdfpragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QDebug>


#include <QPixmap>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include<QDragEnterEvent>
#include<QMimeData> //数据拖动在Qt中会被储存为MIME类型，在Qt中使用QMimeData类来表示MIME类型的数据
#include<QDropEvent>
#include<QUrl>

#include <QClipboard>

#include <QDateTime>
#include <QTimer>


#include "include/qiniu/base.h"
#include "include/qiniu/conf.h"
#include "include/qiniu/http.h"
#include "include/qiniu/io.h"
#include "include/qiniu/resumable_io.h"
#include "include/qiniu/rs.h"

#include "accountdialog.h"
#include "globalsettingdialog.h"

#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>


#include <QDesktopWidget>

#include <renamedialog.h>

#include <QFile>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keepLoadPic();


protected:
    void dragEnterEvent(QDragEnterEvent *event); //重写拖动进入事件
    void dropEvent(QDropEvent *event);// 放下事件

private slots:
    void updatePicEvent();
    void on_accoutAction_triggered();
    void on_globalSettingAction_triggered();
    void on_aboutAction_triggered();

private:
    Ui::MainWindow *ui;
    Qiniu_Mac mac;
    AccountDialog *accountDlg;
    renameDialog *rnd;
    GlobalSettingDialog *gsd;
    void saveAndUpload(QString userRename,QString now_time,QString dir,QPixmap pix,QClipboard *board);

};

#endif // MAINWINDOW_H
