#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "database.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPixmap> // <--- 1. IMPORTANT : Inclure QPixmap
#include "admindashboard.h"
#include "receptiondashboard.h"
#include "doctordashboard.h"
#include "patientdashboard.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // --- 2. CODE AJOUTÉ POUR L'IMAGE ---
    // Assurez-vous que le dossier "resources" est bien dans le dossier de compilation (build)
    // Ou utilisez un fichier de ressources Qt (.qrc) et le chemin ":/resources/hospital_bg.png"
    QPixmap pix(":/resources/hospital_bg.png");

    // Vérification optionnelle pour voir si l'image est bien chargée
    if (!pix.isNull()) {
        ui->label_image->setPixmap(pix);
        ui->label_image->setScaledContents(true); // Pour que l'image s'adapte à la taille du label
    } else {
        qDebug() << "Erreur : Impossible de trouver l'image 'resources/hospital_bg.png'";
    }
    // -----------------------------------

    // On tente de connecter la BDD dès le démarrage de la fenêtre
    Database::connect();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btn_login_clicked()
{
    QString login = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT role, id_user FROM utilisateurs WHERE login = :login AND mot_de_passe = :pass");
    query.bindValue(":login", login);
    query.bindValue(":pass", password);

    if (query.exec()) {
        if (query.next()) {
            QString role = query.value(0).toString();
            int userId = query.value(1).toInt();
            qDebug() << "Utilisateur connecté avec le rôle :" << role;

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
                PatientDashboard *w = new PatientDashboard(userId);
                w->show();
                this->close();
            }
            else {
                QMessageBox::critical(this, "Erreur", "Rôle utilisateur inconnu.");
            }
        }
        else {
            QMessageBox::warning(this, "Erreur", "Identifiant ou mot de passe incorrect.");
        }
    }
    else {
        QMessageBox::critical(this, "Erreur BDD", query.lastError().text());
    }
}
