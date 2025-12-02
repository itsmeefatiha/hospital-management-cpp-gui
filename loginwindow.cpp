#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "database.h"  // Votre classe de connexion
#include <QMessageBox>
#include <QSqlQuery>   // Pour exécuter les requêtes SQL
#include <QSqlError>
#include <QDebug>
#include "admindashboard.h"
#include "receptiondashboard.h"
#include "doctordashboard.h"
#include "patientdashboard.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // On tente de connecter la BDD dès le démarrage de la fenêtre
    Database::connect();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btn_login_clicked()
{
    QString login = ui->lineEdit_email->text(); // On utilise ce champ comme "Login"
    QString password = ui->lineEdit_password->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // 1. Préparation de la requête
    QSqlQuery query;
    // On cherche le rôle correspondant au login ET mot de passe
    query.prepare("SELECT role, id_user FROM utilisateurs WHERE login = :login AND mot_de_passe = :pass");
    query.bindValue(":login", login);
    query.bindValue(":pass", password);

    // 2. Exécution
    if (query.exec()) {
        if (query.next()) {
            // --- Connexion Réussie ---
            QString role = query.value(0).toString(); // On récupère la colonne "role"
            int userId = query.value(1).toInt();
            qDebug() << "Utilisateur connecté avec le rôle :" << role;

            // 3. Redirection selon le rôle
            if (role == "ADMIN") {
                AdminDashboard *w = new AdminDashboard();
                w->show();
                this->close();
            }
            else if (role == "RECEPTIONNISTE") {
                ReceptionDashboard *w = new ReceptionDashboard();
                w->show();
                this->close();
            }
            else if (role == "MEDECIN") {
                DoctorDashboard *w = new DoctorDashboard(userId);
                w->show();
                this->close();
            }
            else if (role == "PATIENT") {
                // On passe l'ID au constructeur
                PatientDashboard *w = new PatientDashboard(userId);
                w->show();
                this->close();
            }
            else {
                QMessageBox::critical(this, "Erreur", "Rôle utilisateur inconnu.");
            }
        }
        else {
            // --- Échec (Pas de résultat) ---
            QMessageBox::warning(this, "Erreur", "Identifiant ou mot de passe incorrect.");
        }
    }
    else {
        // --- Erreur technique SQL ---
        QMessageBox::critical(this, "Erreur BDD", query.lastError().text());
    }
}
