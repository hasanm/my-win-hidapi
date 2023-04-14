#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "mainwindow.h"

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
  topLayout->addWidget(quitButton);


  /* Content Layout */
  contentLayout = new QVBoxLayout(content);


  /* root Layout */
  rootLayout = new QVBoxLayout(root);
  rootLayout->addWidget(top);
  rootLayout->addWidget(content);

  setCentralWidget(root);
}
