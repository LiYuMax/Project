#ifndef FILEWRITETHREAD_H
#define FILEWRITETHREAD_H
#include <QObject>
#include <qthread>
#include <QTimer>
#include <QDebug>
#include <QFile>
class FileWriteThread : public QThread
{
    Q_OBJECT
public:
    explicit FileWriteThread(QObject *parent = nullptr);
    void run()override;
public slots:
    void recvPath(QString &filePath);
    void write();
signals:
    void begin();
    void writeOver();
private:
    QString Path;
    QTimer myTimer;
    QFile myFile;
    int writeTimes;
};

#endif // FILEWRITETHREAD_H
