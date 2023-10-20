#include "insertdatatherad.h"

InsertDataTherad::InsertDataTherad(QObject *parent)
    : QThread{parent}
{

}

void InsertDataTherad::run()
{
    qDebug()<<"我是子线程";
   // MydataBase->open();
    qDebug()<<"dd";
         QSqlQuery query;
         for (int i = 0; i < 1000; i++) {
            int num1 = QRandomGenerator::global()->bounded(1, 3000);
            int num2 = QRandomGenerator::global()->bounded(1, 3000);
            int num3 = QRandomGenerator::global()->bounded(1, 3000);
            query.prepare("INSERT INTO Student(name, score, student) VALUES (?, ?, ?)");
            query.addBindValue(num1);
            query.addBindValue(num2);
            query.addBindValue(num3);
            if (!query.exec()) {
                return;
            }
         }
}

void InsertDataTherad::recvDataBase(QSqlDatabase *dataBase)
{
         qDebug()<<"收到了";
         qDebug()<<dataBase;
         MydataBase = dataBase;
}
