﻿#ifndef TcpServer_H
#define TcpServer_H

#include <QTcpServer>
#include <QHash>
#include "localsocket.h"
#include "../common/datastruct.h"
#include "../common/botanaes256.h"


class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    ~TcpServer();
signals:
    void notToServer();
    void userErro();
    void listenState(bool);

public slots:
    void setInfo(const QString &serHost,qint16 serPort,qint16 localBind);
    void socketConnect(const QString & user,const QString & pass);

    void serSocketRead();
    void serSocketDisCon();

    void localSockedDisCon();//断开连接的用户信息
    void LocalSocketRead();

protected:
    void incomingConnection(qintptr socketDescriptor);
    void initLocalProxy(QString & thisHost,qint16 & thisPort,LocalSocket * sock);

    void handleSwapData(swapData & data);
    void handleUserLog(swapData & data);
    void handleDisCon(swapData & data);

    inline bool decryptData(swapData & data);
    inline QByteArray encryptData(const QByteArray & data);
private:
    QHash<int,LocalSocket *> * tcpClient;//管理连接的map
    qint32 userID = -1;//用户ID
    QString tocken;
    QTcpSocket * serverSocket;
    bool isSerCon;
    QString serHost;
    qint16 serPort;
    qint16 localBind;
    qulonglong lastsize;
    BotanAES256 * aes;
};

#endif // TcpServer_H
