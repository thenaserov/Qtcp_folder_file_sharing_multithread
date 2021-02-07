/**************************************************
 *  Copyright (C) 2021 ARAD. All Rights Reserved.  *
 ***************************************************/

#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include <QObject>
#include <QTcpSocket>
class MyTcpSocket: public QObject
{
  Q_OBJECT

public:
  explicit MyTcpSocket(QObject *parent = 0);

signals:
public  slots:
private:
  QTcpSocket *socket;
};

#endif // MYTCPSOCKET_H
