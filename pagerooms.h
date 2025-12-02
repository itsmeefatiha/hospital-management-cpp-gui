#ifndef PAGEROOMS_H
#define PAGEROOMS_H

#include <QWidget>

namespace Ui {
class PageRooms;
}

class PageRooms : public QWidget
{
    Q_OBJECT

public:
    explicit PageRooms(QWidget *parent = nullptr);
    ~PageRooms();

    void refresh(); // <--- AJOUTÉ

private slots:
    void on_btn_add_room_clicked();

private:
    Ui::PageRooms *ui;
};

#endif // PAGEROOMS_H
