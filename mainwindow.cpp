#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "mainwindow.h"


#include <windows.h>
#include <hidapi.h>

MainWindow::~MainWindow(){
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{

  root = new QWidget(this);
  top  = new QWidget(this);
  content = new QWidget(this);

  /* Top Layout */
  topLayout = new QHBoxLayout(top);
  quitButton = new QPushButton(QString("Quit"));
  connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);


  pushButton = new QPushButton(QString("Push"));
  connect(pushButton, &QPushButton::clicked, this, &MainWindow::onPush); 
  
  topLayout->addWidget(quitButton);
  topLayout->addWidget(pushButton);


  /* Content Layout */
  contentLayout = new QVBoxLayout(content);
  textArea = new QTextEdit(this);
  textArea->setText(QString("Hello World!"));
  textArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // scrollArea = new QScrollArea(this);
  // scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // scrollArea->setWidget(textArea);

  contentLayout->addWidget(textArea);


  /* root Layout */
  rootLayout = new QVBoxLayout(root);
  rootLayout->addWidget(top);
  rootLayout->addWidget(content);

  setCentralWidget(root);
}


void MainWindow::onPush()
{
  QString output{"Enumeration Begins\n"};
  textArea->setText(output);
  hid_device *handle;
  struct hid_device_info *devs;

  if (hid_init()) {
    return;
  }
  devs = hid_enumerate(0x0, 0x0);
  int i = 0; 
  while(devs){
    i++;
    output.append(QString("%1 %2 %3 %4 %5\n").arg(i).arg(devs->vendor_id).arg(devs->product_id).arg(devs->path).arg(devs->serial_number));
    devs = devs->next; 
  }
  hid_free_enumeration(devs);
  textArea->setText(output);
}
