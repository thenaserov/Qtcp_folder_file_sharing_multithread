// 2021.02.04

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <iostream>
#include <string>
#include <QFile>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include "MyTcpServer.h"
#include "sockettest.h"

int  main(int argc, char *argv[])
{
  QCoreApplication  app(argc, argv);

  QCoreApplication::setApplicationName("transferer");
  QCoreApplication::setApplicationVersion("1.0");
  QCommandLineParser  parser;
  parser.setApplicationDescription("Transfer files to the server");
  parser.addHelpOption();
  parser.addVersionOption();
  QCommandLineOption  port(QStringList() << "p" << "port",
                          QCoreApplication::translate("main", "to deifne a port"),
                          QCoreApplication::translate("main", "port"));
  QCommandLineOption  mode(QStringList() << "m" << "mode",
                          QCoreApplication::translate("main", "Copy all source files into <directory>."),
                          QCoreApplication::translate("main", "mode"));
  QCommandLineOption  fpath(QStringList() << "f" << "fpath",
                           QCoreApplication::translate("main", "to define a file path"),
                           QCoreApplication::translate("main", "fpath"));
  parser.addOption(port);
  parser.addOption(fpath);
  parser.addOption(mode);
  parser.parse(app.arguments());
  parser.process(app);
  const QStringList  args       = parser.positionalArguments();
  QString            fpathStr   = parser.value(fpath);
  QString            modeStr    = parser.value(mode);
  QString            portVal    = parser.value(port);
  qint16             portValInt = portVal.toInt();

  qDebug() << "you have provided this information: ";
  qDebug() << modeStr;
  qDebug() << fpathStr;
  qDebug() << portValInt;

  // WARNING : used the new method that Farzad Abedini said
  SocketTest  *cTest  = nullptr;
  MyTcpServer *server = nullptr;

  // client
  if (parser.value(mode) == "client")
  {
    qDebug() << "client...";
    qDebug() << "checking if the path exists...";

    // WARNING : CODE STUCK IN HERE -> there must be a problem with file checking sequence!
    if (QFile(parser.value(fpath)).exists())
// if (QFile::exists(fpathStr))
    {
      qDebug() << "path exists...";
      qDebug() << "checking if the port is set...";

      if (parser.isSet(port))
      {
        qDebug() << "port is set...";
        cTest = new SocketTest(fpathStr, portValInt);
        cTest->doConnect();
      }
      else
      {
        qDebug() << "port is not set...";
        qint16  portClient = 8080;
        cTest = new SocketTest(fpathStr, portClient);
        cTest->doConnect();
      }
    }
    else
    {
      qDebug() << "file does not exist!";
    }
  }
  // server
  else if (parser.value(mode) == "server")
  {
    if (parser.isSet(port))
    {
      qDebug() << "port is defined...";
      server = new MyTcpServer(portValInt);
    }
    else
    {
      qDebug() << "port is not defined...";
      qint16  serverPort = 8080;
      server = new MyTcpServer(serverPort);
    }
  }

  int  exec = app.exec();

  if (cTest)
  {
    delete cTest;
  }

  if (server)
  {
    delete server;
  }

  return exec;
}
