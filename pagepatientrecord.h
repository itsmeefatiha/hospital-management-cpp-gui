#ifndef PAGEPATIENTRECORD_H
#define PAGEPATIENTRECORD_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class PagePatientRecord;
}

class PagePatientRecord : public QWidget
{
    Q_OBJECT

public:
    explicit PagePatientRecord(QWidget *parent = nullptr);
    ~PagePatientRecord();

    void loadData(int patientId);

private slots:
    void on_listWidget_reports_itemClicked(QListWidgetItem *item);

private:
    Ui::PagePatientRecord *ui;
};

#endif // PAGEPATIENTRECORD_H
