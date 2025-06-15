#include "spinboxdelegate.h"
#include "qtpreprocessorsupport.h"
#include "qwidget.h"
#include <QSpinBox>
#include <QPainter>
#include <QApplication>

SpinBoxDelegate::SpinBoxDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}


QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);



    QSpinBox* editor = new QSpinBox(parent);

    editor->setMinimum(0);
    editor->setMaximum(INT_MAX);

    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.data().toInt();

    QSpinBox *spinBox = qobject_cast<QSpinBox *> (editor);

    spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
    int value = spinBox->value();

    model->setData(index, value);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);

}
