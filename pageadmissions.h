#ifndef PAGEADMISSIONS_H
#define PAGEADMISSIONS_H

#include <QWidget>
#include "pagepatientsearch.h"
#include "pagemedicalrecord.h"

namespace Ui {
class PageAdmissions;
}

class PageAdmissions : public QWidget
{
    Q_OBJECT

public:
    explicit PageAdmissions(QWidget *parent = nullptr);
    ~PageAdmissions();

    void refresh();

private slots:
    void on_btn_save_clicked();

    // Slot pour le clic dans le tableau (Bouton Sortie)
    void on_tableAdmissions_cellClicked(int row, int column);

private:
    Ui::PageAdmissions *ui;

    void loadActiveAdmissions();

    // Nouvelle fonction qui prend la date en paramètre
    void dischargePatient(int admissionId, int roomId, QDate exitDate);
};

#endif // PAGEADMISSIONS_H
