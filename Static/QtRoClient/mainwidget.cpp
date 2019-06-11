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
    m_pInterface = m_pRemoteNode->acquire<CommonInterfaceReplica>();

    connect(m_pInterface,&CommonInterfaceReplica::sigMessage,
            this,&MainWidget::onReceiveMsg);
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
        m_pInterface->onMessage(msg); //调用槽发送消息给服务器
    }
    ui->textEdit->append(QString("Client:") + msg);
    ui->lineEdit->clear();
}

void MainWidget::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}
