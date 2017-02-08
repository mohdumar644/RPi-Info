#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include "QMessageBox"
#include "QProcess"
#include "QDesktopWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1200);


    connect(ui->menuAbout, SIGNAL(aboutToShow()), this, SLOT(about()));

    initmodel();
    sysinfo();

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initmodel()
{
    modeldb.insert("Beta","BBeta BoardQ1 2012 ");
    modeldb.insert("0002","B Q1 2012 ");
    modeldb.insert("0003","B (ECN0001) (Fuses mod and D14 removed) Q3 2012 ");
    modeldb.insert("0004","B (Mfg by Sony) Q3 2012 ");
    modeldb.insert("0005","B (Mfg by Qisda) Q4 2012 ");
    modeldb.insert("0006","B (Mfg by Egoman) Q4 2012 ");
    modeldb.insert("0007","A (Mfg by Egoman) Q1 2013 ");
    modeldb.insert("0008","A (Mfg by Sony) Q1 2013 ");
    modeldb.insert("0009","A (Mfg by Qisda) Q1 2013 ");
    modeldb.insert("000d","B (Mfg by Egoman) Q4 2012 ");
    modeldb.insert("000e","B (Mfg by Sony) Q4 2012 ");
    modeldb.insert("000f","B (Mfg by Qisda) Q4 2012 ");
    modeldb.insert("0010","B+ (Mfg by Sony) Q3 2014 ");
    modeldb.insert("0011","Compute Module 1 (Mfg by Sony) Q2 2014 ");
    modeldb.insert("0012","A+ (Mfg by Sony) Q4 2014 ");
    modeldb.insert("0013","B+  Q1 2015 ");
    modeldb.insert("0014","Compute Module 1 (Mfg by Embest) Q2 2014 ");
    modeldb.insert("0015","A+ (Mfg by Embest) Unknown ");
    modeldb.insert("a01040","2 Model B (Mfg by Sony) Unknown Date ");
    modeldb.insert("a01041","2 Model B (Mfg by Sony) Q1 2015 ");
    modeldb.insert("a21041","2 Model B (Mfg by Embest) Q1 2015 ");
    modeldb.insert("a22042","2 Model B (with BCM2837) (Mfg by Embest) Q3 2016 ");
    modeldb.insert("900021","A+ (Mfg by Sony) Q3 2016 ");
    modeldb.insert("900092","Zero (Mfg by Sony) Q4 2015 ");
    modeldb.insert("900093","Zero (Mfg by Sony) Q2 2016 ");
    modeldb.insert("920093","Zero (Mfg by Embest) Q4 2016? ");
    modeldb.insert("a02082","3 Model B (Mfg by Sony) Q1 2016 ");
    modeldb.insert("a020a0","Compute Module 3 (and CM3 Lite) (Mfg by Sony) Q1 2017 ");
    modeldb.insert("a22082","3 Model B (Mfg by Embest) Q1 2016 ");
    modeldb.insert("a32082","3 Model B (Mfg by Sony Japan) Q4 2016 ");
}

QString MainWindow::getmodel(QString rev)
{
    QString model = "UNKNOWN";
    QMapIterator<QString, QString> i(modeldb);
    while (i.hasNext()) {
        i.next();
        if (rev.indexOf(i.key())!=-1)
        {
            model = i.value();
            break;
        }
        //qDebug(QString(rev+"  "+i.key() + ": "+ i.value() ).toStdString().c_str());
    }
    //qDebug(model.toStdString().c_str());
    return model;
}

void MainWindow::about()
{
    QMessageBox::information(this,"About Me","RPi_Info v1.0\nInitial Release\n\n(C) 2017, mohdumar");
}

void MainWindow::sysinfo()
{
    QProcess qproc;
    qproc.start("uname -mrs");
    if (!qproc.waitForFinished())
        return;
    QByteArray result = qproc.readAll();
    QString res = QString::fromStdString(result.toStdString());
    ui->lineEdit_6->setText(res);


    qproc.start("lsb_release -a");
    if (!qproc.waitForFinished())
        return ;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString());
    int idx = res.indexOf("Description:")+13;
    res = res.mid(idx,res.indexOf("\n",idx)-idx);
    ui->lineEdit_5->setText(res);



    qproc.start("vcgencmd get_mem arm");
    if (!qproc.waitForFinished())
        return ;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString());
    idx = res.indexOf("=");
    res = res.mid(idx+1);
    ui->lineEdit_3->setText(res);

    qproc.start("vcgencmd get_mem gpu");
    if (!qproc.waitForFinished())
        return ;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString());
    idx = res.indexOf("=");
    res = res.mid(idx+1);
    ui->lineEdit_4->setText(res);




    //
    qproc.start("lscpu");
    if (!qproc.waitForFinished())
        return ;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString());
    idx = res.indexOf("Model name:")+12;
    int idx2 = res.indexOf("CPU(s):")+8;
    QString cpu = res.mid(idx+1,res.indexOf("\n",idx)-idx).trimmed() + QString("  [") + res.mid(idx2+1,res.indexOf("\n",idx2)-idx2).trimmed()+ QString(" CPUs]");
    ui->lineEdit_2->setText(cpu);



    qproc.start("cat /proc/cpuinfo");
    if (!qproc.waitForFinished())
        return ;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString());
    idx = res.indexOf("Revision");
    idx = res.indexOf(":",idx);
    QString hw = res.mid(idx+1,res.indexOf("\n",idx)-idx).trimmed();
    ui->lineEdit->setText(getmodel(hw));

}

int MainWindow::update()
{
    QProcess qproc;
    qproc.start("cat /sys/class/thermal/thermal_zone0/temp");
    if (!qproc.waitForFinished())
        return false;
    QByteArray result = qproc.readAll();
    QString res = QString::number(QString::fromStdString(result.toStdString()).toDouble()/1000).left(4);
    ui->lcdNumber->display(res);



    qproc.start("/opt/vc/bin/vcgencmd measure_temp");
    if (!qproc.waitForFinished())
        return false;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString()).mid(5,4);
    ui->lcdNumber_2->display(res);



    qproc.start("/opt/vc/bin/vcgencmd measure_volts");
    if (!qproc.waitForFinished())
        return false;
    result = qproc.readAll();
    res=QString::fromStdString(result.toStdString()).mid(5,4);
    ui->lcdNumber_3->display(res);


    qproc.start("cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
    if (!qproc.waitForFinished())
        return false;
    result = qproc.readAll();
    res = QString::number(QString::fromStdString(result.toStdString()).toDouble()/1000).left(4);
    ui->lcdNumber_4->display(res);

}
