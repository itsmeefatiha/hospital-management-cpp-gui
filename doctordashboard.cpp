#include "doctordashboard.h"
#include "ui_doctordashboard.h"
#include "loginwindow.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>

DoctorDashboard::DoctorDashboard(int doctorId,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DoctorDashboard)
    , currentDoctorId(doctorId)
{
    ui->setupUi(this);

    QSqlQuery qDoc;
    qDoc.prepare("SELECT u.nom, u.prenom, s.nom_service "
                 "FROM utilisateurs u "
                 "JOIN medecins m ON u.id_user = m.id_medecin "
                 "JOIN services s ON m.id_service = s.id_service "
                 "WHERE u.id_user = :id");
    qDoc.bindValue(":id", doctorId);

    if (qDoc.exec() && qDoc.next()) {
        QString nom = qDoc.value(0).toString();
        QString prenom = qDoc.value(1).toString();
        QString service = qDoc.value(2).toString();

        // On met à jour le label de la barre latérale
        ui->label_doctor_profile->setText("Dr. " + prenom + " " + nom + " (" + service + ")");
    }

    // Initialisation des pages externes
    pageSearch = new PagePatientSearch();
    pageMedical = new PageMedicalRecord();


    // Ajout au StackedWidget (L'agenda est déjà à l'index 0)
    ui->stackedWidget->addWidget(pageSearch);   // Index 1
    ui->stackedWidget->addWidget(pageMedical);  // Index 2


    // Par défaut : Agenda
    ui->stackedWidget->setCurrentIndex(0);
    connect(pageSearch, &PagePatientSearch::patientSelected, this, [=](int patientId){
        pageMedical->loadPatient(patientId, currentDoctorId); // On charge le dossier
        ui->stackedWidget->setCurrentIndex(2); // On affiche la page dossier
        ui->btn_menu_search->setChecked(false);
        ui->btn_menu_dossier->setChecked(true);
    });

    refreshAgenda();
}

DoctorDashboard::~DoctorDashboard()
{
    delete ui;
}

void DoctorDashboard::refreshAgenda()
{
    ui->table_appointments->setRowCount(0);

    // CORRECTION : On sélectionne aussi 'id_patient'
    // Note : On garde 'Consultation' comme motif statique puisque la colonne n'existe pas
    QString sql = QString("SELECT r.date_heure, p.nom || ' ' || p.prenom, 'Consultation', r.statut, p.id_user "
                          "FROM rendez_vous r "
                          "JOIN utilisateurs p ON r.id_patient = p.id_user "
                          "WHERE r.id_medecin = %1 AND CAST(r.date_heure AS DATE) >= CURRENT_DATE "
                          "ORDER BY r.date_heure").arg(currentDoctorId);

    QSqlQuery query;
    if(query.exec(sql)) {
        while(query.next()) {
            int row = ui->table_appointments->rowCount();
            ui->table_appointments->insertRow(row);

            // Récupération des données
            QString dateStr = query.value(0).toDateTime().toString("dd/MM HH:mm");
            QString patientName = query.value(1).toString();
            QString motif = query.value(2).toString();
            QString statut = query.value(3).toString();
            int patientId = query.value(4).toInt(); // L'ID du patient

            ui->table_appointments->setItem(row, 0, new QTableWidgetItem(dateStr));
            ui->table_appointments->setItem(row, 1, new QTableWidgetItem(patientName));
            ui->table_appointments->setItem(row, 2, new QTableWidgetItem(motif));
            ui->table_appointments->setItem(row, 3, new QTableWidgetItem(statut));

            // --- ASTUCE : Bouton "Voir" avec l'ID caché ---
            QTableWidgetItem *btnItem = new QTableWidgetItem("Voir Dossier");
            btnItem->setData(Qt::UserRole, patientId); // On cache l'ID dans l'item
            btnItem->setTextAlignment(Qt::AlignCenter);
            btnItem->setForeground(QBrush(QColor("#2d7aed"))); // Bleu lien
            btnItem->setFont(QFont("Segoe UI", 9, QFont::Bold));

            ui->table_appointments->setItem(row, 4, btnItem);
        }
    } else {
        qDebug() << "ERREUR SQL :" << query.lastError().text();
    }
}
void DoctorDashboard::on_btn_menu_agenda_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->btn_menu_agenda->setChecked(true);
    ui->btn_menu_search->setChecked(false);
    ui->btn_menu_dossier->setChecked(false);
}

void DoctorDashboard::on_btn_menu_search_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->btn_menu_agenda->setChecked(false);
    ui->btn_menu_search->setChecked(true);
    ui->btn_menu_dossier->setChecked(false);
}

void DoctorDashboard::on_btn_menu_dossier_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->btn_menu_agenda->setChecked(false);
    ui->btn_menu_search->setChecked(false);
    ui->btn_menu_dossier->setChecked(true);
}

void DoctorDashboard::on_btn_logout_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}
void DoctorDashboard::on_table_appointments_cellClicked(int row, int column)
{
    // On vérifie si l'utilisateur a cliqué sur la dernière colonne (celle du bouton "Voir")
    // (Indices : 0=Heure, 1=Patient, 2=Motif, 3=Statut, 4=Action)
    if (column == 4) {
        // 1. Récupérer l'ID caché
        QTableWidgetItem *item = ui->table_appointments->item(row, column);
        int patientId = item->data(Qt::UserRole).toInt();

        qDebug() << "Ouverture dossier patient ID :" << patientId;

        // 2. Charger le dossier médical (via la page MedicalRecord)
        pageMedical->loadPatient(patientId, currentDoctorId);

        // 3. Basculer l'affichage sur l'onglet "Dossier Médical" (Index 2)
        ui->stackedWidget->setCurrentIndex(2);

        // 4. Mettre à jour le menu latéral (visuel)
        ui->btn_menu_agenda->setChecked(false);
        ui->btn_menu_search->setChecked(false);
        ui->btn_menu_dossier->setChecked(true);
    }
}
