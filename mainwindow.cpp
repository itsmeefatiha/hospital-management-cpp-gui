#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admindashboard.h"
#include "doctordashboard.h"
#include "receptiondashboard.h"

#include <QSqlDatabase>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReceptionDashboard *dashboard = new ReceptionDashboard(this);
    setCentralWidget(dashboard);

    //qDebug() << QSqlDatabase::drivers();

}

MainWindow::~MainWindow()
{
    delete ui;
}
