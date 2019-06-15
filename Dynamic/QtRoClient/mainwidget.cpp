#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("This is Client");
    init();
    ui->textEdit->setReadOnly(true);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    m_pRemoteNode = new QRemoteObjectNode(this);
    m_pRemoteNode->connectToNode(QUrl("local:interfaces"));
//    m_pInterface = m_pRemoteNode->acquire<CommonInterfaceReplica>();
    m_pInterface = m_pRemoteNode->acquireDynamic("Interfaces1");//动态获取

    //只有Replica初始化好了才能真正使用它，要不然connect无效
    connect(m_pInterface, &QRemoteObjectDynamicReplica::initialized, this, &MainWidget::onInitConnect);
}

/**
 * @brief MainWidget::onReceiveMsg
 * @param msg
 * 接收服务器下发的消息
 */
void MainWidget::onReceiveMsg(QString msg)
{
    ui->textEdit->append(QString("Server:") + msg);
}

void MainWidget::on_pushButton_clicked()
{
    QString msg = ui->lineEdit->text();
    if(!msg.isEmpty()){
//        m_pInterface->onMessage(msg); //调用槽发送消息给服务器
        emit sigSendMsg(msg);
    }
    ui->textEdit->append(QString("Client:") + msg);
    ui->lineEdit->clear();
}

void MainWidget::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void MainWidget::onInitConnect()
{
    qDebug() << "--->>>Lynn<<<---" << __FUNCTION__;
    connect(m_pInterface,SIGNAL(sigMessage(QString)),
            this,SLOT(onReceiveMsg(QString)));
    connect(this,SIGNAL(sigSendMsg(QString)),
            m_pInterface,SLOT(onMessage(QString)));

}
