#include "accountdialog.h"
#include "ui_accountdialog.h"




AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
}

AccountDialog::~AccountDialog()
{
    delete ui;
}

void AccountDialog::loadAccount()
{
    ifstream loadAccount("account.ini",ios::in);
    if(loadAccount.is_open())//可以打开才继续读
    {
        char line[1024]={0};

        int i=0;
        string bucketString = "";
        string accessKeyString = "";
        string secretKeyString = "";
        string domainString = "";
        while(loadAccount.getline(line,sizeof(line)))
        {
            stringstream word(line);
            if(i==0)
            {
                word>>bucketString;

                i++;
                continue;
            }

            if(i==1)
            {
                word>>accessKeyString;

                i++;
                continue;
            }
            if(i==2)
            {
                word>>secretKeyString;
                i++;
                continue;
            }
            if(i==3)
            {
                word>>domainString;
                i++;

                continue;
            }
            if(i==4)
            {
                break;
            }

        }

        ui->bucketLineEdit->setText(QString::fromStdString(bucketString));
        ui->accessKeyLineEdit->setText(QString::fromStdString(accessKeyString));
        ui->secretKeyLineEdit->setText(QString::fromStdString(secretKeyString));
        ui->domainLineEdit->setText(QString::fromStdString(domainString));

    }

}



void AccountDialog::on_pushButton_clicked()
{
    QString bucket;
    QString accessKey;
     QString secretKey;
     QString domain;
    if(ui->bucketLineEdit->text().isEmpty())
    {
        ui->bucketLineEdit->setFocus();
        return;
    }
    else
    {
        bucket = ui->bucketLineEdit->text();
    }

    if(ui->accessKeyLineEdit->text().isEmpty())
    {
        ui->accessKeyLineEdit->setFocus();
        return;
    }
    else
    {
        accessKey = ui->accessKeyLineEdit->text();
    }

    if(ui->secretKeyLineEdit->text().isEmpty())
    {
        ui->secretKeyLineEdit->setFocus();
        return;
    }
    else
    {
        secretKey = ui->secretKeyLineEdit->text();
    }

    if(ui->domainLineEdit->text().isEmpty())
    {
        ui->domainLineEdit->setFocus();
        return;
    }
    else
    {
        domain = ui->domainLineEdit->text();
    }

    QString httpString="http://";
    domain=domain.trimmed();// 由于domain要进行于http://的拼接,因此要先过滤前后空格,否则会有bug
    if(!domain.contains(httpString,Qt::CaseSensitive))
        domain=httpString+domain;


    qDebug()<<"bucket: "<<bucket;
    qDebug()<<"accessKey: "<<accessKey;
    qDebug()<<"secretKey: "<< secretKey;
    qDebug()<<"domain(accountdialog): "<< domain;
    // 后期记得加上输入为空的判断
    ofstream writeAccount("account.ini");
    writeAccount<<bucket.trimmed().toStdString()<<endl;
    writeAccount<<accessKey.trimmed().toStdString()<<endl;
    writeAccount<<secretKey.trimmed().toStdString()<<endl;
    writeAccount<<domain.toStdString()<<endl;

    writeAccount.close();

    QMessageBox::about(this,"提示","保存成功");
    this->close();// 点击确定后关闭账号设置窗口
}
