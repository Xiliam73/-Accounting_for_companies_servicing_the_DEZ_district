#include "mytablemodel.h"
#include <QFile>
#include <QMessageBox>
MyTableModel::MyTableModel(QObject *parent)
    : QAbstractTableModel{parent}
    , columnsNum(9)
    , editFlag(false)
    , FileName("")
{

}

void MyTableModel::changeFlag(const bool fl)
{
    editFlag = fl;
}

bool MyTableModel::editLine(const int index, const int id,
                                             const QString CompanyName,
                                             const int TaxpayerID,
                                             const ServiceType service,
                                             const QString ContactName,
                                             const QString PhoneNumber,
                                             const QString email,
                                             const QDate ContractDate,
                                             const StatusType Status )
{
    if(index >= companies.size()) return false;

    companies[index].id = id;
    companies[index].CompanyName = CompanyName;
    companies[index].TaxpayerID = TaxpayerID;
    companies[index].service = service;
    companies[index].ContactName = ContactName;
    companies[index].PhoneNumber = PhoneNumber;
    companies[index].email = email;
    companies[index].ContractDate = ContractDate;
    companies[index].status = Status;




    return true;
}

bool MyTableModel::insertLine(const int position, const int id, const QString CompanyName, const int TaxpayerID, const ServiceType service, const QString ContactName, const QString PhoneNumber, const QString email, const QDate ContractDate, const StatusType Status)
{
    beginInsertColumns(QModelIndex(), position, position);
    companies.insert(position, company(id, CompanyName, TaxpayerID, service, ContactName, PhoneNumber, email, ContractDate, Status));
    endInsertRows();
    return true;
}

bool MyTableModel::removeRow(const int position)
{
    if(companies.isEmpty() || position >= companies.size()) return false;

    beginRemoveRows(QModelIndex(),position,position);

    companies.removeAt(position);

    endRemoveRows();

    return true;
}

bool MyTableModel::LoadDataFromFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        // QMessageBox::warning(nullptr,tr("Application"), QString(tr("Can't read file %1: \n%2")).arg(fileName, file.errorString()));
         qWarning() << "Cannot open file:" << fileName << "Error:" << file.errorString();
        return false;
    }


    beginResetModel();
    companies.clear();

    QTextStream in(&file);
    QString line = in.readLine();
    //можно использовать первую строку для инициализации колонок

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');

        ServiceType servicetype;
        if(parts[3] == "Waste removal, Cleaning" or parts[3] == "Вывоз мусора, Уборка")  servicetype = ServiceType::WasteRemoval;
        if(parts[3] == "Road repairs" or parts[3] == "Ремонт дорог")              servicetype = ServiceType::RoadRepairs;
        if(parts[3] == "Landscaping, Maintenance" or parts[3] == "Озеленение, Обслуживание") servicetype = ServiceType::Landscaping;
        if(parts[3] == "Electricity, Water supply" or parts[3] == "Электроснабжение, Водоснабжение")servicetype = ServiceType::ElectricityWater;

        if (parts.size() >= 9) {
            companies.append(company(
                parts[0].toInt(),
                parts[1],
                parts[2].toInt(),
                servicetype,
                parts[4],
                parts[5],
                parts[6],
                QDate::fromString(parts[7], "dd.MM.yyyy"),
                parts[8] == "Active" or parts[8] == "Активна" ? StatusType::Active : StatusType::Inactive
                ));
        }
    }
    endResetModel(); // Уведомляем view об изменениях


    FileName = fileName;
    file.close();
    return true;
}

bool MyTableModel::WriteDataInFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qWarning() << "Cannot open file:" << fileName;
        return false;
    }
    QTextStream out(&file);



    out << "ID;Company Name;Taxpayer ID;Service Type;Contact Person;Phone Number;Email;Contract Date;Status\n";


    for (const company &comp : companies) {


        qDebug() << comp.id << comp.CompanyName << comp.TaxpayerID;

        QString serviceStr;
        switch (comp.service) {
        case ServiceType::WasteRemoval: serviceStr = "Waste removal, Cleaning"; break;
        case ServiceType::RoadRepairs: serviceStr = "Road repairs"; break;
        case ServiceType::Landscaping: serviceStr = "Landscaping, Maintenance"; break;
        case ServiceType::ElectricityWater: serviceStr = "Electricity, Water supply"; break;
        }

        QString statusStr = (comp.status == StatusType::Active) ? "Active" : "Inactive";

        out << comp.id << ";"
            << comp.CompanyName << ";"
            << comp.TaxpayerID << ";"
            << serviceStr << ";"
            << comp.ContactName << ";"
            << comp.PhoneNumber << ";"
            << comp.email << ";"
            << comp.ContractDate.toString("dd.MM.yyyy") << ";"
            << statusStr << "\n";
    }

    file.close();
    return true;
}

bool MyTableModel::addLine(const company &cp)
{
    beginResetModel();

    companies.append(cp);


    endResetModel();
    return true;
}

QString MyTableModel::getFileName()
{
    return FileName;
}



int MyTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : companies.count();
}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : columnsNum;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant();
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if(col == 0)
            return companies.at(row).id;
        if(col == 1)
            return companies.at(row).CompanyName;

        if(col == 2)
            return companies.at(row).TaxpayerID;

        if(col == 3)
            switch(companies.at(row).service) {
                case ServiceType::WasteRemoval: return tr("Waste removal, Cleaning");
                case ServiceType::RoadRepairs: return tr("Road repairs");
                case ServiceType::Landscaping: return tr("Landscaping, Maintenance");
                case ServiceType::ElectricityWater: return tr("Electricity, Water supply");
                default: return "Unknown";
            }

        if(col == 4)
            return companies.at(row).ContactName;

        if(col == 5)
            return companies.at(row).PhoneNumber;

        if(col == 6)
            return companies.at(row).email;

        if(col == 7)
            return companies.at(row).ContractDate;

        if(col == 8)
            return companies.at(row).status == StatusType::Active ? tr("Active") : tr("Inactive");

    }
    return QVariant();
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
        return false;

    int col = index.column();
    int row = index.row();

    if(role == Qt::EditRole && editFlag){
        if(col == 0){
            company cp = companies.at(row);
            cp.id = value.toInt();
            companies.replace(index.row(), cp);
        }
        if(col == 1){
            company cp = companies.at(row);
            cp.CompanyName = value.toString();
            companies.replace(index.row(), cp);
        }
        if(col == 2){
            company cp = companies.at(row);
            cp.TaxpayerID = value.toInt();
            companies.replace(index.row(), cp);
        }
        if(col == 3){
            company cp = companies.at(row);
            if(value.toString() == "Waste removal, Cleaning")  cp.service = ServiceType::WasteRemoval;
            if(value.toString() == "Road repairs")             cp.service = ServiceType::RoadRepairs;
            if(value.toString() == "Landscaping, Maintenance") cp.service = ServiceType::Landscaping;
            if(value.toString() == "Electricity, Water supply")cp.service = ServiceType::ElectricityWater;
            companies.replace(index.row(), cp);
            }
        if(col == 4){
            company cp = companies.at(row);
            cp.ContactName = value.toString();
            companies.replace(index.row(), cp);
        }
        if(col == 5){
            company cp = companies.at(row);
            cp.PhoneNumber = value.toString();
            companies.replace(index.row(), cp);
        }
        if(col == 6){
            company cp = companies.at(row);
            cp.email = value.toString();
            companies.replace(index.row(), cp);
        }
        if(col == 7){
            company cp = companies.at(row);
            cp.ContractDate = value.toDate();
            companies.replace(index.row(), cp);
        }
        if(col == 8){
            company cp = companies.at(row);
            if(value == "Active") cp.status = StatusType::Active;
            else cp.status = StatusType::Inactive;

            companies.replace(index.row(), cp);
        }
        return true;
    }
    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return false;
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case 0:
            return QString(tr("id"));
        case 1:
            return QString(tr("Company Name"));
        case 2:
            return QString(tr("Taxpayer ID"));
        case 3:
            return QString(tr("service"));
        case 4:
            return QString(tr("Contact Name"));
        case 5:
            return QString(tr("Phone Number"));
        case 6:
            return QString(tr("email"));
        case 7:
            return QString(tr("Contract Date"));
        case 8:
            return QString(tr("status"));
        }
    }

    if(orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString::number(section + 1);

    return QVariant();
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    else
        return Qt::NoItemFlags;
}

void MyTableModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();

    switch (column) {
    case 0:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.id < company2.id;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.id > company2.id;
            } );
        break;
    case 1:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.CompanyName < company2.CompanyName;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.CompanyName > company2.CompanyName;
            } );
        break;
    case 2:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.TaxpayerID < company2.TaxpayerID;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.TaxpayerID > company2.TaxpayerID;
            } );
        break;
    case 3:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return static_cast<int>(company1.service) <= static_cast<int>(company2.service);
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.service > company2.service;
            } );
        break;
    case 4:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.ContactName < company2.ContactName;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.ContactName > company2.ContactName;
            } );
    case 5:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.PhoneNumber < company2.PhoneNumber;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.PhoneNumber > company2.PhoneNumber;
            } );
    case 6:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.email < company2.email;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.email > company2.email;
            } );
    case 7:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.ContractDate < company2.ContractDate;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.ContractDate > company2.ContractDate;
            } );
    case 8:
        if(order == Qt::AscendingOrder)
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.status < company2.status;
            } );
        else
            std::sort(companies.begin(), companies.end(), [](const company &company1,
                                                             const company &company2){
                return company1.status > company2.status;
            } );
    }

    emit layoutChanged();

}
