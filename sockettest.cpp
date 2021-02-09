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

SocketTest::SocketTest(const QString &fpathStr, const qint16 &portValInt, const QString &fname, QObject *parent):
  QObject(parent), _fpathStr(fpathStr), _portVal(portValInt), _fname(fname)
{
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
    QFile  file(filename);

    if (file.open(QIODevice::ReadWrite))
    {
      // NOTE : sending the file name to the server
      socket->write(_fname.toStdString().c_str(), _fname.toStdString().size());
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
  }
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
