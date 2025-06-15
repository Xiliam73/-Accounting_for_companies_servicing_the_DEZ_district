#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);


    ui->comboBoxColumn->addItem(tr("ID"), 0);
    ui->comboBoxColumn->addItem(tr("Название компании"), 1);
    ui->comboBoxColumn->addItem(tr("ИНН"), 2);
    ui->comboBoxColumn->addItem(tr("Тип услуги"), 3);
    ui->comboBoxColumn->addItem(tr("Контактное лицо"), 4);
    ui->comboBoxColumn->addItem(tr("Телефон"), 5);
    ui->comboBoxColumn->addItem(tr("Email"), 6);
    ui->comboBoxColumn->addItem(tr("Дата контракта"), 7);
    ui->comboBoxColumn->addItem(tr("Статус"), 8);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

int SearchDialog::selectedColumn() const
{
    return ui->comboBoxColumn->currentData().toInt();
}

QString SearchDialog::searchValue() const
{
    return ui->lineEditValue->text();
}
