#ifndef INSERTDATATHERAD_H
#define INSERTDATATHERAD_H

#include <QObject>
#include <QThread>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QRandomGenerator>
class InsertDataTherad : public QThread
{
    Q_OBJECT
public:
    explicit InsertDataTherad(QObject *parent = nullptr);

    void run()override;
signals:

public slots:
    void recvDataBase(QSqlDatabase *dataBase);
public:
    QSqlDatabase *MydataBase;
};

#endif // INSERTDATATHERAD_H
