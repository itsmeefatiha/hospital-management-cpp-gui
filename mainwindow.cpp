#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admindashboard.h" // <-- à ajouter

#include <QSqlDatabase>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AdminDashboard *dashboard = new AdminDashboard(this);
    setCentralWidget(dashboard);

    qDebug() << QSqlDatabase::drivers();

}

MainWindow::~MainWindow()
{
    delete ui;
}
