#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#include <QIcon>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QTreeView>
#include <QRandomGenerator>
#include <QHeaderView>
#include "mywidget.h"
#include <QTextEdit>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFileDialog>
#include <QFile>
#include "filewritethread.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSql>
#include <QSqlError>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <insertdatatherad.h>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTable();
    void insertData();
public slots:
    void sendMsg();

signals:
    void sendPath(QString &path);
    void sendDataBase(QSqlDatabase *database);
private:
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QMenu *menu;
    QWidget *newWindow;
    QTimer *myTimer;
    QTableView *tableView;
    QStandardItemModel *itemModel;
    QPushButton *reverseButton;
    QTreeView *treeView;
    QStandardItemModel *treeItemModel;
    bool reverseFlag;
    QTextEdit *textEdit;
    QTcpSocket *socket;
    QTcpServer *localServer;
    QString msg;
    FileWriteThread *writeThread;
    InsertDataTherad dataThread;
};
#endif // MAINWINDOW_H
