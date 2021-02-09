/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/
#include "sockettest.h"
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QHostAddress>
#include <string>

SocketTest::SocketTest(const QString &fpathStr, const qint16 &portValInt, QObject *parent):
  QObject(parent), _fpathStr(fpathStr), _portVal(portValInt)
{
}

void  SocketTest::sendfile(QString path)
{
  // code of socket construction
  socket = new QTcpSocket(this);

  connect(socket, &QTcpSocket::connected, this, &SocketTest::connected);
  connect(socket, &QTcpSocket::disconnected, this, &SocketTest::disconnected);
  connect(socket, &QTcpSocket::bytesWritten, this, &SocketTest::bytesWritten);
  connect(socket, &QTcpSocket::readyRead, this, &SocketTest::readyRead);

  qDebug() << "connecting...";

  socket->connectToHost("localhost", _portVal);

  if (!socket->waitForConnected(10000))
  {
    qDebug() << "Error: " << socket->errorString();
    exit(1);
  }

  QFile  file(path);

  if (file.open(QIODevice::ReadWrite))
  {
// NOTE : sending the file name to the server
    qDebug() << path;
    socket->write(path.toStdString().c_str(), path.toStdString().size());
    socket->waitForBytesWritten(3000);
    socket->flush();
// NOTE : sending the file itself
    QByteArray  data = file.readAll();
    file.close();
    socket->write(data, data.length());
    socket->waitForBytesWritten(3000);
    socket->flush();
  }
  else
  {
    qDebug() << "not open!";
  }

  // sending

  // socket destruction
}

void  SocketTest::doConnect()
{
  socket = new QTcpSocket(this);

  connect(socket, &QTcpSocket::connected, this, &SocketTest::connected);
  connect(socket, &QTcpSocket::disconnected, this, &SocketTest::disconnected);
  connect(socket, &QTcpSocket::bytesWritten, this, &SocketTest::bytesWritten);
  connect(socket, &QTcpSocket::readyRead, this, &SocketTest::readyRead);

  qDebug() << "connecting...";

  socket->connectToHost("localhost", _portVal);

  if (!socket->waitForConnected(1000))
  {
    qDebug() << "Error: " << socket->errorString();
  }
}

void  SocketTest::connected()
{
  // QFile  file(_fpathStr);

  // assume the directory exists and contains some files
  QDir         directory(_fpathStr);
  QStringList  files = directory.entryList(QStringList() << "*.*", QDir::Files);

  for (QString filename : files)
  {
    sendfile(filename);
  }

  socket->close();
  delete socket;
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
  qDebug() << socket->readAll();
}
