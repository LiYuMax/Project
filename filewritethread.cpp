#include "filewritethread.h"

FileWriteThread::FileWriteThread(QObject *parent)
    : QThread{parent}
{
    writeTimes = 0;
    myTimer.setInterval(500);
    connect(&myTimer,&QTimer::timeout,this,&FileWriteThread::write);
    connect(this,&FileWriteThread::begin,this,[=]()
     {
            myTimer.start();
    });
}
void FileWriteThread::run()
{
    emit begin();
}
//接收文件路径和文件名
void FileWriteThread::recvPath(QString &filePath)
{
    Path = filePath;
    myFile.setFileName(Path);
    myFile.open(QIODevice::Append);
}
//向文件中写入指定内容
void FileWriteThread::write()
{
    myFile.write(QString("你好,\"文件\"").toUtf8());
    writeTimes++;
    if(writeTimes == 3)
    {
        myTimer.stop();
        myFile.close();
        emit writeOver();
    }
}
