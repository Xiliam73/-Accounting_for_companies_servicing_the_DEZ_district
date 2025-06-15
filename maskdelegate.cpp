#include "maskdelegate.h"
#include <QLineEdit>

MaskDelegate::MaskDelegate(const QString &mask, QObject *parent)
    : QStyledItemDelegate(parent), m_mask(mask)
{}

QWidget* MaskDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setInputMask(m_mask);
    return editor;
}
