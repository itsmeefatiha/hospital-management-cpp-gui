#include "pagemedicalrecord.h"
#include "ui_pagemedicalrecord.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

// Variables globales au fichier pour stocker le contexte
int currentPatientId = -1;
int currentDocId = -1;

PageMedicalRecord::PageMedicalRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageMedicalRecord)
{
    ui->setupUi(this);

    // Configurer le tableau prescription
    ui->table_prescription->setColumnCount(3);
    ui->table_prescription->setHorizontalHeaderLabels({"Médicament", "Dosage", "Instructions"});
    ui->table_prescription->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Configurer le tableau historique
    ui->table_history->setColumnCount(3);
    ui->table_history->setHorizontalHeaderLabels({"Date", "Médecin", "Diagnostic"});
    ui->table_history->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Connexions manuelles des boutons
    connect(ui->btn_add_med, &QPushButton::clicked, this, &PageMedicalRecord::on_btn_add_med_clicked);
    connect(ui->btn_save_consultation, &QPushButton::clicked, this, &PageMedicalRecord::on_btn_save_consultation_clicked);

    // Connexion du clic sur l'historique
    connect(ui->table_history, &QTableWidget::cellClicked, this, &PageMedicalRecord::on_table_history_cellClicked);
}

PageMedicalRecord::~PageMedicalRecord()
{
    delete ui;
}

void PageMedicalRecord::loadPatient(int pid, int docId)
{
    currentPatientId = pid;
    currentDocId = docId;

    // 1. Infos Patient
    QSqlQuery q;
    q.prepare("SELECT nom || ' ' || prenom, date_naissance FROM utilisateurs p "
              "JOIN patients pat ON p.id_user = pat.id_patient WHERE id_user = :id");
    q.bindValue(":id", pid);

    if(q.exec() && q.next()) {
        QString info = "Patient : " + q.value(0).toString() + " (" + q.value(1).toDate().toString("dd/MM/yyyy") + ")";
        ui->label_patient_name->setText(info);
    }

    // 2. Allergies
    QSqlQuery qAllergy;
    qAllergy.prepare("SELECT libelle FROM allergies a "
                     "JOIN dossiers_medicaux d ON a.id_dossier = d.id_dossier "
                     "WHERE d.id_patient = :id");
    qAllergy.bindValue(":id", pid);

    QStringList allergies;
    if(qAllergy.exec()) {
        while(qAllergy.next()) allergies << qAllergy.value(0).toString();
    }
    ui->label_patient_allergies->setText(allergies.isEmpty() ? "Aucune allergie connue" : "⚠️ Allergies: " + allergies.join(", "));

    // 3. Reset des formulaires
    ui->textEdit_diagnostic->clear();
    ui->textEdit_report->clear();
    ui->table_prescription->setRowCount(0);

    // 4. Charger l'historique
    loadHistory(pid);
}

void PageMedicalRecord::loadHistory(int patientId)
{
    ui->table_history->setRowCount(0);
    ui->textEdit_history_view->clear();

    QSqlQuery query;
    // Récupère l'historique : Date, Nom Médecin, Diagnostic, Rapport Complet
    QString sql = "SELECT c.date_consultation, "
                  "u.nom || ' ' || u.prenom, "
                  "c.diagnostique, "
                  "c.compte_rendu "
                  "FROM consultations c "
                  "JOIN medecins m ON c.id_medecin = m.id_medecin "
                  "JOIN utilisateurs u ON m.id_medecin = u.id_user "
                  "JOIN dossiers_medicaux d ON c.id_dossier = d.id_dossier "
                  "WHERE d.id_patient = :pid "
                  "ORDER BY c.date_consultation DESC";

    query.prepare(sql);
    query.bindValue(":pid", patientId);

    if(query.exec()) {
        while(query.next()) {
            int row = ui->table_history->rowCount();
            ui->table_history->insertRow(row);

            // Col 0: Date
            ui->table_history->setItem(row, 0, new QTableWidgetItem(query.value(0).toDate().toString("dd/MM/yyyy")));
            // Col 1: Médecin
            ui->table_history->setItem(row, 1, new QTableWidgetItem("Dr. " + query.value(1).toString()));
            // Col 2: Diagnostic
            ui->table_history->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));

            // Astuce : On cache le rapport complet dans la première case pour l'afficher au clic
            ui->table_history->item(row, 0)->setData(Qt::UserRole, query.value(3).toString());
        }
    }
}

void PageMedicalRecord::on_table_history_cellClicked(int row, int column)
{
    // Quand on clique sur une ligne, on récupère le rapport caché et on l'affiche en bas
    QString fullReport = ui->table_history->item(row, 0)->data(Qt::UserRole).toString();
    ui->textEdit_history_view->setText(fullReport);
}

void PageMedicalRecord::on_btn_add_med_clicked()
{
    QString nom = ui->lineEdit_med_name->text();
    QString dose = ui->lineEdit_med_dose->text();

    if(nom.isEmpty()) return;

    int row = ui->table_prescription->rowCount();
    ui->table_prescription->insertRow(row);
    ui->table_prescription->setItem(row, 0, new QTableWidgetItem(nom));
    ui->table_prescription->setItem(row, 1, new QTableWidgetItem(dose));
    ui->table_prescription->setItem(row, 2, new QTableWidgetItem("1x/jour"));

    ui->lineEdit_med_name->clear();
    ui->lineEdit_med_dose->clear();
}

void PageMedicalRecord::on_btn_save_consultation_clicked()
{
    if(currentPatientId == -1) {
        QMessageBox::warning(this, "Erreur", "Aucun patient sélectionné.");
        return;
    }

    QSqlDatabase::database().transaction();

    // 1. Récupérer ID Dossier
    QSqlQuery qDossier;
    qDossier.prepare("SELECT id_dossier FROM dossiers_medicaux WHERE id_patient = :id");
    qDossier.bindValue(":id", currentPatientId);
    if(!qDossier.exec() || !qDossier.next()) {
        // Création auto si manque (sécurité)
        QSqlQuery createDos;
        createDos.prepare("INSERT INTO dossiers_medicaux (id_patient) VALUES (:id)");
        createDos.bindValue(":id", currentPatientId);
        createDos.exec();
        // On re-tente
        qDossier.exec(); qDossier.next();
    }
    int idDossier = qDossier.value(0).toInt();

    // 2. Insert Consultation
    QSqlQuery qConsult;
    qConsult.prepare("INSERT INTO consultations (date_consultation, diagnostique, compte_rendu, id_dossier, id_medecin) "
                     "VALUES (CURRENT_DATE, :diag, :cr, :idd, :idm) RETURNING id_consultation");
    qConsult.bindValue(":diag", ui->textEdit_diagnostic->toPlainText());
    qConsult.bindValue(":cr", ui->textEdit_report->toPlainText());
    qConsult.bindValue(":idd", idDossier);
    qConsult.bindValue(":idm", currentDocId);

    if(qConsult.exec() && qConsult.next()) {
        int idConsult = qConsult.value(0).toInt();

        // 3. Insert Prescriptions
        for(int i=0; i < ui->table_prescription->rowCount(); i++) {
            QSqlQuery qPresc;
            qPresc.prepare("INSERT INTO prescriptions (medicament, dosage, duree, instructions, id_consultation) "
                           "VALUES (:m, :d, '7 jours', :i, :idc)");
            qPresc.bindValue(":m", ui->table_prescription->item(i, 0)->text());
            qPresc.bindValue(":d", ui->table_prescription->item(i, 1)->text());
            qPresc.bindValue(":i", ui->table_prescription->item(i, 2)->text());
            qPresc.bindValue(":idc", idConsult);
            qPresc.exec();
        }

        QSqlDatabase::database().commit();
        QMessageBox::information(this, "Succès", "Consultation enregistrée.");

        // Rafraichir l'historique pour voir le nouvel ajout immédiatement
        loadHistory(currentPatientId);

        // Vider les champs
        ui->textEdit_diagnostic->clear();
        ui->textEdit_report->clear();
        ui->table_prescription->setRowCount(0);

    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Erreur", "Erreur SQL : " + qConsult.lastError().text());
    }
}
