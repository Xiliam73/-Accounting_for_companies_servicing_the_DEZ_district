#ifndef STATUSTYPEDELEGATE_H
#define STATUSTYPEDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief Делегат для выбора статуса компании из выпадающего списка
 */
class StatusTypeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit StatusTypeDelegate(QObject *parent = nullptr);

    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // STATUSTYPEDELEGATE_H
