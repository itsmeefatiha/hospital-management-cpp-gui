#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admindashboard.h" // <-- à ajouter

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AdminDashboard *dashboard = new AdminDashboard(this);
    setCentralWidget(dashboard);
}

MainWindow::~MainWindow()
{
    delete ui;
}
