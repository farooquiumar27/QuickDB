#include "tests.h"
#include "quickdb/quickdb.h"

TEST_CASE("Store and retrieve a value","[setKeyValue,getKeyValue]")
{
SECTION("Basei set and get")
{
std::string dbname("emptydb");
std::unique_ptr<quickdb::IDatabase> db(quickdb::QuickDB::createEmptyDB(dbname));

std::string key("simlestring");
std::string value("Some highly valuable value");

db->setKeyValue(key,value);
REQUIRE(value == db->getKeyValue(key));
db->destroy( );
}
}