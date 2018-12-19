#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtAlgorithms>
#include <QDateTime>
#include <QDate>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_OpenFile_clicked()
{
     QString qsResult;
     QString qsTemp =ui->lineEdit_OpenFile->text();
     qsTemp="1629936492_0_v1_1545203239277.csv";
     qsResult=readFromFile(qsTemp);




}

QString MainWindow::readFromFile(QString fileName)
{
  //   qDebug()<< "ReadF from -  "<< fileName;
      char buf[1024];
          int Counter = 0;
     QFile inputFile(fileName);   //открыли файл
     if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
         return "";
     }
  //   if ()
//      qDebug()<< "buf is -  "<< buf;
   while(!inputFile.atEnd()){
     inputFile.readLine(buf,1024);
     Counter++;
     QString qsOneLine(buf);
     qsOneLine=qsOneLine.trimmed();  // удаляем лишнее из строки
     qDebug()<< "read from "<< fileName << " one line is:"<< qsOneLine;

     //Сюда проверку!!

     ui->textBrowser_Output->setText(qsOneLine);

     process_line(qsOneLine);
     analiseString(qsOneLine);
     //qsOneLine=Counter.toString();
      //ui->textBrowser_Output->append(qsOneLine);
     // qDebug() << Counter;
 //    ui->pushButton_Sort->click();  textBrowser_Output

      }
     return "";


}

void MainWindow::process_line(QString input)
{
    QStringList qsl = input.split(',');
    if(qsl.size()==3){
        double lux = qsl.at(0).toDouble();

        QString qsTemp = QString::number(lux,'f',6);
        qsl[0]=qsTemp;

        //qDebug() << "QSL at 1 :" << qsl.at(1);
        qint64 unixTimeMilSec = static_cast<qint64>(qsl.at(1).toLongLong()); //unixTimeMilSec = INT !!!!!!
        //qint64 unixTimeSec = (unixTimeMilSec/ static_cast<qint64>(1000));
        QDateTime dt =QDateTime::fromMSecsSinceEpoch(unixTimeMilSec);
        qsTemp = dt.toString();
        //qDebug() << "Lux :" << lux << "unixTimeSec" << unixTimeSec << "dt: " << qsTemp << "Current hour: " << dt.time().hour();
        qsl.append(qsTemp);
        for (int i = 0; i < qsl.size(); ++i) {
            //qDebug() << "QSL at "<<i << " : "<< qsl.at(i);
        }
        QString outStr = qsl.join(';');
        outStr.append("\n");
        ui->textBrowser_Output->append("Data is: ");
        ui->textBrowser_Output->append(outStr);

    }
}

void MainWindow::analiseString(QString input)
{
    QString  qsTemp;
    QString qsData;
    double dLuxCounter =0;

     QStringList qsl = input.split(',');
    if(qsl.size()==3){
        double lux = qsl.at(0).toDouble(); //v luxah
        qint64 unixTimeMilSec = static_cast<qint64>(qsl.at(1).toLongLong());
        QDateTime dt = QDateTime::fromMSecsSinceEpoch(unixTimeMilSec); //
        qsTemp = dt.toString();
        dLuxCounter=dLuxCounter+lux ;

       qsData = qsTemp.at(7);
       qsData.append(qsTemp.at(8));
          qDebug() << "Lux :" << lux << "unixTimeSec" << unixTimeMilSec << "dt: "<< qsTemp << dt.time().hour()  << "Day is:"<<qsData;
        ui->textBrowser_Output->append("Lux = "+QString::number(dLuxCounter));






 //       QDate date =   "Current hour: "
 //   cur_date = qsl[1].date();   7/8
 //   qDebug() << "date - " << cur_date;
    }


}


