#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
    Qiniu_Global_Init(-1);                  /* 全局初始化函数，整个进程只需要调用一次 */
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    Qiniu_Global_Cleanup();                 /* 全局清理函数，只需要在进程退出时调用一次 */
    delete ui;
}






void MainWindow::updatePicEvent()
{
    // 监控剪切板
    QClipboard *board = QApplication::clipboard();
    QPixmap pix;

    // 读取缓冲区图片并显示在Label上

    //qDebug()<<"in";
    pix =board->pixmap();
    if(!pix.isNull())
    {

        QFile dirSetting("dirSetting.ini");
        QString line="";
        if(dirSetting.open(QIODevice::ReadOnly))
        {
            QTextStream in(&dirSetting);
            line = in.readLine();
        }
        else
        {
            line="image";
        }
        QString dir = line;

        QDir qDir(dir);
        if(!qDir.exists())//文件夹不存在则创建
        {
            qDir.mkpath(dir);
        }
        dir=dir+"/";

        QDateTime time = QDateTime::currentDateTime();   //获取当前时间
        int t=time.toTime_t();//转换成时间戳,需要QDateTime头文件
        QString now_time=QString::number(t);//将时间戳转换为QString
        QString userRename="";


        QFile loadSetting("setting.ini");
        if(loadSetting.open(QIODevice::ReadOnly))
        {
            QTextStream in(&loadSetting);
            QString line = in.readLine();
            qDebug()<<"zhe line:"<<line;
//            while(!line.isNull())
//            {
//                line=in.readLine();
//                qDebug()<<"in line:"<<line;
//            }
            QString skip="true";
            if(!QString::compare(skip,line))//为true,说明确定跳过按钮
            {
                qDebug()<<"Jinlaile";
                this->saveAndUpload(userRename,now_time,dir,pix,board);//保存并上传
            }
            else    // 不是true,说明关闭了随机命名
            {
                rnd = new renameDialog();
                rnd->setModal(true);
                rnd->setWindowFlags(Qt::WindowStaysOnTopHint);
                rnd->exec();
                dir=rnd->getDir();
                if(rnd->getSureChangeName())// 点击了确认按钮
                {

                    rnd->setSureChangeName(false);//重置
                    userRename =rnd->getUserRename().trimmed()+"_";// 去掉空格加上下划线
                    this->saveAndUpload(userRename,now_time,dir,pix,board);//保存并上传
                }
                else//如果用户点了×
                {
                    // 需要清空剪切板,不然会死循环
                    board->clear();
                }

            }


        }
        else // 打开文件失败,说明没有勾选过跳过重命名事件,则继续弹框重命名,第一次运行肯定会进来这里
        {
            rnd = new renameDialog();
            rnd->setModal(true);
            rnd->setWindowFlags(Qt::WindowStaysOnTopHint);
            rnd->exec();
            dir=rnd->getDir();
            if(rnd->getSureChangeName())// 点击了确认按钮
            {

                rnd->setSureChangeName(false);//重置
                userRename =rnd->getUserRename().trimmed()+"_";// 去掉空格
                this->saveAndUpload(userRename,now_time,dir,pix,board);//保存并上传
            }
            else//如果用户点了×
            {
                // 需要清空剪切板,不然会死循环
                board->clear();
            }

        }
        loadSetting.close();
     }

}

void MainWindow::saveAndUpload(QString userRename,QString now_time,QString dir,QPixmap pix,QClipboard *board)
{


    QString filename=userRename+now_time+".jpg";

     QString fileSaveDir = dir+filename;
     qDebug()<<"fileSaveDir"<<fileSaveDir;

    if(pix.save(fileSaveDir))//0:根据后缀选择图像格式,-1:小型压缩文件(100:大型未压缩文件)
    {
        qDebug()<<"保存成功了";


        pix.scaled(ui->dragLabel->size(),Qt::KeepAspectRatio);//设置pixmap缩放的尺寸
        ui->dragLabel->setScaledContents(true);//它的作用是设置label的属性scaledContents，这个属性的作用是
                                               //允许（禁止）label缩放它的内容充满整个可用的空间。
        ui->dragLabel->setPixmap(pix);
        board->clear();//设置完成清除缓冲区

        /*以下为图片上传操作*/

        char *bucket;
        char *domain;

        //const char *key = filename.toStdString().c_str();//QString转char *
        QByteArray keyQBA = filename.toLocal8Bit();//QString转char *
        char key[256];//不能用指针方式
        strcpy(key,keyQBA.data());

        const char *directories=dir.toStdString().c_str();//QString转char *
        // 由directories+key拼接而成
        char *localFile = new char[strlen(key)+strlen(directories)+1];
        strcpy(localFile,directories);
        strcat(localFile,key);


        ifstream loadAccount("account.ini",ios::in);
        if(loadAccount.is_open())
        {
            qDebug()<<"open Account.ini success";

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

            bucket=new char[strlen(bucketString.c_str())+1];
            strcpy(bucket,bucketString.c_str());

            mac.accessKey=accessKeyString.c_str();
            mac.secretKey=secretKeyString.c_str();

            domain=new char[strlen(domainString.c_str())+1];
            strcpy(domain,domainString.c_str());

             loadAccount.close();

//                     qDebug()<<"bucket:"<<bucket;
//                     qDebug()<<"accesskey:"<<mac.accessKey;
//                     qDebug()<<"secretKey:"<<mac.secretKey;
                    qDebug()<<"domain(shangchuan):"<<domain;


            Qiniu_Io_PutRet putRet;
            Qiniu_Client client;
            Qiniu_RS_PutPolicy putPolicy;
            Qiniu_Io_PutExtra putExtra;
            Qiniu_Zero(putPolicy);
            Qiniu_Zero(putExtra);
            putPolicy.scope = bucket;

            char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);

            Qiniu_Client_InitMacAuth(&client, 1024, &mac);
            Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
            if (error.code != 200)
            {
              qDebug()<<"upload file "<< bucket << ":"<<key<<" error";
              debug_log(&client, error);
              QMessageBox::about(this,"上传失败","请先检查七牛云的空间名,accessKey,secretKey的正确性");
            }
            else
            {
              /*200, 正确返回了, 你可以通过statRet变量查询一些关于这个文件的信息*/
              qDebug()<<"upload file "<<bucket<<":"<<key<<" success."<< endl;
              qDebug()<<"key:\t"<<putRet.key;// 外链地址为 domain+"/"+putRet.key
              qDebug()<<"hash:\t"<<putRet.hash;

              // 上传完成后,将链接弄进剪切板
              QClipboard *board = QApplication::clipboard();
              QString link = "![]("+QString::fromStdString(domainString)+"/"+filename+")";
              qDebug()<<"link::::"<<link;
              board->setText(link, QClipboard::Clipboard);
            }
            Qiniu_Free(uptoken);
            Qiniu_Client_Cleanup(&client);  /* 每个HTTP客户端使用完后释放 */
        }
        else
        {
             QMessageBox::about(this,"提示","请先配置好七牛云的账户信息,才能上传图片,拿到链接!");
        }
     }

}

void MainWindow::keepLoadPic()
{

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePicEvent()));
    timer->start(250);//每隔一秒
}




void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // 注意，主窗口的属性AcceptDrop要设置为True
    //如果类型是jpg或者png才能接受拖动。
    //这里的compare字符串比较函数，相等的时候返回0，所以要取反
   if(!event->mimeData()->urls()[0].fileName().right(3).compare("jpg")
           ||!event->mimeData()->urls()[0].fileName().right(3).compare("png"))
       event->acceptProposedAction();
    else
       event->ignore();//否则不接受鼠标事件
}


void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *qm=event->mimeData();//获取MIMEData
    QPixmap qp(qm->urls()[0].toLocalFile());//.toLocalFile()是获取拖动文件的本地路径。
                                            // urls()指的是拖动文件的路径列表,格式为QUrl(“file:///.....”)

    QFile dirSetting("dirSetting.ini");
    QString line="";
    if(dirSetting.open(QIODevice::ReadOnly))
    {
        QTextStream in(&dirSetting);
        line = in.readLine();
    }
    else
    {
        line="image";
    }
    QString dir = line;
    QDir qDir(dir);
    if(!qDir.exists())//文件夹不存在则创建
    {
        qDir.mkpath(dir);
    }
    dir=dir+"/";

    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int t=time.toTime_t();//转换成时间戳,需要QDateTime头文件
    QString now_time=QString::number(t);//将时间戳转换为QString
    QString tempFilename=qm->urls()[0].fileName();
    QString filename;
    // 为了避免自定义的时候,文件名同名,所以也需要加上时间
    if(tempFilename.endsWith(".jpg"))
       filename=tempFilename.replace(tempFilename.indexOf(".jpg"),4,"_"+now_time+".jpg");
    else if(tempFilename.endsWith(".png"))
       filename=tempFilename.replace(tempFilename.indexOf(".png"),4,"_"+now_time+".png");

    qDebug()<<"filename is:"+filename;

    QString fileSaveDir = dir+filename;
    qDebug()<<"fileSaveDir"<<fileSaveDir;

    if(qp.save(fileSaveDir))//0:根据后缀选择图像格式,-1:小型压缩文件(100:大型未压缩文件)
    {
        qDebug()<<"保存成功了";
        qp.scaled(ui->dragLabel->size(),Qt::KeepAspectRatio);
        ui->dragLabel->setScaledContents(true);
        ui->dragLabel->setPixmap(qp);//显示图片

        char *bucket;
        char *domain;

       // const char *key = filename.toStdString().c_str();//QString转char *
        QByteArray keyQBA = filename.toLocal8Bit();//QString转char *
        char key[256];//不能用指针方式
        strcpy(key,keyQBA.data());

        const char *directories=dir.toStdString().c_str();//QString转char *
        // 由directories+key拼接而成
        char *localFile = new char[strlen(key)+strlen(directories)+1];
        strcpy(localFile,directories);
        strcat(localFile,key);


        ifstream loadAccount("account.ini",ios::in);
        if(loadAccount.is_open())
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

            bucket=new char[strlen(bucketString.c_str())+1];
            strcpy(bucket,bucketString.c_str());

            mac.accessKey=accessKeyString.c_str();
            mac.secretKey=secretKeyString.c_str();

            domain=new char[strlen(domainString.c_str())+1];
            strcpy(domain,domainString.c_str());

            loadAccount.close();

//             qDebug()<<"bucket:"<<bucket;
//             qDebug()<<"accesskey:"<<mac.accessKey;
//             qDebug()<<"secretKey:"<<mac.secretKey;
             qDebug()<<"domain(tuodong):"<<domain;

            Qiniu_Io_PutRet putRet;
            Qiniu_Client client;
            Qiniu_RS_PutPolicy putPolicy;
            Qiniu_Io_PutExtra putExtra;
            Qiniu_Zero(putPolicy);
            Qiniu_Zero(putExtra);
            putPolicy.scope = bucket;

            char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);
            Qiniu_Use_Zone_Huadong(Qiniu_False);//使用华东机房
            Qiniu_Client_InitMacAuth(&client, 1024, &mac);
            Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
            if (error.code != 200)
            {
              qDebug()<<"upload file "<< bucket << ":"<<key<<" error";
              debug_log(&client, error);
              QMessageBox::about(this,"上传失败","请先检查七牛云的空间名,accessKey,secretKey的正确性");
            }
            else
            {
              /*200, 正确返回了, 你可以通过statRet变量查询一些关于这个文件的信息*/
              qDebug()<<"upload file "<<bucket<<":"<<key<<" success."<< endl;
              qDebug()<<"key:\t"<<putRet.key;// 外链地址为 domain+"/"+putRet.key
              qDebug()<<"hash:\t"<<putRet.hash;

              // 上传完成后,将链接弄进剪切板
              QClipboard *board = QApplication::clipboard();
              QString link = "![]("+QString::fromStdString(domainString)+"/"+filename+")";
              qDebug()<<"link::::"<<link;
              board->setText(link, QClipboard::Clipboard);
            }
            Qiniu_Free(uptoken);
            Qiniu_Client_Cleanup(&client);  /* 每个HTTP客户端使用完后释放 */
        }
        else
        {
             QMessageBox::about(this,"提示","请先配置好七牛云的账户信息,才能上传图片,拿到链接!");
        }


    }


}






void MainWindow::on_accoutAction_triggered()
{
    accountDlg = new AccountDialog(this);
    accountDlg->setModal(true);//模态

    // 显示之前先之前的账号信息,
    accountDlg->loadAccount();
    accountDlg->exec();//显示对话框
}



void MainWindow::on_globalSettingAction_triggered()
{


        gsd = new GlobalSettingDialog(this);
        gsd->setModal(true);//模态
        gsd->loadSettings();
        gsd->exec();
}

void MainWindow::on_aboutAction_triggered()
{
    QMessageBox::about(this,"关于","当前版本:0.1(内部测试版)\n版权归属:归冯文华所有(个人学习的话随便用,不可用于商业用途)\n更新地址:https://github.com/fengwenhua/HuaMarkdownPic/releases\n这是一个可以截图上传和拖动图片上传到七牛云的小工具");
}
