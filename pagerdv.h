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

    // --- LA FONCTION MANQUANTE ---
    void refresh();

private slots:
    void on_btn_confirm_clicked();

private:
    Ui::PageRDV *ui;

    // --- FONCTIONS D'AIDE NÉCESSAIRES ---
    void loadDoctors(const QString &serviceName);
    void loadAppointments();
};

#endif // PAGERDV_H
