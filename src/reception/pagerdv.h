#ifndef PAGERDV_H
#define PAGERDV_H

#include <QWidget>

namespace Ui {
class PageRDV;
}

class PageRDV : public QWidget
{
    Q_OBJECT

public:
    explicit PageRDV(QWidget *parent = nullptr);
    ~PageRDV();

    void refresh();

private slots:
    void on_btn_confirm_clicked();

private:
    Ui::PageRDV *ui;

    void loadDoctors(const QString &serviceName);
    void loadAppointments();
};

#endif // PAGERDV_H
