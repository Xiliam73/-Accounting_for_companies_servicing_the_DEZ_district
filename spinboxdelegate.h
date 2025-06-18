#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief Делегат для ввода целых чисел (SpinBox).
 *
 * Обеспечивает редактирование числовых значений через QSpinBox.
 */
class SpinBoxDelegate : public QStyledItemDelegate
{
public:
    /**
     * @brief Конструктор делегата.
     * @param parent Родительский виджет.
     */
    explicit SpinBoxDelegate(QWidget *parent);

    /// @name Методы делегата (QAbstractItemDelegate)
    /// @{
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override; ///< Создать редактор.
    void setEditorData(QWidget *editor, const QModelIndex &index) const override; ///< Установить данные в редактор.
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override; ///< Забрать данные из редактора.
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override; ///< Обновить геометрию редактора.
    /// @}
};

#endif // SPINBOXDELEGATE_H
