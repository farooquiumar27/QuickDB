#include<iostream>
#include<filesystem>
#include<iostream>
#include<fstream>
#include "extensions/extdatabase.h"
namespace fs=std::filesystem;
namespace quickdbext
{

class FileKeyValueStore::Impl
{
public:
Impl(std::string fullpath);
std::string m_fullpath;
};

FileKeyValueStore::Impl::Impl(std::string fullpath)
: m_fullpath(fullpath) 
{
;
}

FileKeyValueStore::FileKeyValueStore(std::string fullpath)
: mImpl(std::make_unique<FileKeyValueStore::Impl>(fullpath))
{
if(!fs::exists(fullpath))
{
fs::create_directory(fullpath);
}
}
FileKeyValueStore::~FileKeyValueStore( )
{
;
}

void FileKeyValueStore::setKeyValue(std::string key,std::string value)
{
std::string path;
path=mImpl->m_fullpath+"/"+key+"_string.kv";
std::ofstream os;
os.open(path,std::ios::out | std::ios::trunc);
os<<value;
os.close( );
}

std::string FileKeyValueStore::getKeyValue(std::string key)
{
std::string path;
path=mImpl->m_fullpath+"/"+key+"_string.kv";
std::ifstream is;
is.open(path);
std::string value;
is.seekg(0,std::ios::end);
value.reserve(is.tellg( ));
is.seekg(0,std::ios::beg);
value.assign(std::istreambuf_iterator<char>(is),std::istreambuf_iterator<char>( ));
return value;
}

void FileKeyValueStore::loadKeysInfo(std::function<void(std::string key,std::string value)> callback)
{
for(auto &p : fs::directory_iterator(mImpl->m_fullpath))
{
if(p.exists( ) && p.is_regular_file( ))
{
if(p.path( ).extension( )==".kv")
{
std::string keyWithString=p.path( ).filename( ).u8string( );
std::string key=keyWithString.substr(0,keyWithString.length( )-10);
std::ifstream is(p.path( ));
std::string value;
is.seekg(0,std::ios::end);
value.reserve(is.tellg( ));
is.seekg(0,std::ios::beg);
value.assign(std::istreambuf_iterator<char>(is),std::istreambuf_iterator<char>( ));
callback(key,value);
}
}
}
}

void FileKeyValueStore::clear( )
{
if(fs::exists(mImpl->m_fullpath))
{
fs::remove_all(mImpl->m_fullpath);
}
}
}