#include <iostream>
#include <chrono>
#include <string>
#include <unordered_map>

int main( )
{
//Store 79500 items in memory of random length
char *buffer;
int bufferLength=32;
int storeSize=79500; //Number of record in our database

//OPTION 1 : Store unsorted
unsigned short int chosen=(storeSize/4)*3+1;
std::string chosenString;
std::string* stringPtrArray[storeSize];
int ci=0;
std::chrono::steady_clock::time_point begin=std::chrono::steady_clock::now( );
for(int idx=0;idx<storeSize;idx++)
{
buffer=new char[bufferLength+1];  //termination \0
for(ci=0;ci<bufferLength;ci++)
{
buffer[ci]=(rand( )%26)+'a'; //random character from a to z
}
buffer[bufferLength]='\0';
stringPtrArray[idx]=new std::string(buffer);
if(chosen==idx)
{
chosenString=*stringPtrArray[idx];  //copy constructor
}
} 

//Storage time?
std::chrono::steady_clock::time_point end=std::chrono::steady_clock::now( );
std::cout<<"Stroage Time difference ="<<std::chrono::duration_cast<std::chrono::milliseconds>(end -begin).count( )<<"[ms]"<<std::endl;
std::cout<<"Stroage Time difference ="<<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<"[myus]"<<std::endl;
std::cout<<"Storage Time difference ="<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count( )<<"[ns]"<<std::endl;

//OPTION 1a: Retrieve by key name
int retrieveIdx;
//Pull back a random one by key name(similar to a search by the string in K-V store)
begin=std::chrono::steady_clock::now( );
for(int idx=0;idx<storeSize;idx++)
{
if(chosenString ==*stringPtrArray[idx])
{
retrieveIdx=idx;
break; //end loop early
}
}
end=std::chrono::steady_clock::now( );
std::cout<<"Value at 0 : "<<*stringPtrArray[0]<<std::endl;
std::cout<<"Value at 1 : "<<*stringPtrArray[1]<<std::endl;
std::cout<<"Retrieved : "<<*stringPtrArray[retrieveIdx]<<" at index "<<retrieveIdx<<std::endl;
std::cout<<"Retrieval by name : Time difference = "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count( )<<"[ms]"<<std::endl;
std::cout<<"Retrieval by name : Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<"[myus]"<<std::endl;
std::cout<<"Retrieval by name : Time difference = "<<std::chrono::duration_cast<std::chrono ::nanoseconds>(end-begin).count( )<<"[ns]"<<std::endl;

//OPTION 1b : Retrieve by known key index(position)
std::string recieved;
begin=std::chrono::steady_clock::now( );
recieved=*stringPtrArray[chosen];
end=std::chrono::steady_clock::now( );
std::cout<<"Retrieved : "<<recieved<<std::endl;
std::cout<<"Retrieved by index : Time difference = "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count( )<<"[ms]"<<std::endl;
std::cout<<"Retrieved by index : Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<"[myu]"<<std::endl;
std::cout<<"Retrieved by index : Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count( )<<"[ns]"<<std::endl;

//OPTION 2 : Store by the hash of a key in a efficient (Olog(n))unordered map
//Now do the same for hash table variant
//Hash table -> Convert type (string) to a hash number , store data at hash index and retieve data by hash index
//Use built in hash map type in C++ for this
std::unordered_map<std::string,std::string> keyValueStore;
std::string key;
std::string randomValue="pathaan";
begin=std::chrono::steady_clock::now( );
for(int idx=0;idx<storeSize;idx++)
{
buffer=new char[bufferLength]+1;
for(ci=0;ci<bufferLength;ci++)
{
buffer[ci]=(rand( )%26)+'a';
}
buffer[bufferLength]='\0';
key=std::string(buffer);
keyValueStore.insert({key,randomValue});
if(chosen==idx)
{
chosenString=key;  //copy constructor
}
}
end=std::chrono::steady_clock::now( );
std::cout<<"MapStore : Time difference = "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count( )<<"[ms]"<<std::endl;
std::cout<<"MapStore : Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<"[myu]"<<std::endl;
std::cout<<"MapStore : Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count( )<<"[ns]"<<std::endl;

//OPTION 2 : Retrival time
begin=std::chrono::steady_clock::now( );
auto kvpair=keyValueStore.find(chosenString);
std::string retKey=kvpair->first;  //first is key
std::string retValue=kvpair->second;  //second is value
end=std::chrono::steady_clock::now( );
std::cout<<"Retrieved key : "<<retKey<<" with value : "<<retValue<<std::endl;
std::cout<<"Retireved from Map : Time difference = "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count( )<<"[ms]"<<std::endl;
std::cout<<"Retreived from Map : Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count( )<<"[myus]"<<std::endl;
std::cout<<"Retreived from Map : Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count( )<<"[ns]"<<std::endl;
return 0;
}
