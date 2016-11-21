#ifndef MIXXX_SQLSTORAGE_H
#define MIXXX_SQLSTORAGE_H


#include <QSqlDatabase>


// Common base class/interface of all persistent storage based on an
// SQL database.
class SqlStorage {
  public:
    virtual ~SqlStorage() {}
    SqlStorage(const SqlStorage&) = delete; // disable copying

    // A self-healing function that repairs the managed tables
    // by validating all stored data, both values and relations.
    // If referential integrity constraints are violated those
    // strayed rows should be deleted.
    // This function will only be called while no database
    // is attached to avoid invalidation of internal caches!
    virtual void repairDatabase(QSqlDatabase database) = 0;

    // Attach an open database connection to the storage class.
    // Implementations might need to do the following:
    //  - initialization of prepared queries
    //  - creation of (temporary) tables/views
    //  - initial population of internal caches
    // This database connection stays open and should be used
    // until it is detached (see below). Implementations must
    // store an implicitly shared copy of the QSqlDatabase for
    // accessing it.
    virtual void attachDatabase(QSqlDatabase database) = 0;

    // Detach the currently attached database, e.g. before
    // closing it.
    // Implementations should perform the necessary cleanup
    // and discard all internally cached data that depends
    // on the database connection.
    virtual void detachDatabase() = 0;

  protected:
    SqlStorage() {}
};


#endif // MIXXX_SQLSTORAGE_H
