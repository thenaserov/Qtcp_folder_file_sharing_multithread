/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/

#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class SocketTest: public QObject
{
  Q_OBJECT

public:
  explicit SocketTest(const QString &fpathStr, const qint16 &portValInt, const QString &fname, QObject *parent = 0);

signals:
public slots:
  void  doConnect();

  void  connected();

  void  disconnected();

  void  bytesWritten(qint64 bytes);

  void  readyRead();

private:
  const QString  _fpathStr;
  const qint16   _portVal;
  const QString  _fname;
  QTcpSocket    *socket;
};

#endif // SOCKETTEST_H
