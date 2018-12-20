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
 //    qsTemp="1629936492_0_v1_1545203239277.csv";
     qsResult=readFromFile(qsTemp);
     ui->textBrowser_Output->append(qsResult+"\n");
}

QString MainWindow::readFromFile(QString fileName)
{
     QStringList qslTemp,qslNulldata, qslMaxSun;
     QString qsStartLine="0.0,0,0,0" ;
      char buf[1024];
          int Counter = 0;
     QFile inputFile(fileName);   //открыли файл
     if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
         return "";
     }
     qslMaxSun=qsStartLine.split(',');
     qslNulldata=qsStartLine.split(',');
   while(!inputFile.atEnd()){
     inputFile.readLine(buf,1024);
     Counter++;
     QString qsOneLine(buf);
     qsOneLine=qsOneLine.trimmed();  // удаляем лишнее из строки
//     qDebug()<< "read- "<< fileName << ",line ="<< qsOneLine<< ", # - "<< Counter;

     qslTemp=process_line(qsOneLine);// в формате lux,data,0,day
     if (qslTemp[3].toInt()==qslNulldata[3].toInt()){ //если сегодня, то суммируем lux
         int DayCounter = qslNulldata[2].toInt();
         DayCounter++;
         QString qsDay = QString::number(DayCounter);
         qslNulldata[2]= qsDay;
         double dTmp = qslNulldata.at(0).toDouble()+qslTemp.at(0).toDouble();//lux+lux
         QString qsTemp = QString::number(dTmp,'f',6);// back to QString
         qslNulldata[0]=qsTemp; //lux=summ lux in QString
         qslNulldata[1]=qslTemp[1];
        } else {
        if (qslNulldata[3].toInt()!=0){
            double dMedLux = qslNulldata.at(0).toDouble()/qslNulldata.at(2).toInt() ;
            QString qsLuxToStr =QString::number(dMedLux,'f',6);
         ui->textBrowser_Output->append(qslNulldata[1]+", средная освещенность дня: "
                 +qsLuxToStr+" lux");
       }
         qslNulldata= qslTemp;
  }
     qslMaxSun= CompareString(qslNulldata, qslMaxSun); // сравниваем по lux, выбираем max
     double dMedLux = qslMaxSun.at(0).toDouble()/qslMaxSun.at(2).toInt() ;
     QString qsLuxToStr =QString::number(dMedLux,'f',6);
     qsStartLine="Самый светлый день был в "+qslMaxSun[1]+" и достиг среднего значения: "+qsLuxToStr+" lux \n";
   }
     return qsStartLine; // сюда qslMaxSun в формате QString
}

QStringList MainWindow::process_line(QString input)
{
    int day;
    QStringList qsl = input.split(',');
    if(qsl.size()==3){
        double lux = qsl.at(0).toDouble();

        QString qsTemp = QString::number(lux,'f',6);
        qsl[0]=qsTemp; //   в qsl[0] строка = lux

        qint64 unixTimeMilSec = static_cast<qint64>(qsl.at(1).toLongLong()); //unixTimeMilSec = INT !!!!!!
        QDateTime dt =QDateTime::fromMSecsSinceEpoch(unixTimeMilSec);
        qsTemp = dt.toString();
        qsTemp.remove(10,8);
        qsl[1]=qsTemp; //    в qsl[1] строка = дата типа " Пн дек 10 01:53:00 2018"
        day = dt.date().day(); //day !!  = 10
        qsl.append(QString::number(day));
     }
    return qsl;
}

QStringList MainWindow::CompareString(QStringList inputA, QStringList inputB)
{
    QStringList qslResult;
    if (inputA.at(0).toDouble() >= inputB.at(0).toDouble()){
        qslResult=inputA;
    } else { qslResult=inputB; }
     return qslResult;
}



