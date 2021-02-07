/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/
#include "MyTcpSocket.h"

MyTcpSocket::MyTcpSocket(QObject *parent):
  QObject(parent)
{
}

void  MyTcpSocket::doConnect()
{
  socket = new QTcpSocket(this);

  socket->connectToHost("127.0.0.1", 80);

  if (socket->waitForConnected(5000))
  {
    qDebug() << "Connected!";

    // send
    socket->write("Hello \r\n\r\n");
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);

    qDebug() << "Reading: " << socket->bytesAvailable();

    // get the data
    qDebug() << socket->readAll();

    // close the connection
    socket->close();
  }
  else
  {
    qDebug() << "Not connected!";
  }
}
