#include "patientdashboard.h"
#include "ui_patientdashboard.h"
#include "loginwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QDateTime>

PatientDashboard::PatientDashboard(int patientId, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PatientDashboard)
    , currentPatientId(patientId)
{
    ui->setupUi(this);

    QPixmap logo(":/resources/medicine.png");
    if (!logo.isNull()) {
        ui->label_logo->setPixmap(logo.scaled(ui->label_logo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // Initialisation des pages
    pageRdv = new PagePatientAppointments();
    pageRecord = new PagePatientRecord();
    pagePresc = new PagePatientPrescriptions();

    ui->stackedWidget->addWidget(pageRdv);    // Index 1
    ui->stackedWidget->addWidget(pageRecord); // Index 2
    ui->stackedWidget->addWidget(pagePresc);  // Index 3

    ui->stackedWidget->setCurrentIndex(0); // Accueil

    // --- CHARGEMENT DES DONNÉES ---
    // On passe l'ID aux sous-pages pour qu'elles sachent quoi afficher
    pageRdv->loadData(currentPatientId);
    pageRecord->loadData(currentPatientId);
    pagePresc->loadData(currentPatientId);

    loadHomeSummary();
}

PatientDashboard::~PatientDashboard()
{
    delete ui;
}

void PatientDashboard::loadHomeSummary()
{
    // 1. Afficher le nom du patient
    QSqlQuery qName;
    qName.prepare("SELECT prenom FROM utilisateurs WHERE id_user = :id");
    qName.bindValue(":id", currentPatientId);
    if(qName.exec() && qName.next()) {
        ui->label_patient_name->setText("Bonjour, " + qName.value(0).toString());
    }

    // 2. Afficher le PROCHAIN rendez-vous (Carte)
    QSqlQuery qRdv;
    // On cherche le premier RDV dans le futur
    QString sqlNext = "SELECT r.date_heure, u.nom "
                      "FROM rendez_vous r "
                      "JOIN utilisateurs u ON r.id_medecin = u.id_user "
                      "WHERE r.id_patient = :id AND r.date_heure > CURRENT_TIMESTAMP "
                      "ORDER BY r.date_heure ASC LIMIT 1";

    qRdv.prepare(sqlNext);
    qRdv.bindValue(":id", currentPatientId);

    if(qRdv.exec() && qRdv.next()) {
        QDateTime date = qRdv.value(0).toDateTime();
        QString docName = qRdv.value(1).toString();

        ui->lbl_c1_val->setText(date.toString("dd MMMM à HH:mm"));
        ui->lbl_c1_sub->setText("Avec Dr. " + docName);
    } else {
        ui->lbl_c1_val->setText("Aucun RDV");
        ui->lbl_c1_sub->setText("Rien de prévu prochainement.");
    }

    // 3. REMPLIR LE TABLEAU "DERNIÈRES ACTIVITÉS" (RDV PASSÉS)
    ui->tableRecent->setRowCount(0);

    QSqlQuery qRecent;
    // On cherche les 3 derniers RDV passés (Historique récent)
    QString sqlRecent = "SELECT r.date_heure, s.nom_service, u.nom "
                        "FROM rendez_vous r "
                        "JOIN utilisateurs u ON r.id_medecin = u.id_user "
                        "JOIN medecins m ON u.id_user = m.id_medecin "
                        "JOIN services s ON m.id_service = s.id_service "
                        "WHERE r.id_patient = :id AND r.date_heure < CURRENT_TIMESTAMP "
                        "ORDER BY r.date_heure DESC LIMIT 3";

    qRecent.prepare(sqlRecent);
    qRecent.bindValue(":id", currentPatientId);

    if (qRecent.exec()) {
        while(qRecent.next()) {
            int row = ui->tableRecent->rowCount();
            ui->tableRecent->insertRow(row);

            // Col 0: Date
            QString dateStr = qRecent.value(0).toDateTime().toString("dd/MM/yyyy");
            ui->tableRecent->setItem(row, 0, new QTableWidgetItem(dateStr));

            // Col 1: Type (Service)
            QString service = qRecent.value(1).toString();
            ui->tableRecent->setItem(row, 1, new QTableWidgetItem(service));

            // Col 2: Détail (Nom Médecin)
            QString doc = "Dr. " + qRecent.value(2).toString();
            ui->tableRecent->setItem(row, 2, new QTableWidgetItem(doc));
        }
    }
}

// --- Navigation ---
void PatientDashboard::on_btn_home_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->btn_home->setChecked(true); ui->btn_rdv->setChecked(false); ui->btn_record->setChecked(false); ui->btn_presc->setChecked(false);
}
void PatientDashboard::on_btn_rdv_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->btn_home->setChecked(false); ui->btn_rdv->setChecked(true); ui->btn_record->setChecked(false); ui->btn_presc->setChecked(false);
}
void PatientDashboard::on_btn_record_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
    ui->btn_home->setChecked(false); ui->btn_rdv->setChecked(false); ui->btn_record->setChecked(true); ui->btn_presc->setChecked(false);
}
void PatientDashboard::on_btn_presc_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
    ui->btn_home->setChecked(false); ui->btn_rdv->setChecked(false); ui->btn_record->setChecked(false); ui->btn_presc->setChecked(true);
}
void PatientDashboard::on_btn_logout_clicked() {
    LoginWindow *w = new LoginWindow(); w->show(); this->close();
}
