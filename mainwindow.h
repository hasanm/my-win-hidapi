#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qt_windows.h>
#include <QMainWindow>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void onPush();

private:

  QWidget *root;
  QWidget *top;
  QWidget *content;

  QHBoxLayout *topLayout;
  QVBoxLayout *contentLayout;
  QVBoxLayout *rootLayout;

  QPushButton *quitButton;
  QPushButton *pushButton;

  QScrollArea *scrollArea; 
  QTextEdit *textArea; 
};

#endif // MAINWINDOW_H
