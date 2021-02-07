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
  explicit MyTcpServer(QObject *parent = 0);

signals:
public slots:
  void  newConnection();

private:
  QTcpServer *server;
};

#endif // MYTCPSERVER_H
