#define CATCH_CONFIG_ENABLE_BENCHMARKING 1
//#include "catch.hpp"
#include "tests.h"
#include<unordered_map>
#include<chrono>
#include<iostream>
#include<string>
#include "quickdb/quickdb.h"
#include "quickdb/quickdbext.h"
namespace fs=std::filesystem;
	
TEST_CASE("Measure basic performance","[setKeyValue,getKeyValue]")
{
SECTION("Store and retrieve 100 000 keys -Memory cached key-value store")
{
std::string dbname("myemptydb");
std::unique_ptr<quickdb::IDatabase> db(quickdb::QuickDB::createEmptyDB(dbname));
int total=100000;
//1 Pre-generate the keys and values in memory
std::unordered_map<std::string,std::string> keyValues;
long i=0;
std::cout<<"Pre generating key values pairs ..."<<std::endl;
for(;i<total;i++)
{
keyValues.emplace(std::to_string(i),std::to_string(i));
}
std::cout<<"Key size is max "<<std::to_string(total-1).length( )<<" bytes"<<std::endl;

//2. Store 100 000 key-value pairs (no overlap)
//Raw storage speed
std::cout<<"========Set========"<<std::endl;
std::chrono::steady_clock::time_point begin=std::chrono::steady_clock::now( );
for(auto it=keyValues.begin( );it!=keyValues.end( );it++)
{
db->setKeyValue(it->first,it->second);
}
std::chrono::steady_clock::time_point end=std::chrono::steady_clock::now( );
std::cout<<" "<<keyValues.size( )<<" completed in "<<(std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )/1000000.0)<<" seconds"<<std::endl;
std::cout<<" "<<keyValues.size( )*1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<" requests per second"<<std::endl;

//3.Retrieve 100 000 key-value pairs (no overlap)
//Raw retirival speed
std::string aString("blank");
std::string &result(aString);
std::cout<<"========Get========"<<std::endl;
begin=std::chrono::steady_clock::now( );
for(auto it=keyValues.begin( );it!=keyValues.end( );it++)
{
result=db->getKeyValue(it->first);
}
end=std::chrono::steady_clock::now( );
std::cout<<" "<<keyValues.size( )<<" completed in "<<(std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )/1000000.0)<<" seconds"<<std::endl;
std::cout<<" "<<keyValues.size( )*1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<" requests per second"<<std::endl;

/*
Retrieve 100 random keys
BENCHMARK("GET 100 random keys")
{
return db->getKeyValue(std::to_string(rand( )%keyValues.size( )));
};
4. Retrieve the same 100 000 key-value pairs
Retrieval speed with 'warm cache' (if implemented any)
5. Store 50 000 key-value pairs UPDATES (so half of the data is 'new')(first half of db)
6. Retrieve the same 100 000 key-value pairs
Same as 4 if we write a 'write through cache',halfway between 4 and 3 otherwise
*We know that we have been successfull when :-
*We have min,max,var,total time for each group of opertions
*We have saved these results to a csv file for later comparison
Tear down
*/
std::cout<<"Test complete"<<std::endl;
db->destroy( );
}

SECTION("Store and retrieve 100 000 keys -In memory key-value store")
{
std::cout<<"=====In-memory key-value store performance test ====="<<std::endl;
std::string dbname("myemptydb");
std::unique_ptr<quickdb::KeyValueStore> memoryStore=std::make_unique<quickdbext::MemoryKeyValueStore>( );
std::unique_ptr<quickdb::IDatabase> db(quickdb::QuickDB::createEmptyDB(dbname,memoryStore));
int total=100000;
//1 Pre-generate the keys and values in memory(so we don't skew the test)
std::unordered_map<std::string,std::string> keyValues;
long i=0;
std::cout<<"Pre-generating key value pairs ..."<<std::endl;
for(;i<total;i++)
{
keyValues.emplace(std::to_string(i),std::to_string(i));
}
std::cout<<"Key size is max "<<std::to_string(total-1).length( )<<" bytes"<<std::endl;

//2. Store 100 000 key-value pairs (no overlap)
//Raw storage speed
std::cout<<"==========SET=========="<<std::endl;
std::chrono::steady_clock::time_point begin=std::chrono::steady_clock::now( );
for(auto it=keyValues.begin( );it!=keyValues.end( );it++)
{
db->setKeyValue(it->first,it->second);
}
std::chrono::steady_clock::time_point end=std::chrono::steady_clock::now( );
std::cout<<" "<<keyValues.size( )<<" completed in "<<(std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )/1000000.0)<<" seconds"<<std::endl;
std::cout << "  "
<< (keyValues.size() * 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())
<< " requests per second" << std::endl;

std::cout << std::endl;

// 3. Retrieve 100 000 key-value pairs (no overlap)

// Raw retrieval speed

std::string aString("blank");

std::string& result(aString);

std::cout << "====== GET ======"<< std::endl;

begin = std::chrono::steady_clock::now();

for (auto it = keyValues.begin();it != keyValues.end(); it++)
{

result = db->getKeyValue(it->first);

}

end = std::chrono::steady_clock::now();

std::cout << "  " << keyValues.size() << " completed in "
<< (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0)
<< " seconds" << std::endl;

std::cout << "  "
<< (keyValues.size() * 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())
<< " requests per second" << std::endl;

// 7. Tear down

std::cout << "Tests complete" << std::endl;

db->destroy();

}
 
// Now do the same for pure disc backed storage

SECTION("Store and Retrieve 100 000 keys - File based key-value store")
{

std::cout << "====== File based key-value store performance test ======" << std::endl;

std::string dbname("myemptydb");

std::string fullpath = ".quickdb/" + dbname;

std::unique_ptr<quickdb::KeyValueStore> fileStore = std::make_unique<quickdbext::FileKeyValueStore>(fullpath);

std::unique_ptr<quickdb::IDatabase> db(quickdb::QuickDB::createEmptyDB(dbname, fileStore));

int total = 100000;

// 1. Pre-generate the keys and values in memory (so we don't skew the test)

std::unordered_map<std::string,std::string> keyValues;

long i = 0;

std::cout << "Pre-generating key value pairs..." << std::endl;

for (; i < total;i++)
{

keyValues.emplace(std::to_string(i),std::to_string(i));
}

std::cout << "Key size is max " << std::to_string(total - 1).length() << " bytes" << std::endl;

// 2. Store 100 000 key-value pairs (no overlap)

// Raw storage speed

std::cout << "====== SET ======" << std::endl;

std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

for (auto it = keyValues.begin(); it != keyValues.end(); it++)
{

db->setKeyValue(it->first,it->second);

}
std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

std::cout << "  " << keyValues.size() << " completed in "
<< (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0)
<< " seconds" << std::endl;

std::cout << "  "<< (keyValues.size() * 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())
<< " requests per second" << std::endl;

std::cout << std::endl;

// 3. Retrieve 100 000 key-value pairs (no overlap)

// Raw retrieval speed

std::string aString("blank");

std::string& result(aString);

std::cout << "====== GET ======" << std::endl;

begin = std::chrono::steady_clock::now();

for (auto it = keyValues.begin(); it != keyValues.end(); it++)
{

result = db->getKeyValue(it->first);

}

end = std::chrono::steady_clock::now();

std::cout << "  " << keyValues.size() << " completed in "
<< (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0)
<< " seconds" << std::endl;

std::cout << "  "
<< (keyValues.size() * 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())
<< " requests per second" << std::endl;

// 7. Tear down

std::cout << "Tests complete" << std::endl;

db->destroy();

}

}
