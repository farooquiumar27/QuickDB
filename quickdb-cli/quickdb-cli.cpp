#include<iostream>
#include "cxxopts.hpp"
#include "quickdb/quickdb.h"
using namespace std;
using namespace quickdb;
cxxopts::Options options("quickdb-cli","CLI for QuickDB");
void printUsage(void)
{
cout<<"Whoops bad config!"<<endl;
}
int main(int argc,char* argv[ ])
{
//Grab command line parameters and determine code
options.add_options( )
("c,create","Create a DB")
("d,destroy","Destroy a DB")
("s,set","Set a key in a DB")
("g,get","Get a key from a DB")
("n,name","Database name(required)",cxxopts::value<std::string>( ))
("k,key","Key to set/get",cxxopts::value<std::string>( ))
("v,value","Value to set",cxxopts::value<std::string>( ))
;
auto result=options.parse(argc,argv);

if(result.count("c")==1)
{
if(result.count("n")==0)
{
cout<<"You must specify a database name with -n <name>"<<endl;
printUsage( );
return 1;
}
//create database
std::string dbname(result["n"].as<std::string>( ));
QuickDB::createEmptyDB(dbname);
return 0;
}

if(result.count("s")==1)
{
if(result.count("n")==0)
{
cout<<"You must specify a database name with -n <name>"<<endl;
printUsage( );
return 1;
}
if(result.count("k")==0)
{
cout<<"You must specify a key to set with -k <key>"<<endl;
printUsage( );
return 1;
}
if(result.count("v")==0)
{
cout<<"You must specify a value to set with -v <value>"<<endl;
printUsage( );
return 1;
}
//Set key value in database
std::string dbname(result["n"].as<std::string>( ));
std::string k(result["k"].as<std::string>( ));
std::string v(result["v"].as<std::string>( ));
std::unique_ptr<IDatabase> db(QuickDB::loadDB(dbname));
db->setKeyValue(k,v);
return 0;
}

if(result.count("g")==1)
{
if(result.count("n")==0)
{
cout<<"You must specify a database name with -n <name>"<<endl;
printUsage( );
return 1;
}
if(result.count("k")==0)
{
cout<<"You must specify a key to set with -k <key>"<<endl;
printUsage( );
return 1;
}
//Get key value from database
std::string dbname(result["n"].as<std::string>( ));
std::string k(result["k"].as<std::string>( ));
std::unique_ptr<IDatabase> db(QuickDB::loadDB(dbname));
std::cout<<db->getKeyValue(k)<<std::endl;
return 0;
}

if(result.count("d")==1)
{
if(result.count("n")==0)
{
cout<<"You must specify a database name with -n <name>"<<endl;
printUsage( );
return 1;
}
//Destroy database
std::string dbname(result["n"].as<std::string>( ));
std::unique_ptr<IDatabase> db(QuickDB::loadDB(dbname));
db->destroy( );
return 0;
}
cout<<"No commands specified"<<endl;
printUsage( );
return 1;
}