#include "statustypedelegate.h"
#include "mytablemodel.h"
#include <QComboBox>

StatusTypeDelegate::StatusTypeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* StatusTypeDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem(tr("Active"), QVariant::fromValue(MyTableModel::StatusType::Active));
    editor->addItem(tr("Inactive"), QVariant::fromValue(MyTableModel::StatusType::Inactive));
    return editor;
}

void StatusTypeDelegate::setEditorData(QWidget *editor,
                                       const QModelIndex &index) const
{
    MyTableModel::StatusType value = index.data(Qt::EditRole).value<MyTableModel::StatusType>();
    QComboBox *combo = static_cast<QComboBox*>(editor);
    combo->setCurrentIndex(combo->findData(QVariant::fromValue(value)));
}

void StatusTypeDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    QComboBox *combo = static_cast<QComboBox*>(editor);
    MyTableModel::StatusType value = combo->currentData().value<MyTableModel::StatusType>();
    model->setData(index, QVariant::fromValue(value), Qt::EditRole);
}

void StatusTypeDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
