#ifndef NET_H
#define NET_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

//#include <QNetworkAccessManager>
//#include <QWebSocket>

#if defined(qNet)
#undef qNet
#endif
#define qNet Net::instance()

class Net : public QObject
{main
    Q_OBJECT
public:
    static Net* instance();
    void initialize();
    QJsonObject readRedis();
    QJsonObject tmpJsonObject;
    void writeRedis();
};

#endif // NET_H
