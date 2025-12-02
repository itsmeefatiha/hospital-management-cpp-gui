#include "pagepatientrecord.h"
#include "ui_pagepatientrecord.h"
#include <QSqlQuery>
#include <QDate>

PagePatientRecord::PagePatientRecord(QWidget *parent) :
    QWidget(parent), ui(new Ui::PagePatientRecord)
{
    ui->setupUi(this);
    // Connecter le clic de la liste
    connect(ui->listWidget_reports, &QListWidget::itemClicked,
            this, &PagePatientRecord::on_listWidget_reports_itemClicked);
}

PagePatientRecord::~PagePatientRecord() { delete ui; }

void PagePatientRecord::loadData(int patientId)
{
    ui->listWidget_reports->clear();
    ui->textEdit_report_view->clear();

    QSqlQuery query;
    // On cherche les consultations via le dossier médical
    QString sql = "SELECT c.date_consultation, s.nom_service, c.compte_rendu "
                  "FROM consultations c "
                  "JOIN dossiers_medicaux d ON c.id_dossier = d.id_dossier "
                  "JOIN utilisateurs m ON c.id_medecin = m.id_user "
                  "JOIN medecins med ON m.id_user = med.id_medecin "
                  "JOIN services s ON med.id_service = s.id_service "
                  "WHERE d.id_patient = :id "
                  "ORDER BY c.date_consultation DESC";

    query.prepare(sql);
    query.bindValue(":id", patientId);

    if(query.exec()) {
        while(query.next()) {
            QString date = query.value(0).toDate().toString("dd/MM/yyyy");
            QString service = query.value(1).toString();
            QString rapport = query.value(2).toString();

            // On affiche "Date - Service" dans la liste
            QListWidgetItem *item = new QListWidgetItem(date + " - " + service);
            // On cache le rapport complet dans l'item
            item->setData(Qt::UserRole, rapport);

            ui->listWidget_reports->addItem(item);
        }
    }
}

void PagePatientRecord::on_listWidget_reports_itemClicked(QListWidgetItem *item)
{
    // Afficher le contenu caché
    ui->textEdit_report_view->setHtml(item->data(Qt::UserRole).toString());
}
