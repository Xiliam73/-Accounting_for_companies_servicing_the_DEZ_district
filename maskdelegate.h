#ifndef MASKDELETE_H
#define MASKDELETE_H

#include <QStyledItemDelegate>

/**
 * @brief Делегат для ввода данных по маске.
 *
 * Обеспечивает ввод данных в определенном формате (например, для телефонных номеров).
 */
class MaskDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор делегата.
     * @param mask Маска ввода.
     * @param parent Родительский виджет.
     */
    explicit MaskDelegate(const QString& mask, QObject *parent = nullptr);

    /**
     * @brief Создает редактор для ячейки.
     * @param parent Родительский виджет.
     * @param option Стиль отображения.
     * @param index Индекс модели.
     * @return Виджет-редактор.
     */
    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    QString m_mask; ///< Маска для ввода данных.
};
#endif
