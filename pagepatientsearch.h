#ifndef PAGEPATIENTSEARCH_H
#define PAGEPATIENTSEARCH_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class PagePatientSearch;
}

class PagePatientSearch : public QWidget
{
    Q_OBJECT

public:
    explicit PagePatientSearch(QWidget *parent = nullptr);
    ~PagePatientSearch();

private:
    Ui::PagePatientSearch *ui;
signals:
    void patientSelected(int patientId);

private slots:
    void on_btn_search_clicked();
    void on_listWidget_results_itemClicked(QListWidgetItem *item);
};

#endif // PAGEPATIENTSEARCH_H
