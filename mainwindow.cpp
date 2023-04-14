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

// Vendor_ID Product_ID Usage USAGE_PAGE

// KBD75v2
// 0x4B42 0x6061
// 19266 24673 6 1

void MainWindow::onPush()
{
  hid_device *handle;
  struct hid_device_info *devs;
  unsigned char buf[256];
  int res;




  QString output{"Enumeration Begins\n"};
  textArea->setText(output);

  if (hid_init()) {
    return;
  }
  devs = hid_enumerate(0x0, 0x0);
  int i = 0;
  while(devs){
    i++;
    output.append(QString("%1 %2 %3 %4 %5 %6\n").arg(i).arg(devs->vendor_id).arg(devs->product_id).arg(devs->usage).arg(devs->usage_page).arg(devs->serial_number));
    devs = devs->next;
  }
  hid_free_enumeration(devs);
  handle = hid_open(0x4B42, 0x6061, NULL);
  textArea->setText(output);

  if(!handle) {
    hid_exit();
  } else {
    memset(buf, 0x00, sizeof(buf));
    buf[0] = 0x01;
    buf[1] = 0x80;

    int res = hid_write(handle, buf, 17);

    if (res < 0) {
      output.append(QString("%1\n").arg(hid_error(handle)));
    }

    hid_close(handle);
    hid_exit();
  }

  textArea->setText(output);

}
