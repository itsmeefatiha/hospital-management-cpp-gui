#include "pagerdv.h"
#include "ui_pagerdv.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>

PageRDV::PageRDV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageRDV)
{
    ui->setupUi(this);
    ui->dateTimeEdit_rdv->setDateTime(QDateTime::currentDateTime());
    // Connecter le changement de service au chargement des médecins
    connect(ui->combo_service, &QComboBox::currentTextChanged,
            this, &PageRDV::loadDoctors);

    refresh();
}

PageRDV::~PageRDV()
{
    delete ui;
}

void PageRDV::refresh()
{
    // 1. Charger les Services
    ui->combo_service->blockSignals(true);
    ui->combo_service->clear();
    QSqlQuery query;
    if(query.exec("SELECT nom_service FROM services")) {
        while(query.next()) {
            ui->combo_service->addItem(query.value(0).toString());
        }
    }
    ui->combo_service->blockSignals(false);

    // Charger les médecins pour le premier service
    loadDoctors(ui->combo_service->currentText());

    // 2. Charger la liste des RDV
    loadAppointments();
}

void PageRDV::loadDoctors(const QString &serviceName)
{
    ui->combo_doctor->clear();
    QSqlQuery query;
    query.prepare("SELECT u.nom || ' ' || u.prenom, u.id_user "
                  "FROM medecins m "
                  "JOIN utilisateurs u ON m.id_medecin = u.id_user "
                  "JOIN services s ON m.id_service = s.id_service "
                  "WHERE s.nom_service = :serv");
    query.bindValue(":serv", serviceName);

    if(query.exec()) {
        while(query.next()) {
            // On stocke l'ID dans la "data" de l'item combo
            ui->combo_doctor->addItem(query.value(0).toString(), query.value(1));
        }
    }
}

void PageRDV::loadAppointments() {
    ui->table_rdv->setRowCount(0);
    QSqlQuery q;
    if(q.exec("SELECT r.date_heure, p.nom || ' ' || p.prenom, m.nom || ' ' || m.prenom, r.statut "
               "FROM rendez_vous r "
               "JOIN utilisateurs p ON r.id_patient = p.id_user "
               "JOIN utilisateurs m ON r.id_medecin = m.id_user "
               "WHERE r.date_heure > CURRENT_DATE ORDER BY r.date_heure")) {
        while(q.next()) {
            int r = ui->table_rdv->rowCount();
            ui->table_rdv->insertRow(r);
            ui->table_rdv->setItem(r, 0, new QTableWidgetItem(q.value(0).toDateTime().toString("dd/MM HH:mm")));
            ui->table_rdv->setItem(r, 1, new QTableWidgetItem(q.value(1).toString()));
            ui->table_rdv->setItem(r, 2, new QTableWidgetItem(q.value(2).toString()));
            ui->table_rdv->setItem(r, 3, new QTableWidgetItem(q.value(3).toString()));
        }
    }
}

void PageRDV::on_btn_confirm_clicked()
{
    QString patientInput = ui->lineEdit_patient_search->text().trimmed();

    if(patientInput.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un nom de patient.");
        return;
    }

    // Recherche intelligente (Nom complet ou partiel) ---
    QSqlQuery findPat;
    // On concatène nom + prenom pour pouvoir chercher d'un coup
    // ILIKE permet d'ignorer les majuscules/minuscules
    findPat.prepare("SELECT id_user FROM utilisateurs "
                    "WHERE role='PATIENT' "
                    "AND (nom || ' ' || prenom ILIKE :search "
                    "OR prenom || ' ' || nom ILIKE :search "
                    "OR nom ILIKE :search OR prenom ILIKE :search) LIMIT 1");

    findPat.bindValue(":search", "%" + patientInput + "%");

    if(!findPat.exec() || !findPat.next()) {
        QMessageBox::warning(this, "Erreur", "Patient introuvable.\nEssayez juste le nom de famille ou vérifiez l'orthographe.");
        return;
    }

    int patientId = findPat.value(0).toInt();

    // Vérification médecin
    if (ui->combo_doctor->currentIndex() == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un médecin.");
        return;
    }
    int doctorId = ui->combo_doctor->currentData().toInt();
    QDateTime dateRdv = ui->dateTimeEdit_rdv->dateTime();

    QSqlQuery insert;
    insert.prepare("INSERT INTO rendez_vous (date_heure, statut, id_patient, id_medecin) "
                   "VALUES (:date, 'Planifié', :pid, :mid)");
    insert.bindValue(":date", dateRdv);
    insert.bindValue(":pid", patientId);
    insert.bindValue(":mid", doctorId);

    if(insert.exec()) {
        QMessageBox::information(this, "Succès", "Rendez-vous confirmé !");
        loadAppointments();
        ui->lineEdit_patient_search->clear(); // On vide le champ après succès
    } else {
        QMessageBox::critical(this, "Erreur", insert.lastError().text());
    }
}
