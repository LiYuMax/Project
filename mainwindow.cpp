#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗口
    this->setFixedSize(800,590);
    this->setWindowTitle("界面程序-李雨-2023/10/19");
    this->setWindowIcon(QIcon(":/Robot.png"));
    //定义菜单栏、工具栏、状态栏
    menuBar = new QMenuBar(this);
    toolBar  = new QToolBar(this);
    statusBar = new QStatusBar(this);
    menu = new QMenu(this);
    //添加菜单栏、工具栏、状态栏
    this->addToolBar(Qt::LeftToolBarArea,toolBar);
    toolBar->setMovable(false);
    this->setMenuBar(menuBar);
    this->setStatusBar(statusBar);
    //设置菜单栏菜单项
    QAction *fileAction = new QAction("文件",this);
    QAction *viewAction = new QAction("视图",this);
    QAction *setAction = new QAction("设置",this);
    QAction *helpAction = new QAction("帮助",this);
    QAction *newFileAction = new QAction("打开新页面",this);
    //定义工具栏菜单项
    QAction *newAction1 = new QAction(this);
    QAction *newAction2 = new QAction(this);
    QAction *newAction3 = new QAction(this);
    QAction *newAction4 = new QAction(this);
    QAction *newAction5 = new QAction(this);
    //设置工具栏菜单项图标
    newAction1->setIcon(QIcon(":/Tom.png"));
    newAction2->setIcon(QIcon(":/Jack.png"));
    newAction3->setIcon(QIcon(":/Doraemon.png"));
    newAction4->setIcon(QIcon(":/Pkaqiu.png"));
    newAction5->setIcon(QIcon(":/WeiNi.png"));
    //定义状态栏标签
    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    QLabel *label3 = new QLabel(this);
    //设置状态栏标签图标
    label1->setPixmap(QPixmap(":/China.png").scaled(30,30));
    label3->setPixmap(QPixmap(":/Time.png").scaled(30,30));
    //菜单栏添加菜单项
    menuBar->addAction(fileAction);
    menuBar->addAction(viewAction);
    menuBar->addAction(setAction);
    menuBar->addAction(helpAction);
    menu->addAction(newFileAction);
    viewAction->setMenu(menu);
    //工具栏添加菜单项
    toolBar->addAction(newAction1);
    toolBar->addAction(newAction2);
    toolBar->addAction(newAction3);
    toolBar->addAction(newAction4);
    toolBar->addAction(newAction5);
    //状态栏添加标签
    statusBar->addWidget(label1);
    statusBar->addPermanentWidget(label2);
    statusBar->addPermanentWidget(label3);
    //定义菜单栏"视图"子窗口
    newWindow = new QWidget;
    newWindow->setWindowTitle("子窗口");
    //点击工具栏菜单项触发输出打印事件
    connect(newAction1, &QAction::triggered, this,[=](){qDebug()<<"hello world1";});
    connect(newAction2, &QAction::triggered, this,[=](){qDebug()<<"hello world2";});
    connect(newAction3, &QAction::triggered, this,[=](){qDebug()<<"hello world3";});
    connect(newAction4, &QAction::triggered, this,[=](){qDebug()<<"hello world4";});
    connect(newAction5, &QAction::triggered, this,[=](){qDebug()<<"hello world5";});
    //点击"视图"打开子窗口
    connect(newFileAction, &QAction::triggered, this, [=]()
    {
       newWindow->show();
    });
    //设置状态栏显示当前时间标签
    myTimer = new QTimer(this);;
    myTimer->setInterval(1000);
    QString beginStr = QTime::currentTime().toString();
    label2->setText("当前时间:"+beginStr);
    connect(myTimer, &QTimer::timeout, this, [=]()
    {
       QString str = QTime::currentTime().toString();
       label2->setText("当前时间:"+str);
    });
    myTimer->start();
    //设置8行5列表格
    itemModel = new QStandardItemModel(8,5,this);
    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 5; ++column) {
            QStandardItem *item = new QStandardItem(QString("Row %1, Col %2").arg(row + 1).arg(column + 1));
            itemModel->setItem(row, column, item);
       }
    }
    reverseFlag = false;
    tableView = new QTableView(this);
    tableView->setFixedSize(405,280);
    tableView->move(35,22);
    tableView->setModel(itemModel);
    reverseButton = new QPushButton(this);
    reverseButton->setText("倒序");
    reverseButton->setFixedSize(408,30);
    reverseButton->move(33,300);
    //设置表格倒序按钮
    connect(reverseButton, &QPushButton::clicked, this,[=]()
    {
       if(false == reverseFlag){
              itemModel->sort(0,Qt::DescendingOrder);
              reverseFlag = true;
       }else if(true == reverseFlag)
       {
              itemModel->sort(0,Qt::AscendingOrder);
              reverseFlag = false;
       }
     });
    //使用model/view结构设置8行5列数形图
    treeItemModel = new QStandardItemModel(this);
    treeItemModel->setColumnCount(1);
    treeView = new QTreeView(this);
    treeView->setFixedSize(180,280);
    treeView->move(440,22);
    treeView->setHeaderHidden(false);
    QString headerText = QString("树形表");
    QStandardItem* headerItem = new QStandardItem(headerText);
    treeItemModel->setHorizontalHeaderItem(0,headerItem);
    QRandomGenerator myGenerator;
    QStandardItem *rootItem = treeItemModel->invisibleRootItem();
    for(int i = 0; i <8 ; i++)
    {
       QStandardItem *item = new QStandardItem(QString("Title %1").arg(i));
       rootItem->appendRow(item);
       for(int j =0 ; j<5; j++)
       {
              int randomNum = myGenerator.bounded(50);
              item->appendRow(new QStandardItem(QString::number(randomNum)));
       }
    }
    treeView->setModel(treeItemModel);
    //实现点击按钮使得树形图内小于等于25的数全部变为0
    QPushButton *btn1 = new QPushButton(this);
    btn1->setText("操作一");
    btn1->setFixedSize(93,30);
    btn1->move(438,300);
    connect(btn1, &QPushButton::clicked, this,[&]()
    {
       for(int i = 0; i < treeItemModel->rowCount(); i++)
       {
             for(int j = 0; j < treeItemModel->item(i)->rowCount(); j++)
             {
                     if(treeItemModel->item(i)->child(j)->text().toInt() <= 25)
                     {
                            treeItemModel->item(i)->child(j)->setText("0");
                     }
              }
       }
    }) ;
    //实现点击按钮过滤单数行号，保留单数行号内容，删除其他行
    QPushButton *btn2 = new QPushButton(this);
    btn2->setText("操作二");
    btn2->setFixedSize(93,30);
    btn2->move(528,300);
    connect(btn2, &QPushButton::clicked, this,[&]()
     {
              QVector<int> deleteVector;
                     for(int i = 0; i < treeItemModel->rowCount(); i++)
                     {
                            for(int j = 0; j < treeItemModel->item(i)->rowCount(); j++)
                            {
                                   if(j > 0 && j%2 == 1)
                                   {
                                          deleteVector.push_back(j);
                                   }
                            }
                            for(auto it = deleteVector.rbegin(); it != deleteVector.rend(); ++it)
                            {
                                   int row = *it;
                                   treeItemModel->item(i)->removeRow(row);
                            }
                            deleteVector.clear();
              }
            }) ;
    //实现绘图图片
    MyWidget *myWidget = new MyWidget(this);
    myWidget->setFixedSize(765,200);
    myWidget->move(35,330);
    //实现点击按钮，每隔500ms使用Tcp向本机发送字符串，并在文本显示区显示
    localServer = new QTcpServer(this);
    localServer->listen(QHostAddress::Any,8888);
    localServer->isListening();
    connect(localServer,&QTcpServer::newConnection,this,[=]()
    {
        QTcpSocket *newSocket = localServer->nextPendingConnection();
        connect(newSocket,&QTcpSocket::readyRead,this,[=]()
        {
            QByteArray data = newSocket->readAll();
            textEdit->append(data);
        });
    });
    textEdit = new QTextEdit(this);
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(QString("127.0.0.1")),8888);
    QTimer *timer = new QTimer(this);
    timer->setInterval(500);
    textEdit->setFixedSize(180,280);
    textEdit->move(620,22);
    QPushButton *sendBtn = new QPushButton(this);
    sendBtn->setText("Tcp信息发送");
    sendBtn->move(619,300);
    sendBtn->setFixedSize(182,30);
    msg = "Hello world";
    connect(sendBtn, &QPushButton::clicked, this, [=]()
    {
        timer->start();
    });
    connect(timer,&QTimer::timeout,this,&MainWindow::sendMsg);
    //实现点击按钮弹出文件路径界面，选择后在该路径下创建"hello.txt"文件，并每隔500ms
    //向文件中写入“你好，”文件“”，写入100次后停止
    QPushButton *fileBtn = new QPushButton(this);
    fileBtn->setText("写文件");
    fileBtn->move(34,530);
    connect(fileBtn,&QPushButton::clicked, this,[=]()
    {
        QString dirPath = QFileDialog::getExistingDirectory();
        if(true==dirPath.isEmpty())
        {
            QMessageBox::information(nullptr,"提示","路径名不能为空");
            return;
        }
        QString filePath = dirPath + "/hello.txt";
        writeThread = new FileWriteThread;
        connect(writeThread,&FileWriteThread::writeOver,this,[=](){
            writeThread->deleteLater();
        });
        connect(this,&MainWindow::sendPath,writeThread,&FileWriteThread::recvPath );
        emit sendPath(filePath);
        writeThread->start();
    });
    //实现数据库功能要求
    //设置操作数据库的3个按钮
    QPushButton *dataBtn1 = new QPushButton(this);
    dataBtn1->setText("数据库1");
    dataBtn1->move(510,530);
    QPushButton *dataBtn2 = new QPushButton(this);
    dataBtn2->setText("数据库2");
    dataBtn2->move(605,530);
    dataBtn2->setEnabled(false);
    QPushButton *dataBtn3 = new QPushButton(this);
    dataBtn3->setText("数据库3");
    dataBtn3->move(700,530);
    dataBtn3->setEnabled(false);
    connect(this,&MainWindow::sendDataBase,&dataThread,&InsertDataTherad::recvDataBase);
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("dataBase.db");
    emit sendDataBase(&dataBase);
    dataBase.open();
    QSqlQuery query;
    query.exec("DROP TABLE Student");
    //实现创建数据库并按要求插入数据
    connect(dataBtn1,&QPushButton::clicked,this, [=]()
    {
        createTable();
        insertData();
        dataBtn1->setEnabled(false);
        dataBtn2->setEnabled(true);
    } );
    //实现点击按钮将数据库表内容按照“随机数2”列内容从大到小排序
    connect(dataBtn2, &QPushButton::clicked, this, [=](){
    QSqlQuery query;
    if(false == query.exec(" SELECT * FROM Student ORDER BY score DESC;"))
    {
       return;
    }
    query.finish();
    QMessageBox::information(nullptr,"提示","排序完成");
    dataBtn3->setEnabled(true);
    });
    //实现点击第3个按钮打印数据库中“随机数3”这一列数字为奇数的行内容，删除
    //为偶数的那一行
    connect(dataBtn3,&QPushButton::clicked,this,[=]()
    {
        QSqlQuery query;
        query.exec("SELECT * FROM Student WHERE student % 2 = 1");
        while (query.next()) {
            int id = query.value("id").toInt();
            int random1 = query.value("name").toInt();
            int random2 = query.value("score").toInt();
            int random3 = query.value("student").toInt();
            qDebug()<< QString("id: %1 name: %2 score: %3 student: %4").arg(id).arg(random1).arg(random2).arg(random3);
        }
        query.exec("DELETE FROM Student WHERE student % 2 = 0");
        QMessageBox::information(nullptr,"提示","打印删除完成");
    });
}

MainWindow::~MainWindow()
{
    newWindow->deleteLater();
}
//创建数据库表函数实现
void MainWindow::createTable()
{
    QSqlQuery query;
    if(false == query.exec("CREATE TABLE Student (id INTEGER PRIMARY KEY AUTOINCREMENT"
                                        " DEFAULT 0, name INTEGER, score INTEGER, student INTEGER)"))
    {
       return;
    }
    query.finish();
}
//插入数据函数实现
void MainWindow::insertData()
{
     QMessageBox::information(nullptr,"提示","导入数据时，请耐心等待数据库2按钮就绪，不要进行其他操作");

     dataThread.start();
    //     QSqlQuery query;
//     for (int i = 0; i < 1000; i++) {
//        int num1 = QRandomGenerator::global()->bounded(1, 3000);
//        int num2 = QRandomGenerator::global()->bounded(1, 3000);
//        int num3 = QRandomGenerator::global()->bounded(1, 3000);
//        query.prepare("INSERT INTO Student(name, score, student) VALUES (?, ?, ?)");
//        query.addBindValue(num1);
//        query.addBindValue(num2);
//        query.addBindValue(num3);
//        if (!query.exec()) {
//            qDebug() << query.lastError().text();
//            return;
//        }
//    }
     QMessageBox::information(nullptr,"提示","数据导入完成");
}
//Tcp发送数据函数实现
void MainWindow::sendMsg()
{
    socket->write(msg.toUtf8());
}

