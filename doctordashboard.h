#ifndef DOCTORDASHBOARD_H
#define DOCTORDASHBOARD_H

#include <QMainWindow>
#include "pagepatientsearch.h"
#include "pagemedicalrecord.h"

namespace Ui {
class DoctorDashboard;
}

class DoctorDashboard : public QMainWindow
{
    Q_OBJECT

public:
    // --- MODIFIEZ CETTE LIGNE ---
    // Ajoutez "int doctorId" au début
    explicit DoctorDashboard(int doctorId, QWidget *parent = nullptr);

    ~DoctorDashboard();

private:
    Ui::DoctorDashboard *ui;
    PagePatientSearch *pageSearch;
    PageMedicalRecord *pageMedical;

    int currentDoctorId; // Assurez-vous d'avoir ajouté cette variable aussi
    void refreshAgenda();

private slots:
    void on_btn_menu_agenda_clicked();
    void on_btn_menu_search_clicked();
    void on_btn_menu_dossier_clicked();
    void on_btn_logout_clicked();
    void on_table_appointments_cellClicked(int row, int column);
};

#endif // DOCTORDASHBOARD_H
