#ifndef PATIENTDASHBOARD_H
#define PATIENTDASHBOARD_H
#include <QWidget>
namespace Ui {
class PatientDashboard;
}
class PatientDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit PatientDashboard(QWidget *parent = nullptr);
    ~PatientDashboard();
private:
    Ui::PatientDashboard *ui;
};
#endif // PATIENTDASHBOARD_H
