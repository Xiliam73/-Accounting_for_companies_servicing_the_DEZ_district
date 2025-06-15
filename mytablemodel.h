#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDate>

class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT



public:
    enum class ServiceType {WasteRemoval,RoadRepairs, Landscaping, ElectricityWater};
    enum class StatusType {Active, Inactive};

    struct company
    {
        int id;
        QString CompanyName;
        int TaxpayerID;
        ServiceType service;
        QString ContactName;
        QString PhoneNumber;
        QString email;
        QDate ContractDate;
        StatusType status;
        company(const int pid,
                const QString pCompanyName,
                const int pTaxpayerID,
                const ServiceType pservice,
                const QString pContactName,
                const QString pPhoneNumber,
                const QString pemail,
                const QDate pContractDate,
                const StatusType pstatus) :
                                            id(pid),
                                            CompanyName(pCompanyName),
                                            TaxpayerID(pTaxpayerID),
                                            service(pservice),
                                            ContactName(pContactName),
                                            PhoneNumber(pPhoneNumber),
                                            email(pemail),
                                            ContractDate(pContractDate),
                                            status(pstatus)
        {}
        company(const company &other) :
                                            id(other.id),
                                            CompanyName(other.CompanyName),
                                            TaxpayerID(other.TaxpayerID),
                                            service(other.service),
                                            ContactName(other.ContactName),
                                            PhoneNumber(other.PhoneNumber),
                                            email(other.email),
                                            ContractDate(other.ContractDate),
                                            status(other.status)
        {}
    };


    explicit MyTableModel(QObject *parent = nullptr);

private:
    QList<company> companies;
    const int columnsNum;
    bool editFlag;
    QString FileName;

    // QAbstractItemModel interface
public:
    void changeFlag(const bool fl);
    bool editLine(const int index, const int id,
                  const QString CompanyName,
                  const int TaxpayerID,
                  const ServiceType service,
                  const QString ContactName,
                  const QString PhoneNumber,
                  const QString email,
                  const QDate ContractDate,
                  const StatusType Status );
    bool insertLine(const int position,
                 const int id,
                 const QString CompanyName,
                 const int TaxpayerID,
                 const ServiceType service,
                 const QString ContactName,
                 const QString PhoneNumber,
                 const QString email,
                 const QDate ContractDate,
                 const StatusType Status );
    bool removeRow(const int position);
    bool LoadDataFromFile(const QString& fileName);
    bool WriteDataInFile(const QString& fileName);
    bool addLine(const company &cp);
    QString getFileName();


    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;


};

#endif // MYTABLEMODEL_H
