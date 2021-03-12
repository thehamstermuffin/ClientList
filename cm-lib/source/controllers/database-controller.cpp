#include "database-controller.h"

#include <QDebug>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace cm {
namespace controllers {

class DatabaseController::Implementation
{
public:
    Implementation(DatabaseController* _databaseController)
        : databaseController(_databaseController)
    {
        if (initialise()) {
            qDebug() << "Database created using Sqlite version: " + sqliteVersion();

            if (createTables()) {
                qDebug << "Database tables created";
            } else {
                qDebug() << "ERROR: Unable to create database tables";
            }
        } else {
            qDebug() << "ERROR: Unable to open database";
        }
    }

    DatabaseController* databaseController{nullptr};
    QSqlDatabase database;

private:
    //Instantiate connection to SQLite database cm.sqlite
    //and create file if doesn't exist
    bool initialise()
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "cm");
        database.setDatabaseName( "cm.qslite" );
        return database.open();
    }

    //Create necessary tables if they don't exist already
    //Initially just client is needed, it may be expanded later
    bool createTables()
    {
        return createJsonTable( "client" );
    }

    bool createJsonTable(const QString& tableName) const
    {
        QSqlQuery query(database);
        QString sqlStatement = "CREATE TABLE IF NOT EXISTS " + tableName +
                " (id text primary key, json text not null)";

        if (!query.prepare(sqlStatement)) return false;

        return query.exec();
    }

    QString sqliteVersion() const
    {
        QSqlQuery query(database);

        query.exec("SELECT sqlite_version()");

        if (query.next()) return query.value(0).toString();

        return QString::number(-1);
    }

};

}

namespace controllers {
//banana estos ampersands se autocompletaron asi pero talvez vayan pegados al tipo y no al nombre
bool DatabaseController::createRow(const QString &tableName, const QString &id, const QJsonObject &jsonObject) const
{
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;
    if (jsonObject.isEmpty()) return false; //banana no se porque manda error aqui

    QSqlQuery query(implementation->database);
    QString sqlStatement = "INSERT OR REPLACE INTO " + tableName +
            "(id, json) VALUES (:id, :json)";

    if (!query.prepare(sqlStatement)) return false;

    query.bindValue(":id", QVariant(id));
    query.bindValue(":json", QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));

    if (!query.exec()) return false;

    return query.numRowsAffected() > 0;
}

bool DatabaseController::deleteRow(const QString &tableName, const QString &id) const
{
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;

    QSqlQuery query (implementation->database);

    QString sqlStatement = "DELETE FROM " + tableName + " WHERE id=:id";

    if (!query.prepare(sqlStatement)) return false;

    query.bindValue(":id", QVariant(id));

    if (!query.exec()) return false;

    return query.numRowsAffected() > 0;
}

QJsonObject DatabaseController::readRow(const QString &tableName, const QString &id) const
{
    if (tableName.isEmpty()) return {};
    if (id.isEmpty()) return {};

    QSqlQuery query (implementation->database);

    QString sqlStatement = "DELETE FROM " + tableName + " WHERE id=:id";

    if (!query.prepare(sqlStatement)) return {};

    query.bindValue(":id", QVariant(id));

    if (!query.exec()) return {};

    if (!query.first()) return {};

    auto json = query.value(0).toByteArray();
    auto jsonDocument = QJsonDocument::fromJson(json);

    if (!jsonDocument.isObject()) return {};

    return jsonDocument.object();

}

bool DatabaseController::updateRow(const QString &tableName, const QString &id, const QJsonObject &jsonObject) const
{
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;
    if (jsonObject.isEmpty()) return false;

    QSqlQuery query(implementation->database);

    QString sqlStatement = "UPDATE " + tableName + " SET json=:json WHERE id=:id";

    if (!query.prepare(sqlStatement)) return false;

    query.bindValue(":id", QVariant(id));
    query.bindValue(":json", QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));

    if (!query.exec()) return false;

    return query.numRowsAffected() > 0;
}

}

}
