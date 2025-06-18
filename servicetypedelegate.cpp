#include "servicetypedelegate.h"
#include "mytablemodel.h"
#include <QComboBox>

ServiceTypeDelegate::ServiceTypeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* ServiceTypeDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &,
                                           const QModelIndex &) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem(tr("Waste removal, Cleaning"), QVariant::fromValue(MyTableModel::ServiceType::WasteRemoval));
    editor->addItem(tr("Road Repaires"), QVariant::fromValue(MyTableModel::ServiceType::RoadRepairs));
    editor->addItem(tr("Landscaping, Maintenance"), QVariant::fromValue(MyTableModel::ServiceType::Landscaping));
    editor->addItem(tr("Electricity, Water supply"), QVariant::fromValue(MyTableModel::ServiceType::ElectricityWater));
    return editor;
}

void ServiceTypeDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &index) const
{
    MyTableModel::ServiceType value = index.data(Qt::EditRole).value<MyTableModel::ServiceType>();
    QComboBox *combo = static_cast<QComboBox*>(editor);
    combo->setCurrentIndex(combo->findData(QVariant::fromValue(value)));
}

void ServiceTypeDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
    QComboBox *combo = static_cast<QComboBox*>(editor);
    MyTableModel::ServiceType value = combo->currentData().value<MyTableModel::ServiceType>();
    model->setData(index, QVariant::fromValue(value), Qt::EditRole);
}

void ServiceTypeDelegate::updateEditorGeometry(QWidget *editor,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
