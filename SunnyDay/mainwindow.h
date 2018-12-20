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

    QString readFromFile(QString fileName);
    QStringList process_line(QString input);
    QStringList CompareString(QStringList inputA, QStringList inputB );


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
