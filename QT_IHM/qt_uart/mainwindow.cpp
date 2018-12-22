// JALLOULI ; JOUANNIC

#include "mainwindow.h"
#include "ui_mainwindow.h"

QString nameport = "/dev/ttyUSB0";

//=================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);         // Définition d'une Fenêtre
                                               // Nécessaire avec mainwindow

    buton_up = new QPushButton("UP");
    buton_down = new QPushButton("DOWN");
    buton_left = new QPushButton("LEFT");
    buton_right = new QPushButton("RIGHT");
    buton_stop = new QPushButton("STOP");

    accelerate = new QPushButton("Accelerate ");
    decelerate = new QPushButton("Decelerate");
    m_layout = new QGridLayout();

    m_layout->addWidget(buton_up,1,1);
    m_layout->addWidget(buton_down,3,1);
    m_layout->addWidget(buton_left,2,0);
    m_layout->addWidget(buton_right,2,2);
    m_layout->addWidget(buton_stop,1,3);

    m_layout->addWidget(accelerate,2,3);
    m_layout->addWidget(decelerate,3,3);

    zoneCentrale->setLayout(m_layout);

   /* QLabel *label_to_send = new QLabel;
    label_to_send->setText("Message à Envoyer");
    QLabel *label_received = new QLabel;
    label_received->setText("Message reçu");
*/


   /* but_send = new QPushButton("Send Message");  // NB : on ne précise pas le parent
    mes_to_send = new QLineEdit();
    mes_received = new QLineEdit();

    m_layout = new QVBoxLayout();

    m_layout->addWidget(label_to_send);
    m_layout->addWidget(mes_to_send);
    m_layout->addWidget(but_send);
        m_layout->addWidget(label_received);
    m_layout->addWidget(mes_received);

    zoneCentrale->setLayout(m_layout);
*/
    openSerialPort();
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(buton_up,SIGNAL(clicked()),this,SLOT(onButUpSendClicked()));
    connect(buton_down,SIGNAL(clicked()),this,SLOT(onButDownSendClicked()));
    connect(buton_right,SIGNAL(clicked()),this,SLOT(onButRightSendClicked()));
    connect(buton_left,SIGNAL(clicked()),this,SLOT(onButLeftSendClicked()));
    connect(buton_stop,SIGNAL(clicked()),this,SLOT(onButStopSendClicked()));

    connect(accelerate,SIGNAL(clicked()),this,SLOT(onButAccSendClicked()));
    connect(decelerate,SIGNAL(clicked()),this,SLOT(onButDecSendClicked()));

   // ui->setupUi(this);
}
//=================================================================================
MainWindow::~MainWindow()
{
    delete ui;
}
//=================================================================================
void MainWindow::openSerialPort()
{
    serial = new QSerialPort(this);
    serial->setPortName(nameport);
    serial->open(QIODevice::ReadWrite);

     if( serial->isOpen()==false)
     {
          serial->clearError();
          QMessageBox::critical(this, "Port error", "Port: "+nameport);
          QMessageBox::information(this, "Port error", "Vérifier nom du port \n Fermer tout programme utilisant la lisaison RS232 "+nameport);
      }
   else
     {
         QMessageBox::information(this, "Port open", " "+nameport);
          serial->setBaudRate(QSerialPort::Baud9600);
          serial->setStopBits(QSerialPort::OneStop);
          serial->setParity(QSerialPort::NoParity);
          serial->setDataBits(QSerialPort::Data8);
          serial->setFlowControl(QSerialPort::NoFlowControl);
     }
}

//====================================================
/*
void MainWindow::onButSendClicked()
{
    QString message=mes_to_send->text();
    writeData(message.toUtf8()); // QString --> QByteArray
}
*/
//====================================================

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
//====================================================
void MainWindow::readData()
{
    QByteArray data = serial->readAll();
   // mes_received->setText(data);
}
//====================================================
void MainWindow::onButUpSendClicked(){
    //QString message=mes_to_send->text();
    QString message="1" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}

void MainWindow::onButDownSendClicked(){
    //QString message=mes_to_send->text();
     QString message="2" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}

void MainWindow::onButRightSendClicked(){
    //QString message=mes_to_send->text();
     QString message="4" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}

void MainWindow::onButLeftSendClicked(){
    //QString message=mes_to_send->text();
     QString message="3" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}

void MainWindow::onButStopSendClicked(){
    //QString message=mes_to_send->text();
     QString message="5" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}


void MainWindow::onButAccSendClicked(){
    //QString message=mes_to_send->text();
     QString message="6" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}

void MainWindow::onButDecSendClicked(){
    //QString message=mes_to_send->text();
     QString message="7" ;
    writeData(message.toUtf8()); // QString --> QByteArray
}
