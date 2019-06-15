#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "commoninterface.h"
#include <QRemoteObjectHost>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_clicked();
    void onReceiveMsg(const QString &msg);

    void on_lineEdit_returnPressed();

private:
    void init();
private:
    Ui::MainWidget *ui;
    CommonInterface * m_pInterface = nullptr;
    QRemoteObjectHost * m_pHost = nullptr;
};

#endif // MAINWIDGET_H
