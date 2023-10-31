g++ -c hashing-tests.cpp -I ../ -I../quickdb/include/extensions/ -o hashing-tests.o
g++ -o hashing-tests.exe hashing-tests.o -L ../quickdb -l:quickdb.a
