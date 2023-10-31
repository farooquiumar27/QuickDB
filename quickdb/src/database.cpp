#include "database.h"
#include "extensions/extdatabase.h"
#include<iostream>
#include<fstream>
#include<filesystem>
#include<unordered_map>
namespace fs=std::filesystem;
using namespace quickdb;
using namespace quickdbext;
//Hidden Database impl class here
class EmbeddedDatabase::Impl : public IDatabase
{
public :
Impl(std::string dbname,std::string fullpath);
Impl(std::string dbname,std::string fullpath,std::unique_ptr<KeyValueStore> &kvStore);
~Impl( );
std::string getDirectory(void);
//management functions
static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
static const std::unique_ptr<IDatabase> createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore);
static const std::unique_ptr<IDatabase> load(std::string dbname);
void destroy(void);
//Key-Value use cases
void setKeyValue(std::string key,std::string value);
std::string getKeyValue(std::string key);
private :
std::string m_name;
std::string m_fullpath;
std::unique_ptr<KeyValueStore> m_keyValueStore;
};

//High level Database client API implementation below
EmbeddedDatabase::Impl::Impl(std::string dbname,std::string fullpath)
: m_name(dbname) , m_fullpath(fullpath)
{
//Now we will provide the default keyValueStore
std::unique_ptr<KeyValueStore> fileStore=std::make_unique<FileKeyValueStore>(fullpath);
std::unique_ptr<KeyValueStore> memoryStore=std::make_unique<MemoryKeyValueStore>(fileStore);
m_keyValueStore=std::move(memoryStore);
}

EmbeddedDatabase::Impl::Impl(std::string dbname,std::string fullpath,std::unique_ptr<KeyValueStore> &kvStore)
 : m_name(dbname) , m_fullpath(fullpath) , m_keyValueStore(kvStore.release( ))
{
;
}

EmbeddedDatabase::Impl::~Impl( )
{
;
}
//Management function
const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbname)
{
std::string basedir(".quickdb");
if(!fs::exists(basedir))
{
fs::create_directory(basedir);
}
std::string dbfolder(basedir+"/"+dbname);
return std::make_unique<EmbeddedDatabase::Impl>(dbname,dbfolder);
}
const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbname,std::unique_ptr<KeyValueStore>& kvStore)
{
std::string basedir(".quickdb");
if(!fs::exists(basedir))
{
fs::create_directory(basedir);
}
std::string dbfolder(basedir+"/"+dbname);
return std::make_unique<EmbeddedDatabase::Impl>(dbname,dbfolder,kvStore);
}
const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::load(std::string dbname)
{
std::string basedir(".quickdb");
std::string dbfolder(basedir+"/"+dbname);
return std::make_unique<EmbeddedDatabase::Impl>(dbname,dbfolder);
}
void EmbeddedDatabase::Impl::destroy( )
{
m_keyValueStore->clear( );
}

//Instance user function
std::string EmbeddedDatabase::Impl::getDirectory(void)
{
return m_fullpath;
}
void EmbeddedDatabase::Impl::setKeyValue(std::string key,std::string value)
{
m_keyValueStore->setKeyValue(key,value);
}
std::string EmbeddedDatabase::Impl::getKeyValue(std::string key)
{
return m_keyValueStore->getKeyValue(key);
}


//Embedded database
EmbeddedDatabase::EmbeddedDatabase(std::string dbname,std::string fullpath)
{	
mImpl=std::make_unique<EmbeddedDatabase::Impl>(dbname,fullpath);
}
EmbeddedDatabase::~EmbeddedDatabase( )
{
;
}
std::string EmbeddedDatabase::getDirectory(void)
{
return mImpl->getDirectory( );
}
const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(std::string dbname)
{
return EmbeddedDatabase::Impl::createEmpty(dbname);
}
const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(std::string dbname,std::unique_ptr<KeyValueStore> &kvStore)
{
return EmbeddedDatabase::Impl::createEmpty(dbname,kvStore);
}
const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string dbname)
{
return EmbeddedDatabase::Impl::load(dbname);
}
void EmbeddedDatabase::destroy(void)
{
mImpl->destroy( );
}
void EmbeddedDatabase::setKeyValue(std::string key,std::string value)
{
mImpl->setKeyValue(key,value);
}
std::string EmbeddedDatabase::getKeyValue(std::string key)
{
return mImpl->getKeyValue(key);
}

