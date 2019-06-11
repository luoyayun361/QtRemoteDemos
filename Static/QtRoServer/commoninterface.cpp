#include "commoninterface.h"
#include <QDebug>

CommonInterface::CommonInterface(QObject *parent):
    CommonInterfaceSource(parent)
{
}

/**
 * @brief CommonInterface::onMessage
 * @param msg
 * 接收客户端的消息
 */
void CommonInterface::onMessage(QString msg)
{
    emit sigReceiveMsg(msg);
}

/**
 * @brief CommonInterface::sendMsg
 * @param msg
 * 发送消息给客户端
 */
void CommonInterface::sendMsg(const QString &msg)
{
    emit sigMessage(msg);
}
