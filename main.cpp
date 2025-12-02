#include "mainwindow.h"
#include "loginwindow.h"
#include "database.h"
#include "admindashboard.h"
#include "doctordashboard.h"
#include "receptiondashboard.h"
#include "patientdashboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(
        // 1. Fenêtres de dialogue (Message, Input)
        "QDialog, QMessageBox, QInputDialog { "
        "   background-color: white; "
        "   color: #333333; "
        "}"

        // 2. Textes et Labels
        "QDialog QLabel { "
        "   color: #333333; "
        "   font-size: 14px; "
        "}"

        // 3. Champs de saisie (Texte & Listes)
        "QDialog QLineEdit, QDialog QComboBox { "
        "   background-color: #f9f9f9; "
        "   color: #333333; "
        "   border: 1px solid #ccc; "
        "   border-radius: 4px; "
        "   padding: 6px; "
        "}"

        // 4. Menu déroulant des ComboBox (Popup)
        "QComboBox QAbstractItemView { "
        "   background-color: white; "
        "   color: #333333; "
        "   selection-background-color: #2d7aed; "
        "   selection-color: white; "
        "   border: 1px solid #ccc; "
        "}"

        // 5. Boutons
        "QDialog QPushButton { "
        "   background-color: #2d7aed; "
        "   color: white; "
        "   border: none; "
        "   border-radius: 4px; "
        "   padding: 8px 20px; "
        "   font-weight: bold; "
        "   min-width: 80px; "
        "}"
        "QDialog QPushButton:hover { background-color: #1a5fc7; }"
        "QDialog QPushButton:pressed { background-color: #154ba1; }"

        // -----------------------------------------------------------
        // 6. CORRECTION CALENDRIER (QDateEdit Popup)
        // -----------------------------------------------------------

        // Le conteneur global du calendrier
        "QCalendarWidget QWidget { "
        "   background-color: white; "
        "   color: #333333; "
        "}"

        // La grille des jours (C'est ici que les chiffres étaient invisibles)
        "QCalendarWidget QAbstractItemView:enabled { "
        "   color: #333333; "  /* Chiffres en noir */
        "   background-color: white; "
        "   selection-background-color: #2d7aed; "
        "   selection-color: white; "
        "}"

        // Les flèches de navigation et le mois/année
        "QCalendarWidget QToolButton { "
        "   color: #333333; "
        "   background-color: transparent; "
        "   icon-size: 20px; "
        "}"
        "QCalendarWidget QToolButton:hover { "
        "   background-color: #f0f2f5; "
        "   border-radius: 4px; "
        "}"

        // La barre de menu du calendrier (où il y a les flèches)
        "QCalendarWidget QWidget#qt_calendar_navigationbar { "
        "   background-color: white; "
        "   border-bottom: 1px solid #ccc; "
        "}"
        );
    Database::connect();  // 🔗 Connexion PostgreSQL
    LoginWindow login;
    login.show();
    //AdminDashboard w;
    //DoctorDashboard w;
    //ReceptionDashboard w;
    // PatientDashboard w;
    // w.show();
    return a.exec();
}
