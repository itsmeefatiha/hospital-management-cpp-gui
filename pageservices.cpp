#include "pageservices.h"
#include "ui_pageservices.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog> // Pour demander le nom du nouveau service
#include <QMessageBox>
#include <QComboBox>

PageServices::PageServices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageServices)
{
    ui->setupUi(this);
    refresh();
}

PageServices::~PageServices()
{
    delete ui;
}

void PageServices::refresh()
{
    ui->listWidget_services->clear();

    QSqlQuery query;
    if(query.exec("SELECT nom_service FROM services")) {
        while(query.next()) {
            ui->listWidget_services->addItem(query.value(0).toString());
        }
    }
}

// Quand on clique sur un service dans la liste de gauche
void PageServices::on_listWidget_services_itemClicked(QListWidgetItem *item)
{
    QString serviceName = item->text();
    ui->lbl_details_title->setText("Service : " + serviceName);
    ui->listWidget_assigned_docs->clear();

    QSqlQuery query;
    query.prepare("SELECT u.nom || ' ' || u.prenom "
                  "FROM medecins m "
                  "JOIN utilisateurs u ON m.id_medecin = u.id_user "
                  "JOIN services s ON m.id_service = s.id_service "
                  "WHERE s.nom_service = :service");
    query.bindValue(":service", serviceName);

    if(query.exec()) {
        while(query.next()) {
            ui->listWidget_assigned_docs->addItem("Dr. " + query.value(0).toString());
        }
    }
}

void PageServices::on_btn_add_service_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Nouveau Service",
                                         "Nom du service :", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO services (nom_service, description) VALUES (:nom, 'Description par défaut')");
        query.bindValue(":nom", text);

        if(query.exec()) {
            refresh();
        } else {
            QMessageBox::critical(this, "Erreur", query.lastError().text());
        }
    }
}

void PageServices::on_btn_assign_doc_clicked()
{
    // 1. Vérifier la sélection
    QListWidgetItem *currentItem = ui->listWidget_services->currentItem();
    if(currentItem == nullptr) {
        QMessageBox::warning(this, "Attention", "Veuillez d'abord sélectionner un service dans la liste de gauche.");
        return;
    }

    QString currentService = currentItem->text();

    // 2. Récupérer la liste des médecins depuis la table UTILISATEURS
    QSqlQuery query;
    QStringList doctorsList;

    if(query.exec("SELECT id_user, nom || ' ' || prenom FROM utilisateurs WHERE role = 'MEDECIN'")) {
        while(query.next()) {
            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            doctorsList << name + " (ID: " + id + ")";
        }
    }

    if(doctorsList.isEmpty()) {
        QMessageBox::information(this, "Info", "Aucun médecin trouvé dans la base.");
        return;
    }

    // 3. Dialogue de choix
    bool ok;
    QString selectedDoc = QInputDialog::getItem(this, "Affecter un médecin",
                                                "Choisir un médecin pour : " + currentService,
                                                doctorsList, 0, false, &ok);

    if (ok && !selectedDoc.isEmpty()) {
        // 4. Extraction ID
        QString idStr = selectedDoc.split("ID: ").last().replace(")", "");
        int doctorId = idStr.toInt();

        // 5. MISE À JOUR INTELLIGENTE (UPSERT)
        // On récupère d'abord l'ID du service
        QSqlQuery qService;
        qService.prepare("SELECT id_service FROM services WHERE nom_service = :name");
        qService.bindValue(":name", currentService);

        if(qService.exec() && qService.next()) {
            int idService = qService.value(0).toInt();

            QSqlQuery upsertQuery;
            // Cette requête dit : "Insère le médecin. S'il existe déjà (conflit sur l'ID), mets juste à jour son service."
            upsertQuery.prepare("INSERT INTO medecins (id_medecin, id_service, specialite) "
                                "VALUES (:id, :sid, 'Généraliste') "
                                "ON CONFLICT (id_medecin) "
                                "DO UPDATE SET id_service = :sid");

            upsertQuery.bindValue(":id", doctorId);
            upsertQuery.bindValue(":sid", idService);

            if(upsertQuery.exec()) {
                QMessageBox::information(this, "Succès", "Médecin affecté et dossier créé !");
                // Rafraîchir l'affichage
                on_listWidget_services_itemClicked(currentItem);
            } else {
                QMessageBox::critical(this, "Erreur SQL", upsertQuery.lastError().text());
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Service introuvable en base.");
        }
    }
}
