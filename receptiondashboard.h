#ifndef RECEPTIONDASHBOARD_H
#define RECEPTIONDASHBOARD_H
#include <QWidget>
namespace Ui {
class ReceptionDashboard;
}
class ReceptionDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit ReceptionDashboard(QWidget *parent = nullptr);
    ~ReceptionDashboard();
private:
    Ui::ReceptionDashboard *ui;
};
#endif // RECEPTIONDASHBOARD_H
