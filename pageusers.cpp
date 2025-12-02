#include "pageusers.h"
#include "ui_pageusers.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

PageUsers::PageUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageUsers)
{
    ui->setupUi(this);
    refresh(); // Charger la liste au démarrage
}

PageUsers::~PageUsers()
{
    delete ui;
}

void PageUsers::refresh()
{
    // Vider le tableau
    ui->tableUsers->setRowCount(0);

    QSqlQuery query;
    // On récupère Nom, Login (Email) et Rôle
    if(query.exec("SELECT nom || ' ' || prenom, login, role FROM utilisateurs ORDER BY id_user DESC")) {
        while(query.next()) {
            int row = ui->tableUsers->rowCount();
            ui->tableUsers->insertRow(row);

            ui->tableUsers->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // Nom Complet
            ui->tableUsers->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Login
            ui->tableUsers->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Rôle
        }
    }
}

void PageUsers::on_btn_save_user_clicked()
{
    QString nameFull = ui->lineEdit_name->text();
    QString login = ui->lineEdit_email->text(); 
    QString pass = ui->lineEdit_password->text();
    
    // Récupération du texte affiché dans la combo box
    QString roleText = ui->combo_role->currentText(); 

    // --- CORRECTION DU RÔLE POUR LA BDD ---
    // On transforme l'affichage (ex: "Médecin") en valeur BDD (ex: "MEDECIN")
    QString dbRole;
    if (roleText.contains("Médecin") || roleText.contains("Medecin")) {
        dbRole = "MEDECIN";
    } else if (roleText.contains("Réceptionniste") || roleText.contains("Receptionniste")) {
        dbRole = "RECEPTIONNISTE";
    } else if (roleText.contains("Administrateur") || roleText.contains("Admin")) {
        dbRole = "ADMIN";
    } else {
        // Par sécurité, ou pour le cas "Patient" s'il est ajouté un jour
        dbRole = "PATIENT"; 
    }

    if(nameFull.isEmpty() || login.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires.");
        return;
    }

    // Gestion Nom / Prénom (Si un seul mot est saisi, on évite le vide)
    QString nom = nameFull.split(" ").first();
    QString prenom = nameFull.contains(" ") ? nameFull.split(" ").last() : "."; 

    QSqlQuery query;
    query.prepare("INSERT INTO utilisateurs (nom, prenom, login, mot_de_passe, role) "
                  "VALUES (:nom, :prenom, :login, :pass, :role)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":login", login);
    query.bindValue(":pass", pass);
    query.bindValue(":role", dbRole); // On utilise le rôle corrigé

    if(query.exec()) {
        QMessageBox::information(this, "Succès", "Utilisateur ajouté avec succès.");
        ui->lineEdit_name->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_password->clear();
        refresh(); // Recharge la liste
    } else {
        // Affiche l'erreur technique si ça échoue encore
        QMessageBox::critical(this, "Erreur", "Erreur SQL : " + query.lastError().text());
    }
}