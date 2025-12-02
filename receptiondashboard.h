#ifndef RECEPTIONDASHBOARD_H
#define RECEPTIONDASHBOARD_H

#include <QMainWindow>
#include "pagepatients.h"
#include "pagerdv.h"
#include "pageadmissions.h"

namespace Ui {
class ReceptionDashboard;
}

class ReceptionDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReceptionDashboard(QWidget *parent = nullptr);
    ~ReceptionDashboard();

private slots:
    void on_btn_nav_dashboard_clicked();
    void on_btn_nav_patients_clicked();
    void on_btn_nav_rdv_clicked();
    void on_btn_nav_admissions_clicked();
    void on_btn_logout_clicked();

private:
    Ui::ReceptionDashboard *ui;
    PagePatients *pagePatients;
    PageRDV *pageRDV;
    PageAdmissions *pageAdmissions;

    void refreshAgenda(); // <--- AJOUTER
};

#endif // RECEPTIONDASHBOARD_H
