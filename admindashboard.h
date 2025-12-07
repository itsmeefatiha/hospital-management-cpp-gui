#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
// Inclusions des pages
#include "pageusers.h"
#include "pageservices.h"
#include "pagerooms.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtCharts>

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

private slots:
    // Slots des boutons du menu
    void on_btn_menu_dashboard_clicked();
    void on_btn_menu_users_clicked();
    void on_btn_menu_services_clicked();
    void on_btn_menu_rooms_clicked();
    void on_btn_logout_clicked();

private:
    Ui::AdminDashboard *ui;

    // Pointeurs vers les sous-pages
    PageUsers *pageUsers;
    PageServices *pageServices;
    PageRooms *pageRooms;

    // --- FONCTIONS MANQUANTES ---
    void refreshStats();       // <--- AJOUTÉ
    void loadRecentActivity(); // <--- AJOUTÉ
    void setupChart();
    void setupDoughnutChart();  // <--- AJOUTER CETTE LIGNE
};

#endif // ADMINDASHBOARD_H
