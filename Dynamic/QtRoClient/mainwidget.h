#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QRemoteObjectNode>
//#include "rep_CommonInterface_replica.h"
#include <QRemoteObjectDynamicReplica>


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
signals:
    void sigSendMsg(QString msg);
private slots:
    void onReceiveMsg(QString msg);
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();
    void onInitConnect();

private:
    void init();
private:
    Ui::MainWidget *ui;
    QRemoteObjectNode * m_pRemoteNode = nullptr;
    QRemoteObjectDynamicReplica * m_pInterface = nullptr;
};

#endif // MAINWIDGET_H
