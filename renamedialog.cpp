#include "renamedialog.h"
#include "ui_renamedialog.h"

renameDialog::renameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renameDialog)
{
    ui->setupUi(this);
    sureChangeName=false;

    QFile loadSetting("dirSetting.ini");
    QString saveDirString="";
    if(loadSetting.open(QIODevice::ReadOnly))
    {
        QTextStream in(&loadSetting);
        saveDirString = in.readLine();
        qDebug()<<"saveDirString:"<<saveDirString;
        ui->dirLabel->setText(saveDirString);
    }
    else
    {
        ui->dirLabel->setText("image");
    }
    loadSetting.close();
}

renameDialog::~renameDialog()
{
    delete ui;
}

bool renameDialog::getSureChangeName()
{
    return sureChangeName;
}

void renameDialog::setSureChangeName(bool b)
{
    sureChangeName=b;
}

QString renameDialog::getUserRename()
{
    return ui->userRenameLineEdit->text();
}

QString renameDialog::getDir()
{

    return ui->dirLabel->text()+"/";
}

void renameDialog::setDir(QString dir)
{
    ui->dirLabel->setText(dir);
}


void renameDialog::on_sureSaveButton_clicked()
{
    sureChangeName=true;

    // 不能出现重复写的情况
    if(ui->enableRandomRadioButton->isChecked())//不再出现的按钮被选中
    {
        qDebug()<<"选中的不再出现的按钮";
        QString ture = "true";
        ofstream writeAccount("setting.ini");
        writeAccount<<ture.toStdString()<<endl;
        writeAccount.close();
    }
    this->close();
}

void renameDialog::on_changeDirButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择存放文件夹", "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->dirLabel->setText(dir);
}
