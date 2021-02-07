/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/
#include "sockettest.h"
#include <QTcpSocket>
#include <QFile>
#include <QByteArray>
#include <QHostAddress>

SocketTest::SocketTest(const QString &fpathStr, const qint16 &portValInt, QObject *parent):
  QObject(parent), _fpathStr(fpathStr), _portVal(portValInt) //// NOTE I don't understand this line
{
}

void  SocketTest::doConnect()
{
  socket = new QTcpSocket(this);

  connect(socket, SIGNAL(connected()), this, SLOT(connected()));
  connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

  qDebug() << "connecting...";

  socket->connectToHost("localhost", _portVal);

  if (!socket->waitForConnected(1000))
  {
    qDebug() << "Error: " << socket->errorString();
  }
}

// NOTE : why the program did not work without this function?
void  SocketTest::connected()
{
// NOTE : the stackoverflow code to send a file to the server
  QFile  file(_fpathStr);

// WARNING : Behnam Sabbaghi helped for this part
  if (file.open(QIODevice::ReadWrite))
  {
    QByteArray  data = file.readAll();
    file.close();
    socket->write(data, data.length());
// WARNING : added on 2021/02/07
    socket->waitForBytesWritten(3000);
    socket->flush();
  }
  else
  {
    qDebug() << "not open!";
  }

// qDebug() << "connected...";
// socket->write("NIGGAAAAAA");
// socket->waitForBytesWritten(1000);
// socket->flush();
}

void  SocketTest::disconnected()
{
  qDebug() << "disconnected...";
}

void  SocketTest::bytesWritten(qint64 bytes)
{
  qDebug() << bytes << " bytes written...";
}

void  SocketTest::readyRead()
{
  qDebug() << "reading...";

  // read the data from the socket
  qDebug() << socket->readAll();
}
