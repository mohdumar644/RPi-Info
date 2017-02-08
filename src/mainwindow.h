#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
 #include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void sysinfo();
    void initmodel();
    QString getmodel(QString rev);
    QMap <QString,QString> modeldb;

private slots:
    int update();
    void about();
};

#endif // MAINWINDOW_H
