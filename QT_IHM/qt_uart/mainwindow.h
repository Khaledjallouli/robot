#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:


  void openSerialPort();
  void writeData(const QByteArray &);
  void readData();
  void onButUpSendClicked();
  void onButDownSendClicked();
  void onButLeftSendClicked();
  void onButRightSendClicked();
  void onButStopSendClicked();
  void onButAccSendClicked();
  void onButDecSendClicked();

private:

  QSerialPort *serial;
  Ui::MainWindow *ui;

  QGridLayout *m_layout;
  QPushButton *buton_up,*buton_down, * buton_left, *buton_right, *buton_stop,*accelerate, *decelerate;





};

#endif // MAINWINDOW_H
