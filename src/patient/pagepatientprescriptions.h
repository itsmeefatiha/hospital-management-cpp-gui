#ifndef PAGEPATIENTPRESCRIPTIONS_H
#define PAGEPATIENTPRESCRIPTIONS_H

#include <QWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

namespace Ui {
class PagePatientPrescriptions;
}

class PagePatientPrescriptions : public QWidget
{
    Q_OBJECT

public:
    explicit PagePatientPrescriptions(QWidget *parent = nullptr);
    ~PagePatientPrescriptions();

    // Fonction pour charger la liste des ordonnances du patient
    void loadData(int patientId);

private slots:
    // Slot qui détecte le clic sur le bouton "Imprimer" du tableau
    void on_tablePrescriptions_cellClicked(int row, int column);

private:
    Ui::PagePatientPrescriptions *ui;

    // Fonction interne pour générer et imprimer le document
    void printPrescription(int row);
};

#endif // PAGEPATIENTPRESCRIPTIONS_H
