#ifndef PAGEPATIENTS_H
#define PAGEPATIENTS_H

#include <QWidget>

namespace Ui {
class PagePatients;
}

class PagePatients : public QWidget
{
    Q_OBJECT

public:
    explicit PagePatients(QWidget *parent = nullptr);
    ~PagePatients();

    void refresh();

private slots:
    void on_btn_save_clicked();
    void on_btn_new_clicked();
    void on_btn_search_clicked();
    void on_search_text_changed(const QString &arg1);

private:
    Ui::PagePatients *ui;
};

#endif // PAGEPATIENTS_H
