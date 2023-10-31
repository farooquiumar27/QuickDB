#include "tests.h"
#include "quickdb/quickdbext.h"
#include "highwayhash/highwayhash.h"

#include<unordered_map>

TEST_CASE("Test unoredered_map custom hashing algorithms","[set,get]")
{
SECTION("Produces known expected value from known input")
{
quickdbext::HighwayHash h;
std::string text("Known");
std::size_t r=h(text);
using namespace highwayhash;
const HHKey key HH_ALIGNAS(64)={1,2,3,4};
HHResult64 result;
HHStateT<HH_TARGET> state(key);
HighwayHashT(&state,text.c_str( ),text.length( ),&result);
REQUIRE(result==r);
}
SECTION("Privious hash dosen't affect next hash result")
{
quickdbext::HighwayHash hfirst;
std::size_t rfirst=hfirst("OtherThings");
quickdbext::HighwayHash h;
std::size_t r1=h("Known");
std::size_t r2=h("OtherThings");
REQUIRE(r1!=r2);
REQUIRE(r1!=rfirst);
REQUIRE(rfirst==r2);
}
SECTION("Different seed keys produce different result for the same input")
{
quickdbext::HighwayHash h1{1,2,3,4};
std::size_t r1=h1("AThing");
quickdbext::HighwayHash h2{5,6,7,8};
std::size_t r2=h2("AThing");
REQUIRE(r1!=r2);
}

SECTION("Unordered map works as expected with custom hash")
{
std::unordered_map<std::string,std::string,quickdbext::HighwayHash> m;

std::string key("A very sensibile key name");
std::string value("A very valuable value");
std::string k2("Some other key");
std::string v2("Another value");
m.emplace(key,value);
m.emplace(k2,v2);
REQUIRE(m[key]==value);
REQUIRE(m[k2]==v2);
}

}