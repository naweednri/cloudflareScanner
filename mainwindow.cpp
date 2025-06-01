#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include "cloudflare.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_start,&QPushButton::clicked,this,&MainWindow::BtnStart_Clicked);
    connect(ui->btn_fetch,&QPushButton::clicked,this,&MainWindow::BtnFetch_Clicked);
    ui->tblWidget->setRowCount(10);
    ui->tblWidget->horizontalHeader()->setStretchLastSection(true);
    ui->txtEdit_thread->setPlaceholderText("1");

}
void MainWindow::BtnStart_Clicked()
{
    qDebug()<<"Btn start clicked";
}
void MainWindow::BtnFetch_Clicked()
{
    cloudflare obj("https://www.cloudflare.com/ips-v4/#");
    obj.run();
    qDebug()<<"Btn fetch clicked";
}
MainWindow::~MainWindow()
{
    delete ui;
}
