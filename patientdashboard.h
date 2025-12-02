#ifndef PATIENTDASHBOARD_H
#define PATIENTDASHBOARD_H

#include <QMainWindow>
// Inclusions des pages
#include "pagepatientappointments.h"
#include "pagepatientrecord.h"
#include "pagepatientprescriptions.h"

namespace Ui {
class PatientDashboard;
}

class PatientDashboard : public QMainWindow
{
    Q_OBJECT

public:
    // Constructeur modifié pour accepter l'ID
    explicit PatientDashboard(int patientId, QWidget *parent = nullptr);
    ~PatientDashboard();

private slots:
    void on_btn_home_clicked();
    void on_btn_rdv_clicked();
    void on_btn_record_clicked();
    void on_btn_presc_clicked();
    void on_btn_logout_clicked();

private:
    Ui::PatientDashboard *ui;

    int currentPatientId; // L'ID de l'utilisateur connecté

    // Pointeurs vers les pages
    PagePatientAppointments *pageRdv;
    PagePatientRecord *pageRecord;
    PagePatientPrescriptions *pagePresc;

    void loadHomeSummary(); // Pour afficher le prochain RDV sur l'accueil
};

#endif // PATIENTDASHBOARD_H
