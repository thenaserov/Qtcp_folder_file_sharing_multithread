/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/
#include <QFile>
#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(int port, QObject *parent):
  QObject(parent), _port(port)
{
  server = new QTcpServer(this);
  connect(server, &QTcpServer::newConnection,
          this, &MyTcpServer::newConnection);

  if (!server->listen(QHostAddress::LocalHost, port))
  {
    qDebug() << "Server could not start";
  }
  else
  {
    qDebug() << "Server started!";
  }
}

void  MyTcpServer::newConnection()
{
  QTcpSocket *socket = server->nextPendingConnection();
  QString     rfname;

  rfname = socket->readAll();

  socket->waitForReadyRead(3000);

  QByteArray  bytesReceived = socket->readAll();
  QFile       fileFromClient;
// fileFromClient.setFileName("/home/nrezayi/Desktop/downloaded/f.txt");
  fileFromClient.setFileName(rfname);

  if (fileFromClient.open(QIODevice::ReadWrite))
  {
    fileFromClient.write(bytesReceived, bytesReceived.length());
    fileFromClient.close();
    qDebug() << "file has been received";
    qDebug() << "great";
  }
  else
  {
    qDebug() << "file has NOT been received";
  }
}
