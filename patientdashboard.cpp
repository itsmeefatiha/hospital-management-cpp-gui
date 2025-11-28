#include "patientdashboard.h"
#include "ui_patientdashboard.h"
PatientDashboard::PatientDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientDashboard)
{
    ui->setupUi(this);
}
PatientDashboard::~PatientDashboard()
{
    delete ui;
}
