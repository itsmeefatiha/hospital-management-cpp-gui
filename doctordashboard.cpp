#include "doctordashboard.h"
#include "ui_doctordashboard.h"
DoctorDashboard::DoctorDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorDashboard)
{
    ui->setupUi(this);
}
DoctorDashboard::~DoctorDashboard()
{
    delete ui;
}
