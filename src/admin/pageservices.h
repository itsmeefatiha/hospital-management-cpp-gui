#ifndef PAGESERVICES_H
#define PAGESERVICES_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class PageServices;
}

class PageServices : public QWidget
{
    Q_OBJECT

public:
    explicit PageServices(QWidget *parent = nullptr);
    ~PageServices();
    void refresh();

private slots:
    void on_listWidget_services_itemClicked(QListWidgetItem *item);
    void on_btn_add_service_clicked();
    void on_btn_assign_doc_clicked();

private:
    Ui::PageServices *ui;
};

#endif // PAGESERVICES_H
