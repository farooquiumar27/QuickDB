#include "include/quickdb.h"
#include "include/database.h"
#include "include/extensions/extdatabase.h"
using namespace quickdb;
using namespace quickdbext;
QuickDB::QuickDB( )
{

}

std::unique_ptr<IDatabase> QuickDB::createEmptyDB(std::string &dbname)
{
return EmbeddedDatabase::createEmpty(dbname);
}

std::unique_ptr<IDatabase> QuickDB::createEmptyDB(std::string &dbname,std::unique_ptr<KeyValueStore> &kvStore)
{
return EmbeddedDatabase::createEmpty(dbname,kvStore);
}

std::unique_ptr<IDatabase> QuickDB::loadDB(std::string &dbname)
{
return EmbeddedDatabase::load(dbname);
}