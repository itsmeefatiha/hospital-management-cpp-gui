#include "pagepatients.h"
#include "ui_pagepatients.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

PagePatients::PagePatients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagePatients)
{
    ui->setupUi(this);
    connect(ui->lineEdit_search, &QLineEdit::returnPressed, this, &PagePatients::on_btn_search_clicked);

    // Connecte le changement de texte à notre nouvelle fonction
    connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &PagePatients::on_search_text_changed);

    refresh();
}

PagePatients::~PagePatients()
{
    delete ui;
}

void PagePatients::refresh()
{
    ui->listWidget_patients->clear();
    QSqlQuery query;
    // On affiche Nom + Date de naissance pour distinguer les homonymes
    if(query.exec("SELECT u.nom || ' ' || u.prenom || ' (' || p.date_naissance || ')' "
                   "FROM patients p JOIN utilisateurs u ON p.id_patient = u.id_user")) {
        while(query.next()) {
            ui->listWidget_patients->addItem(query.value(0).toString());
        }
    }
}

void PagePatients::on_btn_save_clicked() // Bouton Enregistrer
{
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QDate dob = ui->dateEdit_dob->date();
    QString tel = ui->lineEdit_tel->text();
    QString addr = ui->lineEdit_addr->text();

    if(nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom et Prénom obligatoires.");
        return;
    }

    // Génération automatique d'un login/pass pour le patient
    QString login = nom.toLower() + "." + prenom.toLower();
    QString password = "1234";

    // TRANSACTION : On doit insérer dans 2 tables. Si l'une échoue, on annule tout.
    QSqlDatabase::database().transaction();

    QSqlQuery qUser;
    qUser.prepare("INSERT INTO utilisateurs (nom, prenom, login, mot_de_passe, role) "
                  "VALUES (:n, :p, :l, :pw, 'PATIENT') RETURNING id_user");
    qUser.bindValue(":n", nom);
    qUser.bindValue(":p", prenom);
    qUser.bindValue(":l", login);
    qUser.bindValue(":pw", password);

    if(qUser.exec() && qUser.next()) {
        int newId = qUser.value(0).toInt(); // On récupère l'ID créé

        QSqlQuery qPatient;
        qPatient.prepare("INSERT INTO patients (id_patient, date_naissance, adresse, telephone) "
                         "VALUES (:id, :dob, :addr, :tel)");
        qPatient.bindValue(":id", newId);
        qPatient.bindValue(":dob", dob);
        qPatient.bindValue(":addr", addr);
        qPatient.bindValue(":tel", tel);

        if(qPatient.exec()) {
            // Création du dossier médical vide aussi !
            QSqlQuery qDossier;
            qDossier.prepare("INSERT INTO dossiers_medicaux (id_patient) VALUES (:id)");
            qDossier.bindValue(":id", newId);
            qDossier.exec();

            QSqlDatabase::database().commit(); // Tout est bon, on valide
            QMessageBox::information(this, "Succès", "Patient créé avec succès.\nLogin généré: " + login);
            refresh();

            // Reset champs
            ui->lineEdit_nom->clear(); ui->lineEdit_prenom->clear(); ui->lineEdit_tel->clear(); ui->lineEdit_addr->clear();
        } else {
            QSqlDatabase::database().rollback(); // Erreur patient -> on annule user
            QMessageBox::critical(this, "Erreur", "Erreur insertion Patient: " + qPatient.lastError().text());
        }
    } else {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Erreur", "Erreur insertion User (Login existe déjà ?): " + qUser.lastError().text());
    }
}

void PagePatients::on_btn_new_clicked() {
    // Vider le formulaire
    ui->lineEdit_nom->clear(); ui->lineEdit_prenom->clear();
    ui->lineEdit_tel->clear(); ui->lineEdit_addr->clear();
    ui->dateEdit_dob->setDate(QDate(2000, 1, 1));
}
void PagePatients::on_btn_search_clicked()
{
    QString searchText = ui->lineEdit_search->text().trimmed();

    qDebug() << "--- DÉBUT RECHERCHE ---";
    qDebug() << "Texte saisi :" << searchText;

    // Si vide, on rafraichit tout
    if (searchText.isEmpty()) {
        qDebug() << "Champ vide -> Refresh complet";
        refresh();
        return;
    }

    ui->listWidget_patients->clear();

    QSqlQuery query;
    // On utilise ILIKE pour PostgreSQL (insensible à la casse)
    // Assurez-vous que la jointure est correcte : un patient DOIT être dans la table 'patients' ET 'utilisateurs'
    QString sql = "SELECT u.nom || ' ' || u.prenom || ' (' || p.date_naissance || ')' "
                  "FROM patients p "
                  "JOIN utilisateurs u ON p.id_patient = u.id_user "
                  "WHERE u.nom ILIKE :search OR u.prenom ILIKE :search";

    query.prepare(sql);
    QString pattern = "%" + searchText + "%";
    query.bindValue(":search", pattern);

    qDebug() << "Pattern SQL :" << pattern;

    if (query.exec()) {
        int count = 0;
        while(query.next()) {
            ui->listWidget_patients->addItem(query.value(0).toString());
            count++;
        }
        qDebug() << "Résultats trouvés :" << count;

        if (count == 0) {
            // Optionnel : Afficher un petit item pour dire "Aucun résultat"
            ui->listWidget_patients->addItem("Aucun patient trouvé pour : " + searchText);
        }
    } else {
        qDebug() << "ERREUR SQL CRITIQUE :" << query.lastError().text();
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
    }

    qDebug() << "--- FIN RECHERCHE ---";
}
void PagePatients::on_search_text_changed(const QString &arg1)
{
    // arg1 contient le texte actuel du champ
    // .trimmed() enlève les espaces inutiles au début et à la fin
    if (arg1.trimmed().isEmpty()) {
        refresh(); // Si c'est vide, on réaffiche tout le monde !
    }
}
