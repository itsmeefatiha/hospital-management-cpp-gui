#ifndef DOCTORDASHBOARD_H
#define DOCTORDASHBOARD_H
#include <QWidget>
namespace Ui {
class DoctorDashboard;
}
class DoctorDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit DoctorDashboard(QWidget *parent = nullptr);
    ~DoctorDashboard();
private:
    Ui::DoctorDashboard *ui;
};
#endif // DOCTORDASHBOARD_H
