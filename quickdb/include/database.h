#ifndef DATABASE_H
#define DATABASE_H
#include<string>
#include<memory>
#include <functional>
namespace quickdb
{
class Store
{
public:
Store( )=default;
virtual ~Store( )=default;
};
class KeyValueStore : public Store
{
public:
KeyValueStore( )=default;
virtual ~KeyValueStore( )=default;
//Key-Value user function
virtual void setKeyValue(std::string key,std::string value)=0;
virtual std::string getKeyValue(std::string key)=0;
virtual void loadKeysInfo(std::function<void(std::string key,std::string value)> callback)=0;
virtual void clear( )=0;
};
class IDatabase
{
public :
IDatabase( )=default;
virtual ~IDatabase( )=default;
virtual std::string getDirectory(void)=0;
//management functions
static const std::unique_ptr<IDatabase> createEmpty(std::string dbname);
static const std::unique_ptr<IDatabase> load(std::string dbname);
virtual void destroy(void)=0;
//Key-Value use cases
virtual  void setKeyValue(std::string key,std::string value)=0;
virtual  std::string getKeyValue(std::string key)=0;
};
}

#endif