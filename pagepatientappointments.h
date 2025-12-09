#ifndef PAGEPATIENTAPPOINTMENTS_H
#define PAGEPATIENTAPPOINTMENTS_H

#include <QWidget>

namespace Ui {
class PagePatientAppointments;
}

class PagePatientAppointments : public QWidget
{
    Q_OBJECT

public:
    explicit PagePatientAppointments(QWidget *parent = nullptr);
    ~PagePatientAppointments();

    void loadData(int patientId);

private:
    Ui::PagePatientAppointments *ui;
};

#endif // PAGEPATIENTAPPOINTMENTS_H
