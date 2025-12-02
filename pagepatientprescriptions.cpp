#include "pagepatientprescriptions.h"
#include "ui_pagepatientprescriptions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QMessageBox>
#include <QDebug>

PagePatientPrescriptions::PagePatientPrescriptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagePatientPrescriptions)
{
    ui->setupUi(this);

    // Amélioration visuelle du tableau
    ui->tablePrescriptions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // CONNEXION DU CLIC : Indispensable pour que le bouton "Imprimer" fonctionne
    connect(ui->tablePrescriptions, &QTableWidget::cellClicked,
            this, &PagePatientPrescriptions::on_tablePrescriptions_cellClicked);
}

PagePatientPrescriptions::~PagePatientPrescriptions()
{
    delete ui;
}

void PagePatientPrescriptions::loadData(int patientId)
{
    ui->tablePrescriptions->setRowCount(0);

    QSqlQuery query;
    // On récupère : Date, Nom Médecin, Détail (Médicament + Dosage + Instructions)
    QString sql = "SELECT c.date_consultation, u.nom || ' ' || u.prenom, "
                  "p.medicament || ' (' || p.dosage || ') - ' || p.instructions "
                  "FROM prescriptions p "
                  "JOIN consultations c ON p.id_consultation = c.id_consultation "
                  "JOIN dossiers_medicaux d ON c.id_dossier = d.id_dossier "
                  "JOIN utilisateurs u ON c.id_medecin = u.id_user "
                  "WHERE d.id_patient = :id "
                  "ORDER BY c.date_consultation DESC";

    query.prepare(sql);
    query.bindValue(":id", patientId);

    if(query.exec()) {
        while(query.next()) {
            int row = ui->tablePrescriptions->rowCount();
            ui->tablePrescriptions->insertRow(row);

            // Col 0 : Date
            ui->tablePrescriptions->setItem(row, 0, new QTableWidgetItem(query.value(0).toDate().toString("dd/MM/yyyy")));

            // Col 1 : Médecin
            ui->tablePrescriptions->setItem(row, 1, new QTableWidgetItem("Dr. " + query.value(1).toString()));

            // Col 2 : Détails Médicament
            ui->tablePrescriptions->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));

            // Col 3 : BOUTON ACTION "IMPRIMER"
            QTableWidgetItem *printItem = new QTableWidgetItem("🖨️ Imprimer");
            printItem->setTextAlignment(Qt::AlignCenter);
            // On le met en bleu et en gras pour qu'il ressemble à un lien
            printItem->setForeground(QBrush(QColor("#2d7aed")));
            printItem->setFont(QFont("Segoe UI", 9, QFont::Bold));

            ui->tablePrescriptions->setItem(row, 3, printItem);
        }
    } else {
        qDebug() << "Erreur SQL Prescriptions :" << query.lastError().text();
    }
}

void PagePatientPrescriptions::on_tablePrescriptions_cellClicked(int row, int column)
{
    // Si l'utilisateur clique sur la 4ème colonne (index 3), c'est le bouton "Imprimer"
    if (column == 3) {
        printPrescription(row);
    }
}

void PagePatientPrescriptions::printPrescription(int row)
{
    // 1. Récupérer les informations
    QString date = ui->tablePrescriptions->item(row, 0)->text();
    QString medecin = ui->tablePrescriptions->item(row, 1)->text();
    QString details = ui->tablePrescriptions->item(row, 2)->text();

    // 2. Créer le HTML avec des tailles en POINTS (pt) pour l'impression
    // J'ai augmenté toutes les tailles : 12pt (standard papier) à 24pt (titres)
    QString htmlContent = R"(
        <div style='font-family: Arial, sans-serif; padding: 50px;'>

            <div style='text-align: center; margin-bottom: 40px;'>
                <h1 style='color: #2d7aed; margin: 0; font-size: 28pt;'>ORDONNANCE MÉDICALE</h1>
                <p style='color: #555; font-size: 14pt; margin-top: 10px;'>Hôpital Manager - Service de Santé</p>
            </div>

            <hr style='border: 2px solid #ccc;' />

            <table style='width: 100%; margin-top: 30px; font-size: 16pt;'>
                <tr>
                    <td style='font-weight: bold; padding-bottom: 10px;'>Date :</td>
                    <td style='padding-bottom: 10px;'>%1</td>
                </tr>
                <tr>
                    <td style='font-weight: bold;'>Médecin :</td>
                    <td>%2</td>
                </tr>
            </table>

            <br><br>

            <div style='border: 2px solid #2d7aed; padding: 30px; border-radius: 10px; background-color: #fcfcfc;'>
                <h3 style='color: #333; margin-top: 0; font-size: 18pt; text-decoration: underline;'>Prescription :</h3>
                <p style='font-size: 16pt; line-height: 2.0;'>%3</p>
            </div>

            <br><br><br><br><br>

            <div style='text-align: right; margin-right: 50px;'>
                <p style='font-size: 14pt;'><i>Signature :</i></p>
                <br><br><br>
                <p style='font-size: 14pt;'>___________________</p>
            </div>

            <div style='position: absolute; bottom: 20px; width: 100%; text-align: center; font-size: 10pt; color: #999;'>
                <hr>
                Document généré électroniquement - Valide pour délivrance.
            </div>
        </div>
    )";

    htmlContent = htmlContent.arg(date, medecin, details);

    QTextDocument document;
    document.setHtml(htmlContent);

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPageSize::A4);

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Imprimer l'ordonnance");

    if (dialog.exec() == QDialog::Accepted) {
        document.print(&printer);
    }
}
