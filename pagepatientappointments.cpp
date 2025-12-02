#include "pagepatientappointments.h"
#include "ui_pagepatientappointments.h"
#include <QSqlQuery>
#include <QDateTime>

PagePatientAppointments::PagePatientAppointments(QWidget *parent) :
    QWidget(parent), ui(new Ui::PagePatientAppointments)
{
    ui->setupUi(this);
    // Ajuster les colonnes
    ui->tableAppointments->setColumnWidth(0, 150); // Date
    ui->tableAppointments->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Médecin
}

PagePatientAppointments::~PagePatientAppointments() { delete ui; }

void PagePatientAppointments::loadData(int patientId)
{
    ui->tableAppointments->setRowCount(0);

    QSqlQuery query;
    // On récupère tout l'historique des RDV
    QString sql = "SELECT r.date_heure, u.nom || ' ' || u.prenom, s.nom_service, r.statut "
                  "FROM rendez_vous r "
                  "JOIN utilisateurs u ON r.id_medecin = u.id_user "
                  "JOIN medecins m ON u.id_user = m.id_medecin "
                  "JOIN services s ON m.id_service = s.id_service "
                  "WHERE r.id_patient = :id "
                  "ORDER BY r.date_heure DESC"; // Du plus récent au plus vieux

    query.prepare(sql);
    query.bindValue(":id", patientId);

    if(query.exec()) {
        while(query.next()) {
            int row = ui->tableAppointments->rowCount();
            ui->tableAppointments->insertRow(row);

            ui->tableAppointments->setItem(row, 0, new QTableWidgetItem(query.value(0).toDateTime().toString("dd/MM/yyyy HH:mm")));
            ui->tableAppointments->setItem(row, 1, new QTableWidgetItem("Dr. " + query.value(1).toString()));
            ui->tableAppointments->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));

            QTableWidgetItem *status = new QTableWidgetItem(query.value(3).toString());
            // Petit code couleur sympa
            if(status->text() == "Confirmé") status->setForeground(QBrush(QColor("#28a745")));
            else if(status->text() == "Annulé") status->setForeground(QBrush(QColor("#dc3545")));

            ui->tableAppointments->setItem(row, 3, status);
        }
    }
}
