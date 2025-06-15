#include <QStyledItemDelegate>

class MaskDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MaskDelegate(const QString& mask, QObject *parent = nullptr);

    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    QString m_mask;
};
