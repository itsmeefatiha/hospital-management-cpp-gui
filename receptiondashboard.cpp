#include "receptiondashboard.h"
#include "ui_receptiondashboard.h"
ReceptionDashboard::ReceptionDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReceptionDashboard)
{
    ui->setupUi(this);
}
ReceptionDashboard::~ReceptionDashboard()
{
    delete ui;
}
