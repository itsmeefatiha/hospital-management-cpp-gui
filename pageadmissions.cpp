#include "pageadmissions.h"
#include "ui_pageadmissions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QSqlDatabase>
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDateEdit>
PageAdmissions::PageAdmissions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAdmissions)
{
    ui->setupUi(this);
    ui->dateEdit_entry->setDate(QDate::currentDate());

    // CONFIGURATION TABLEAU : 4 Colonnes
    ui->tableAdmissions->setColumnCount(4);
    ui->tableAdmissions->setHorizontalHeaderLabels({"Chambre", "Patient", "Entrée le", "Action"});
    ui->tableAdmissions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // CONNEXION DU CLIC
    connect(ui->tableAdmissions, &QTableWidget::cellClicked,
            this, &PageAdmissions::on_tableAdmissions_cellClicked);

    refresh();
}

PageAdmissions::~PageAdmissions()
{
    delete ui;
}

void PageAdmissions::refresh()
{
    // 1. Charger les chambres libres
    ui->combo_room->clear();
    QSqlQuery query;
    if(query.exec("SELECT id_chambre, numero, type_chambre FROM chambres WHERE est_disponible = true ORDER BY numero")) {
        while(query.next()) {
            QString id = query.value(0).toString();
            QString label = "Chambre " + query.value(1).toString() + " (" + query.value(2).toString() + ")";
            ui->combo_room->addItem(label, id);
        }
    }

    // 2. Charger le tableau
    loadActiveAdmissions();
}

void PageAdmissions::loadActiveAdmissions()
{
    ui->tableAdmissions->setRowCount(0);

    QSqlQuery q;
    // On sélectionne UNIQUEMENT ceux qui n'ont pas de date de sortie (IS NULL)
    QString sql = "SELECT c.numero, p.nom || ' ' || p.prenom, h.date_entree, h.id_hosp, c.id_chambre "
                  "FROM hospitalisations h "
                  "JOIN chambres c ON h.id_chambre = c.id_chambre "
                  "JOIN utilisateurs p ON h.id_patient = p.id_user "
                  "WHERE h.date_sortie IS NULL "  // <--- C'EST CETTE LIGNE QUI FILTRE LES PRÉSENTS
                  "ORDER BY h.date_entree DESC";

    if(q.exec(sql)) {
        while(q.next()) {
            int row = ui->tableAdmissions->rowCount();
            ui->tableAdmissions->insertRow(row);

            // Récupération des IDs
            int idHospitalisation = q.value(3).toInt();
            int idChambre = q.value(4).toInt();

            // Col 0 : Chambre
            QTableWidgetItem *roomItem = new QTableWidgetItem("Chambre " + q.value(0).toString());
            roomItem->setData(Qt::UserRole, idHospitalisation);
            roomItem->setData(Qt::UserRole + 1, idChambre);
            ui->tableAdmissions->setItem(row, 0, roomItem);

            // Col 1 : Patient
            ui->tableAdmissions->setItem(row, 1, new QTableWidgetItem(q.value(1).toString()));

            // Col 2 : Date Entrée
            ui->tableAdmissions->setItem(row, 2, new QTableWidgetItem(q.value(2).toDate().toString("dd/MM/yyyy")));

            // Col 3 : Action
            QTableWidgetItem *actionItem = new QTableWidgetItem("❌ Sortie");
            actionItem->setTextAlignment(Qt::AlignCenter);
            actionItem->setForeground(QBrush(QColor("#d9534f"))); // Rouge
            actionItem->setFont(QFont("Segoe UI", 9, QFont::Bold));
            ui->tableAdmissions->setItem(row, 3, actionItem);
        }
    } else {
        QMessageBox::critical(this, "Erreur SQL", q.lastError().text());
    }
}

// --- CLIC SUR LE TABLEAU ---
void PageAdmissions::on_tableAdmissions_cellClicked(int row, int column)
{
    if (column == 3) { // Colonne Action
        QTableWidgetItem *item = ui->tableAdmissions->item(row, 0);
        int admissionId = item->data(Qt::UserRole).toInt();
        int roomId = item->data(Qt::UserRole + 1).toInt();

        // --- REMPLACEMENT DE QInputDialog::getDate ---
        QDialog dialog(this);
        dialog.setWindowTitle("Date de Sortie");

        QFormLayout form(&dialog);
        QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
        dateEdit->setCalendarPopup(true);
        form.addRow("Date de sortie :", dateEdit);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);

        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        // Si l'utilisateur clique sur OK
        if (dialog.exec() == QDialog::Accepted) {
            dischargePatient(admissionId, roomId, dateEdit->date());
        }
    }
}

// --- LOGIQUE DE SORTIE ---
void PageAdmissions::dischargePatient(int admissionId, int roomId, QDate exitDate)
{
    QSqlDatabase::database().transaction();
    bool success = false;

    // A. Mettre à jour la date de sortie
    QSqlQuery qUp;
    qUp.prepare("UPDATE hospitalisations SET date_sortie = :d WHERE id_hosp = :id");
    qUp.bindValue(":d", exitDate);
    qUp.bindValue(":id", admissionId);

    if (qUp.exec()) {
        // B. Libérer la chambre
        QSqlQuery qRoom;
        qRoom.prepare("UPDATE chambres SET est_disponible = true WHERE id_chambre = :id");
        qRoom.bindValue(":id", roomId);

        if (qRoom.exec()) success = true;
    }

    if (success) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "Succès", "Sortie enregistrée au " + exitDate.toString("dd/MM/yyyy"));
        refresh(); // La ligne disparaitra du tableau car le patient est sorti
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la sortie.");
    }
}

// --- FONCTION D'AJOUT (Votre code original corrigé) ---
void PageAdmissions::on_btn_save_clicked()
{
    QString patientName = ui->lineEdit_patient->text().trimmed();
    if (patientName.isEmpty()) return;

    QSqlQuery findPat;
    findPat.prepare("SELECT id_user FROM utilisateurs WHERE role='PATIENT' AND (nom || ' ' || prenom ILIKE :n OR prenom || ' ' || nom ILIKE :n) LIMIT 1");
    findPat.bindValue(":n", "%" + patientName + "%");

    if(!findPat.exec() || !findPat.next()) {
        QMessageBox::warning(this, "Erreur", "Patient introuvable.");
        return;
    }
    int patientId = findPat.value(0).toInt();

    if(ui->combo_room->count() == 0) {
        QMessageBox::warning(this, "Erreur", "Pas de chambre !");
        return;
    }
    int roomId = ui->combo_room->currentData().toInt();
    QDate dateEntree = ui->dateEdit_entry->date();

    QSqlDatabase::database().transaction();

    QSqlQuery qAdm;
    qAdm.prepare("INSERT INTO hospitalisations (date_entree, id_patient, id_chambre, motif) VALUES (:d, :p, :c, 'Admission')");
    qAdm.bindValue(":d", dateEntree);
    qAdm.bindValue(":p", patientId);
    qAdm.bindValue(":c", roomId);
    bool ok1 = qAdm.exec();

    QSqlQuery qRoom;
    qRoom.prepare("UPDATE chambres SET est_disponible = false WHERE id_chambre = :id");
    qRoom.bindValue(":id", roomId);
    bool ok2 = qRoom.exec();

    if(ok1 && ok2) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this, "Succès", "Admission enregistrée.");
        refresh();
        ui->lineEdit_patient->clear();
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Erreur", qAdm.lastError().text());
    }
}
