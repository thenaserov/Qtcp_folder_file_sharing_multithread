/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class MyTcpServer: public QObject
{
  Q_OBJECT

public:
  explicit MyTcpServer(int port, QObject *parent = 0);

signals:
public slots:
  void  newConnection();

private:
  QTcpServer         *server;
  QTcpSocket         *socket;
  const QHostAddress  _host;
  const quint16       _port;
};

#endif // MYTCPSERVER_H
