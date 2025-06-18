#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

/**
 * @brief Диалоговое окно для настройки параметров поиска.
 *
 * Позволяет выбрать столбец и ввести значение для фильтрации данных.
 */
class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор диалогового окна поиска.
     * @param parent Родительский виджет.
     */
    explicit SearchDialog(QWidget *parent = nullptr);

    /**
     * @brief Деструктор диалогового окна поиска.
     */
    ~SearchDialog();

    /**
     * @brief Получить выбранный столбец для поиска.
     * @return Индекс выбранного столбца.
     */
    int selectedColumn() const;

    /**
     * @brief Получить значение для поиска.
     * @return Строка поиска.
     */
    QString searchValue() const;

private:
    Ui::SearchDialog *ui; ///< Указатель на UI-форму.
};

#endif
