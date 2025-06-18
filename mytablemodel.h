#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDate>



/**
 * @brief Модель данных для таблицы компаний-подрядчиков.
 *
 * Предоставляет данные для отображения в таблице и обработки операций.
 */
class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /// @name Перечисления
    /// @{
    enum class ServiceType {WasteRemoval,RoadRepairs, Landscaping, ElectricityWater}; ///< Типы услуг.
    enum class StatusType {Active, Inactive}; ///< Статусы компаний.
    /// @}

    /**
     * @brief Структура данных о компании.
     */
    struct company
    {
        int id; ///< Уникальный идентификатор.
        QString CompanyName; ///< Название компании.
        int TaxpayerID; ///< ИНН налогоплательщика.
        ServiceType service; ///< Тип предоставляемых услуг.
        QString ContactName; ///< Контактное лицо.
        QString PhoneNumber; ///< Телефон.
        QString email; ///< Электронная почта.
        QDate ContractDate; ///< Дата договора.
        StatusType status; ///< Статус компании.

        /**
         * @brief Конструктор с параметрами.
         * @param pid Идентификатор.
         * @param pCompanyName Название компании.
         * @param pTaxpayerID ИНН.
         * @param pservice Тип услуг.
         * @param pContactName Контактное лицо.
         * @param pPhoneNumber Телефон.
         * @param pemail Электронная почта.
         * @param pContractDate Дата договора.
         * @param pstatus Статус.
         */
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

        /**
         * @brief Конструктор копирования.
         * @param other Другой объект company.
         */
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

    /**
     * @brief Конструктор модели.
     * @param parent Родительский объект.
     */
    explicit MyTableModel(QObject *parent = nullptr);

private:
    QList<company> companies; ///< Список компаний.
    const int columnsNum; ///< Количество столбцов.
    bool editFlag; ///< Флаг разрешения редактирования.
    QString FileName; ///< Имя текущего файла.

    /// @name Методы модели (QAbstractItemModel)
    /// @{
public:
    void changeFlag(const bool fl); ///< Изменить флаг редактирования.
    bool editLine(const int index, const int id,
                  const QString CompanyName,
                  const int TaxpayerID,
                  const ServiceType service,
                  const QString ContactName,
                  const QString PhoneNumber,
                  const QString email,
                  const QDate ContractDate,
                  const StatusType Status ); ///< Редактировать строку.
    bool insertLine(const int position,
                    const int id,
                    const QString CompanyName,
                    const int TaxpayerID,
                    const ServiceType service,
                    const QString ContactName,
                    const QString PhoneNumber,
                    const QString email,
                    const QDate ContractDate,
                    const StatusType Status ); ///< Вставить строку.
    bool removeRow(const int position); ///< Удалить строку.
    bool LoadDataFromFile(const QString& fileName); ///< Загрузить данные из файла.
    bool WriteDataInFile(const QString& fileName); ///< Сохранить данные в файл.
    bool addLine(const company &cp); ///< Добавить компанию.
    QString getFileName(); ///< Получить имя файла.

    int rowCount(const QModelIndex &parent) const override; ///< Количество строк.
    int columnCount(const QModelIndex &parent) const override; ///< Количество столбцов.
    QVariant data(const QModelIndex &index, int role) const override; ///< Данные ячейки.
    bool setData(const QModelIndex &index, const QVariant &value, int role) override; ///< Установить данные.
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override; ///< Заголовки столбцов.
    Qt::ItemFlags flags(const QModelIndex &index) const override; ///< Флаги элементов.
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override; ///< Сортировка данных.
    /// @}
};
Q_DECLARE_METATYPE(MyTableModel::ServiceType);
#endif // MYTABLEMODEL_H
