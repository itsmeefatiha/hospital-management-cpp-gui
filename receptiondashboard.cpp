#include "receptiondashboard.h"
#include "ui_receptiondashboard.h"
#include "loginwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

ReceptionDashboard::ReceptionDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReceptionDashboard)
{
    ui->setupUi(this);

    // Initialisation des pages
    pagePatients = new PagePatients();
    pageRDV = new PageRDV();
    pageAdmissions = new PageAdmissions();

    ui->stackedWidget->addWidget(pagePatients);   // Index 1
    ui->stackedWidget->addWidget(pageRDV);        // Index 2
    ui->stackedWidget->addWidget(pageAdmissions); // Index 3

    ui->stackedWidget->setCurrentIndex(0);

    refreshAgenda();
}

ReceptionDashboard::~ReceptionDashboard()
{
    delete ui;
}

void ReceptionDashboard::refreshAgenda()
{
    ui->table_global_agenda->setRowCount(0);

    QSqlQuery query;
    // On récupère les RDV du jour et futurs, triés par date
    QString sql = "SELECT r.date_heure, "
                  "p.nom || ' ' || p.prenom, " // Nom Patient
                  "m.nom || ' ' || m.prenom, " // Nom Médecin
                  "s.nom_service, "
                  "r.statut "
                  "FROM rendez_vous r "
                  "JOIN utilisateurs p ON r.id_patient = p.id_user "
                  "JOIN utilisateurs m ON r.id_medecin = m.id_user "
                  "JOIN medecins med ON m.id_user = med.id_medecin "
                  "JOIN services s ON med.id_service = s.id_service "
                  "WHERE r.date_heure >= CURRENT_DATE "
                  "ORDER BY r.date_heure ASC";

    if(query.exec(sql)) {
        while(query.next()) {
            int row = ui->table_global_agenda->rowCount();
            ui->table_global_agenda->insertRow(row);

            ui->table_global_agenda->setItem(row, 0, new QTableWidgetItem(query.value(0).toDateTime().toString("dd/MM HH:mm")));
            ui->table_global_agenda->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->table_global_agenda->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->table_global_agenda->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->table_global_agenda->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        }
    }
}

// --- Navigation ---
void ReceptionDashboard::on_btn_nav_dashboard_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    refreshAgenda(); // Rafraichir à chaque retour
    ui->btn_nav_dashboard->setChecked(true);
    ui->btn_nav_patients->setChecked(false); ui->btn_nav_rdv->setChecked(false); ui->btn_nav_admissions->setChecked(false);
}

void ReceptionDashboard::on_btn_nav_patients_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    pagePatients->refresh(); // Charger la liste patients
    ui->btn_nav_dashboard->setChecked(false);
    ui->btn_nav_patients->setChecked(true); ui->btn_nav_rdv->setChecked(false); ui->btn_nav_admissions->setChecked(false);
}

void ReceptionDashboard::on_btn_nav_rdv_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
    pageRDV->refresh(); // Charger les listes déroulantes
    ui->btn_nav_dashboard->setChecked(false);
    ui->btn_nav_patients->setChecked(false); ui->btn_nav_rdv->setChecked(true); ui->btn_nav_admissions->setChecked(false);
}

void ReceptionDashboard::on_btn_nav_admissions_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
    pageAdmissions->refresh(); // Charger les chambres dispos
    ui->btn_nav_dashboard->setChecked(false);
    ui->btn_nav_patients->setChecked(false); ui->btn_nav_rdv->setChecked(false); ui->btn_nav_admissions->setChecked(true);
}

void ReceptionDashboard::on_btn_logout_clicked() {
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}
