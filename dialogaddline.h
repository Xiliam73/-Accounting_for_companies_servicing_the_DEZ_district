#ifndef DIALOGADDLINE_H
#define DIALOGADDLINE_H

#include <QDialog>
#include "mytablemodel.h"

namespace Ui {
class DialogAddLine;
}

/**
 * @brief Диалоговое окно для добавления новой записи о компании.
 *
 * Предоставляет форму для ввода данных о новой компании-подрядчике.
 */
class DialogAddLine : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор диалогового окна.
     * @param parent Родительский виджет.
     */
    explicit DialogAddLine(QWidget *parent = nullptr);

    /**
     * @brief Деструктор диалогового окна.
     */
    ~DialogAddLine();

private slots:
    /**
     * @brief Обработчик нажатия кнопки "OK".
     *
     * Собирает данные из формы и отправляет сигнал companyAdded.
     */
    void on_pushButtonOk_clicked();

signals:
    /**
     * @brief Сигнал о добавлении новой компании.
     * @param newCompany Данные о новой компании.
     */
    void companyAdded(const MyTableModel::company &newCompany);

private:
    Ui::DialogAddLine *ui; ///< Указатель на UI-форму.
};

#endif // DIALOGADDLINE_H
