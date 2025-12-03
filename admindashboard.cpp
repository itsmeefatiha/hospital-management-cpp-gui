#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "loginwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QPixmap>
#include <QDir> // <--- Ajout pour le diagnostic de chemin
#include <QFile> // <--- Ajout pour vérifier l'existence du fichier

AdminDashboard::AdminDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);

    // --- DIAGNOSTIC DE CHEMIN D'IMAGE ---
    QString imagePath = ":/resources/medicine.png";
    qDebug() << "--- DIAGNOSTIC IMAGE ---";
    qDebug() << "Dossier d'exécution de l'app :" << QDir::currentPath();
    qDebug() << "Chemin complet attendu :" << QDir::current().absoluteFilePath(imagePath);

    if (!QFile::exists(imagePath)) {
        qDebug() << "ERREUR CRITIQUE : Le fichier n'existe pas à cet emplacement !";
        qDebug() << "SOLUTION : Copiez le dossier 'resources' dans le dossier 'build-...'";
    }
    // ------------------------------------

    // --- 2. AJOUT DU LOGO DANS LA SIDEBAR ---
    QPixmap logo(imagePath);

    if (!logo.isNull()) {
        ui->label_app_name->setPixmap(logo.scaledToWidth(50, Qt::SmoothTransformation));
        ui->label_app_name->setAlignment(Qt::AlignCenter);
    } else {
        // Fallback
        qDebug() << "Erreur : Chargement de l'image échoué.";
        ui->label_app_name->setText("Hôpital Manager");
    }
    // ----------------------------------------

    // Initialisation des pages
    pageUsers = new PageUsers();
    pageServices = new PageServices();
    pageRooms = new PageRooms();

    ui->stackedWidget->addWidget(pageUsers);
    ui->stackedWidget->addWidget(pageServices);
    ui->stackedWidget->addWidget(pageRooms);

    ui->stackedWidget->setCurrentIndex(0);

    // Charger les données du Dashboard au démarrage
    refreshStats();
    loadRecentActivity();
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::refreshStats()
{
    QSqlQuery query;

    // 1. Total Utilisateurs
    if(query.exec("SELECT COUNT(*) FROM utilisateurs")) {
        if(query.next()) {
            ui->label_s1_v->setText(query.value(0).toString());
        }
    }

    // 2. Taux d'Occupation ((Chambres occupées / Total) * 100)
    int totalRooms = 0;
    int occupiedRooms = 0;

    // Compter total
    if(query.exec("SELECT COUNT(*) FROM chambres")) {
        if(query.next()) totalRooms = query.value(0).toInt();
    }
    // Compter occupées (est_disponible = false)
    if(query.exec("SELECT COUNT(*) FROM chambres WHERE est_disponible = false")) {
        if(query.next()) occupiedRooms = query.value(0).toInt();
    }

    if(totalRooms > 0) {
        int rate = (occupiedRooms * 100) / totalRooms;
        ui->label_s2_v->setText(QString::number(rate) + "%");
    } else {
        ui->label_s2_v->setText("0%");
    }

    // 3. Médecins Actifs
    if(query.exec("SELECT COUNT(*) FROM medecins")) {
        if(query.next()) {
            ui->label_s3_v->setText(query.value(0).toString());
        }
    }
}

void AdminDashboard::loadRecentActivity()
{
    // Affiche les 5 derniers RDV planifiés
    ui->tableWidget_appointments->setRowCount(0);

    QSqlQuery query;
    // Jointure pour avoir les noms
    QString sql = "SELECT p.nom || ' ' || p.prenom, "
                  "m.nom || ' ' || m.prenom, "
                  "s.nom_service, "
                  "r.date_heure "
                  "FROM rendez_vous r "
                  "JOIN utilisateurs p ON r.id_patient = p.id_user "
                  "JOIN utilisateurs m ON r.id_medecin = m.id_user "
                  "JOIN medecins med ON m.id_user = med.id_medecin "
                  "JOIN services s ON med.id_service = s.id_service "
                  "ORDER BY r.date_heure DESC LIMIT 5";

    if(query.exec(sql)) {
        while(query.next()) {
            int row = ui->tableWidget_appointments->rowCount();
            ui->tableWidget_appointments->insertRow(row);

            ui->tableWidget_appointments->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // Patient
            ui->tableWidget_appointments->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Médecin
            ui->tableWidget_appointments->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Service
            ui->tableWidget_appointments->setItem(row, 3, new QTableWidgetItem(query.value(3).toDateTime().toString("dd/MM/yyyy HH:mm"))); // Date
        }
    }
}

// --- Navigation ---
void AdminDashboard::on_btn_menu_dashboard_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    refreshStats();
    ui->btn_menu_dashboard->setChecked(true); ui->btn_menu_users->setChecked(false);
    ui->btn_menu_services->setChecked(false); ui->btn_menu_rooms->setChecked(false);
}

void AdminDashboard::on_btn_menu_users_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    pageUsers->refresh();
    ui->btn_menu_dashboard->setChecked(false); ui->btn_menu_users->setChecked(true);
    ui->btn_menu_services->setChecked(false); ui->btn_menu_rooms->setChecked(false);
}

void AdminDashboard::on_btn_menu_services_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
    pageServices->refresh();
    ui->btn_menu_dashboard->setChecked(false); ui->btn_menu_users->setChecked(false);
    ui->btn_menu_services->setChecked(true); ui->btn_menu_rooms->setChecked(false);
}

void AdminDashboard::on_btn_menu_rooms_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
    pageRooms->refresh();
    ui->btn_menu_dashboard->setChecked(false); ui->btn_menu_users->setChecked(false);
    ui->btn_menu_services->setChecked(false); ui->btn_menu_rooms->setChecked(true);
}

void AdminDashboard::on_btn_logout_clicked() {
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}
