#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_OpenFile_clicked();

private:  //sami!!
  //  QString sort(QString qsInput);
  //  bool writeToFile(QString qsWord);
    QString readFromFile(QString fileName);
    void process_line(QString input);
    void analiseString(QString input);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
