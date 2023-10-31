#ifndef EXTDATABASE_H
#define EXTDATABASE_H

#include "../database.h"
#include<functional>
namespace quickdbext
{
using namespace quickdb;
class FileKeyValueStore : public KeyValueStore
{
private:
class Impl;
std::unique_ptr<Impl> mImpl;
public:
FileKeyValueStore(std::string fullpath);
~FileKeyValueStore( );
void setKeyValue(std::string key,std::string value);
std::string getKeyValue(std::string key);
void loadKeysInfo(std::function<void(std::string key,std::string value)> callback);
void clear( );
};
class MemoryKeyValueStore : public KeyValueStore
{
private:
class Impl;
std::unique_ptr<Impl> mImpl;
public:
MemoryKeyValueStore( );
MemoryKeyValueStore(std::unique_ptr<KeyValueStore> &toCache);
~ MemoryKeyValueStore( );
void setKeyValue(std::string key,std::string value);
std::string getKeyValue(std::string key);
void loadKeysInfo(std::function<void(std::string key,std::string value)> callback);
void clear( );
};
class EmbeddedDatabase : public IDatabase
{
public :
EmbeddedDatabase(std::string dbname,std::string fullpath);
EmbeddedDatabase(std::string dbname,std::string fullpath,std::unique_ptr<KeyValueStore> &kvStore);
~EmbeddedDatabase( );
std::string getDirectory(void);
//management functions
static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
static const std::unique_ptr<IDatabase> createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore);
static const std::unique_ptr<IDatabase> load(std::string dbname);
void destroy(void);
//Key-Value use cases
void setKeyValue(std::string key,std::string value);
std::string getKeyValue(std::string key);
class Impl;
private :
std::unique_ptr<Impl> mImpl;
};
}

#endif   //EXTDATABSE_H