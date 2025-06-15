#ifndef DIALOGADDLINE_H
#define DIALOGADDLINE_H

#include <QDialog>
#include "mytablemodel.h"
namespace Ui {
class DialogAddLine;
}

class DialogAddLine : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddLine(QWidget *parent = nullptr);
    ~DialogAddLine();

private slots:
    void on_pushButtonOk_clicked();


signals:
    void companyAdded(const MyTableModel::company &newCompany);

private:
    Ui::DialogAddLine *ui;
};

#endif // DIALOGADDLINE_H
