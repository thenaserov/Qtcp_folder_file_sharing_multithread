/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/

// mytcpserver.cpp
#include <QFile>
#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(int port, QObject *parent):
  QObject(parent), _port(port)
{
  server = new QTcpServer(this);
  // NOTE : if user connects, the signal will be emitted!
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

  socket->waitForReadyRead(3000);
  QByteArray  bytesReceived = socket->readAll();
  QFile       fileFromClient;
  fileFromClient.setFileName("/home/nrezayi/Desktop/downloaded/f.txt");

  if (fileFromClient.open(QIODevice::ReadWrite))
  {
    fileFromClient.write(bytesReceived, bytesReceived.length());
    fileFromClient.close();
    qDebug() << "file has been received";
  }
  else
  {
    qDebug() << "file has NOT been received";
  }
}
