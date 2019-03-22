#include "net.h"
//#include <QNetworkProxy>
//#include <QNetworkReply>
#include <QUrl>

/*
{
    "image_type":"jpg",
    "images":{
        "20160914175230_00210":{
            "annos":[
                {
                    "points":[
                        420,
                        477,
                        539,
                        568,
                        0,
                        -1
                    ],
                    "type":2,
                    "subtype":0
                }
            ],
            "size":[
                1280,
                1024
            ]
        }
    }
}
*/

Q_GLOBAL_STATIC(Net, net)

Net* Net::instance()
{
    return net();
}

void Net::initialize()
{
    tmpJsonObject.insert("image_type", "jpg");
    QJsonObject obj;
    QJsonArray arr1;
    QJsonObject nos1;

    QJsonArray arr3;
    arr3 << 420 << 477 << 539 << 568 << 0 << -1;

    nos1.insert("points", arr3);
    nos1.insert("type", 2);
    nos1.insert("subtype", 0);

    arr1.append(nos1);

    QJsonArray arr2;
    arr2.append(1280);
    arr2.append(1024);
    obj.insert("annos", arr1);
    obj.insert("size", arr2);
    tmpJsonObject.insert("image", obj);
}

QJsonObject Net::readRedis()
{
    return tmpJsonObject;
}

void Net::writeRedis()
{
    //
}
