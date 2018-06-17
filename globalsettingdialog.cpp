#include "globalsettingdialog.h"
#include "ui_globalsettingdialog.h"

GlobalSettingDialog::GlobalSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobalSettingDialog)
{
    ui->setupUi(this);
}

GlobalSettingDialog::~GlobalSettingDialog()
{
    delete ui;
}

void GlobalSettingDialog::loadSettings()
{
    // 读取图片存放路径
    QFile loadSetting("dirSetting.ini");
    QString loadSettingString="";
    QString saveDirString="";
    if(loadSetting.open(QIODevice::ReadOnly))
    {
        QTextStream in(&loadSetting);
        saveDirString = in.readLine();
        qDebug()<<"saveDirString:"<<saveDirString;
    }
    else
    {
        saveDirString="image";
    }
    loadSetting.close();
    ui->pictureSaveDirLabel->setText(saveDirString);

    // 读取是否开始随机命名
    QFile isRandomName("setting.ini");
    QString isRandom="";
    QString isRandomDemo="true";
    if(isRandomName.open(QIODevice::ReadOnly))
    {
        QTextStream in(&isRandomName);
        isRandom = in.readLine();
        qDebug()<<"isRandom:"<<isRandom;
    }

    if(!QString::compare(isRandom,isRandomDemo))
    {
        ui->enableRandomCheckBox->setChecked(true);
    }

    isRandomName.close();

}


void GlobalSettingDialog::on_changeDirButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择存放文件夹", "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ofstream writeAccount("dirSetting.ini");
    writeAccount<<dir.trimmed().toStdString()<<endl;
    writeAccount.close();
    //rnd->setDir(dir);
     ui->pictureSaveDirLabel->setText(dir);
    //QMessageBox::information(this,"提示","目录修改成功");

}

// 随机命名的勾勾
// 选择是2,取消是0
void GlobalSettingDialog::on_enableRandomCheckBox_stateChanged(int arg1)
{
    if(arg1==2)
    {
        qDebug()<<"zhe"<<arg1;
        QString ture = "true";
        ofstream writeAccount("setting.ini");
        writeAccount<<ture.toStdString()<<endl;
        writeAccount.close();
    }
    else
    {
        qDebug()<<"zhe"<<arg1;
        QString f = "false";
        ofstream writeAccount("setting.ini");
        writeAccount<<f.toStdString()<<endl;
        writeAccount.close();
    }

}

void GlobalSettingDialog::on_saveSettingButton_clicked()
{
    this->close();
}
