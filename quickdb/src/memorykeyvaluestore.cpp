#include "extensions/extdatabase.h"
#include "extensions/highwayhash.h"
#include<unordered_map>
#include<optional>
#include<iostream>
namespace quickdbext
{
class MemoryKeyValueStore::Impl
{
public:
Impl( );
Impl(std::unique_ptr<KeyValueStore>& toCache);
~Impl( );
std::unordered_map<std::string,std::string,HighwayHash> m_keyValueStore;
std::optional<std::unique_ptr<KeyValueStore>> m_cachedStore;
};

MemoryKeyValueStore::Impl::Impl( )
: m_keyValueStore( ) , m_cachedStore( )
{
;
}
MemoryKeyValueStore::Impl::Impl(std::unique_ptr<KeyValueStore>& toCache)
: m_keyValueStore( ) , m_cachedStore(toCache.release( ))
{
;
}
MemoryKeyValueStore::Impl::~Impl( )
{
;
}

MemoryKeyValueStore::MemoryKeyValueStore( )
: mImpl(std::make_unique<MemoryKeyValueStore::Impl>( ))
{
;
}
MemoryKeyValueStore::MemoryKeyValueStore(std::unique_ptr<KeyValueStore> &toCache)
: mImpl(std::make_unique<MemoryKeyValueStore::Impl>(toCache))
{
mImpl->m_cachedStore->get( )->loadKeysInfo([this](std::string key,std::string value){
mImpl->m_keyValueStore.insert({key,value});
});
}
MemoryKeyValueStore::~ MemoryKeyValueStore( )
{
;
}
void MemoryKeyValueStore::setKeyValue(std::string key,std::string value)
{
mImpl->m_keyValueStore.insert({key,value});
if(mImpl->m_cachedStore)
{
mImpl->m_cachedStore->get( )->setKeyValue(key,value);
}
}
std::string MemoryKeyValueStore::getKeyValue(std::string key)
{
const auto &it=mImpl->m_keyValueStore.find(key);
if(it==mImpl->m_keyValueStore.end( ))
{
return "";
}
return it->second;
}
void MemoryKeyValueStore::loadKeysInfo(std::function<void(std::string key,std::string value)> callback)
{
for(auto it : mImpl->m_keyValueStore)
{
callback(it.first,it.second);
}
}
void MemoryKeyValueStore::clear( )
{
mImpl->m_keyValueStore.clear( );
if(mImpl->m_cachedStore)
{
mImpl->m_cachedStore->get( )->clear( );
}
}

}