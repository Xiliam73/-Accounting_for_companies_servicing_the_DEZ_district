#include "dialogaddline.h"
#include "ui_dialogaddline.h"


DialogAddLine::DialogAddLine(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAddLine)
{
    ui->setupUi(this);

    ui->comboBoxServiceType->clear();
    ui->comboBoxServiceType->addItem(tr("Вывоз мусора, Уборка"), static_cast<int>(MyTableModel::ServiceType::WasteRemoval));
    ui->comboBoxServiceType->addItem(tr("Ремонт дорог"), static_cast<int>(MyTableModel::ServiceType::RoadRepairs));
    ui->comboBoxServiceType->addItem(tr("Озеленение, Обслуживание"), static_cast<int>(MyTableModel::ServiceType::Landscaping));
    ui->comboBoxServiceType->addItem(tr("Электроснабжение, Водоснабжение"), static_cast<int>(MyTableModel::ServiceType::ElectricityWater));

    ui->dateEditDate->setCalendarPopup(true);
}

DialogAddLine::~DialogAddLine()
{
    delete ui;
}

void DialogAddLine::on_pushButtonOk_clicked()
{
    MyTableModel::ServiceType serviceType;
    switch (ui->comboBoxServiceType->currentIndex()) {
    case 0:
        serviceType = MyTableModel::ServiceType::WasteRemoval;
        break;
    case 1:
        serviceType = MyTableModel::ServiceType::RoadRepairs;
        break;
    case 2:
        serviceType = MyTableModel::ServiceType::Landscaping;
        break;
    case 3:
        serviceType = MyTableModel::ServiceType::ElectricityWater;
        break;

    }


    MyTableModel::StatusType statusType;
    if(ui->checkBoxActive->isChecked())
        statusType = MyTableModel::StatusType::Active;
    else
        statusType = MyTableModel::StatusType::Inactive;




    MyTableModel::company current(ui->spinBoxID->value(),ui->lineEditCompanyName->text(),ui->spinBox_TaxPayerID->value(),serviceType, ui->lineEditContactName->text(), ui->lineEditPhoneNumber->text(), ui->lineEditemail->text(), ui->dateEditDate->date(), statusType);
    emit companyAdded(current);
    this->close();
}

