#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("This is Server");
    init();
    ui->textEdit->setReadOnly(true);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    m_pHost = new QRemoteObjectHost(this);
    m_pHost->setHostUrl(QUrl("local:interfaces"));
    m_pInterface = new CommonInterface(this);
    m_pHost->enableRemoting(m_pInterface);
    connect(m_pInterface,&CommonInterface::sigReceiveMsg,this,&MainWidget::onReceiveMsg);
}

void MainWidget::on_pushButton_clicked()
{
    QString msg = ui->lineEdit->text();
    if(!msg.isEmpty()){
        m_pInterface->sendMsg(msg);
    }
    ui->textEdit->append(QString("Server:") + msg);
    ui->lineEdit->clear();
}

void MainWidget::onReceiveMsg(const QString &msg)
{
    ui->textEdit->append(QString("Client:") + msg);
}

void MainWidget::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}
