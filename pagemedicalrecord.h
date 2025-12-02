#ifndef PAGEMEDICALRECORD_H
#define PAGEMEDICALRECORD_H

#include <QWidget>

namespace Ui {
class PageMedicalRecord;
}

class PageMedicalRecord : public QWidget
{
    Q_OBJECT

public:
    explicit PageMedicalRecord(QWidget *parent = nullptr);
    ~PageMedicalRecord();

    void loadPatient(int pid, int docId);

private slots:
    void on_btn_add_med_clicked();
    void on_btn_save_consultation_clicked();
    void on_table_history_cellClicked(int row, int column);

private:
    Ui::PageMedicalRecord *ui;

    // --- THIS WAS MISSING ---
    void loadHistory(int patientId);
};

#endif // PAGEMEDICALRECORD_H
