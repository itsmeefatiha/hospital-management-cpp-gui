#ifndef PAGEADMISSIONS_H
#define PAGEADMISSIONS_H

#include <QWidget>

namespace Ui {
class PageAdmissions;
}

class PageAdmissions : public QWidget
{
    Q_OBJECT

public:
    explicit PageAdmissions(QWidget *parent = nullptr);
    ~PageAdmissions();

    void refresh();

private slots:
    void on_btn_save_clicked();

private:
    Ui::PageAdmissions *ui;
    
    // --- NOUVELLE FONCTION ---
    void loadActiveAdmissions();
};

#endif // PAGEADMISSIONS_H