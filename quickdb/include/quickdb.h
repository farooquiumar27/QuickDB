#ifndef QUICKDB_H
#define QUICKDB_H
#include<string>
//WARNING This should ONLY include Client API files
//i.e. NOT anything within include/extension!
#include "database.h"
namespace quickdb
{
class QuickDB
{
public:
QuickDB( );
static std::unique_ptr<IDatabase> createEmptyDB(std::string &dbname);
static std::unique_ptr<IDatabase> createEmptyDB(std::string &dbname,std::unique_ptr<KeyValueStore> &kvStore);
static std::unique_ptr<IDatabase> loadDB(std::string &dbname);
};
}

#endif   //QUICKDB_H