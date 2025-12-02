#include "pageadmissions.h"
#include "ui_pageadmissions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>

PageAdmissions::PageAdmissions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAdmissions)
{
    ui->setupUi(this);
    ui->dateEdit_entry->setDate(QDate::currentDate());
    refresh();
}

PageAdmissions::~PageAdmissions()
{
    delete ui;
}

void PageAdmissions::refresh()
{
    // 1. Charger les chambres libres dans la Combo
    ui->combo_room->clear();
    QSqlQuery query;
    if(query.exec("SELECT id_chambre, numero, type_chambre FROM chambres WHERE est_disponible = true ORDER BY numero")) {
        while(query.next()) {
            QString id = query.value(0).toString();
            QString label = "Chambre " + query.value(1).toString() + " (" + query.value(2).toString() + ")";
            ui->combo_room->addItem(label, id);
        }
    }
    
    // 2. Charger le tableau des admissions
    loadActiveAdmissions();
}

// --- NOUVELLE FONCTION ---
void PageAdmissions::loadActiveAdmissions()
{
    ui->tableAdmissions->setRowCount(0);
    QSqlQuery q;
    // On cherche les hospitalisations sans date de sortie (donc en cours)
    QString sql = "SELECT c.numero, p.nom || ' ' || p.prenom, h.date_entree "
                  "FROM hospitalisations h "
                  "JOIN chambres c ON h.id_chambre = c.id_chambre "
                  "JOIN utilisateurs p ON h.id_patient = p.id_user "
                  "WHERE h.date_sortie IS NULL "
                  "ORDER BY h.date_entree DESC";
                  
    if(q.exec(sql)) {
        while(q.next()) {
            int row = ui->tableAdmissions->rowCount();
            ui->tableAdmissions->insertRow(row);
            
            ui->tableAdmissions->setItem(row, 0, new QTableWidgetItem("Chambre " + q.value(0).toString()));
            ui->tableAdmissions->setItem(row, 1, new QTableWidgetItem(q.value(1).toString()));
            ui->tableAdmissions->setItem(row, 2, new QTableWidgetItem(q.value(2).toDate().toString("dd/MM/yyyy")));
        }
    }
}

void PageAdmissions::on_btn_save_clicked()
{
    // On utilise .trimmed() pour enlever les espaces inutiles au début/fin
    QString patientName = ui->lineEdit_patient->text().trimmed();

    if (patientName.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un nom de patient.");
        return;
    }

    // 1. Trouver le patient (Correction : Recherche intelligente Nom + Prénom)
    QSqlQuery findPat;
    // Cette requête concatène (colle) nom et prénom pour la recherche
    findPat.prepare("SELECT id_user FROM utilisateurs "
                    "WHERE role='PATIENT' "
                    "AND (nom || ' ' || prenom ILIKE :n "   // Cherche "Nom Prénom" (ex: Dupont Jean)
                    "OR prenom || ' ' || nom ILIKE :n "     // Cherche "Prénom Nom" (ex: Jean Dupont)
                    "OR nom ILIKE :n OR prenom ILIKE :n) "  // Cherche juste le nom ou le prénom
                    "LIMIT 1");

    findPat.bindValue(":n", "%" + patientName + "%");

    if(!findPat.exec() || !findPat.next()) {
        QMessageBox::warning(this, "Erreur", "Patient introuvable. Vérifiez l'orthographe.");
        return;
    }
    int patientId = findPat.value(0).toInt();

    // 2. Vérifier s'il y a une chambre sélectionnée
    if(ui->combo_room->count() == 0) {
        QMessageBox::warning(this, "Erreur", "Aucune chambre disponible !");
        return;
    }
    int roomId = ui->combo_room->currentData().toInt();
    QDate dateEntree = ui->dateEdit_entry->date();

    // 3. Début de la Transaction (Tout ou rien)
    QSqlDatabase::database().transaction();

    // Étape A : Créer l'hospitalisation
    QSqlQuery qAdm;
    qAdm.prepare("INSERT INTO hospitalisations (date_entree, id_patient, id_chambre, motif) VALUES (:d, :p, :c, 'Admission')");
    qAdm.bindValue(":d", dateEntree);
    qAdm.bindValue(":p", patientId);
    qAdm.bindValue(":c", roomId);

    bool ok1 = qAdm.exec();

    // Étape B : Marquer la chambre comme occupée
    QSqlQuery qRoom;
    qRoom.prepare("UPDATE chambres SET est_disponible = false WHERE id_chambre = :id");
    qRoom.bindValue(":id", roomId);
    bool ok2 = qRoom.exec();

    // 4. Validation finale
    if(ok1 && ok2) {
        QSqlDatabase::database().commit(); // On valide les changements
        QMessageBox::information(this, "Succès", "Patient admis avec succès.");

        // --- MISE A JOUR AFFICHAGE ---
        refresh(); // Recharge la liste des chambres (la chambre prise va disparaitre) ET le tableau
        ui->lineEdit_patient->clear();
    } else {
        QSqlDatabase::database().rollback(); // On annule tout en cas d'erreur
        QMessageBox::critical(this, "Erreur", "Echec technique : " + qAdm.lastError().text());
    }
}
