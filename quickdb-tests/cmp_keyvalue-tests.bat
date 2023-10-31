g++ -c keyvalue-tests.cpp -I../ -o keyvalue-tests.o
g++ -o keyvalue-tests.exe keyvalue-tests.o -L../quickdb -l:quickdb.a