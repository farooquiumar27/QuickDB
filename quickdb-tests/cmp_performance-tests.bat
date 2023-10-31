g++ -c performance-tests.cpp -I../ -I../quickdb/include/extensions/ -o performance-tests.o
g++ -o performance-tests.exe performance-tests.o  -L../quickdb -l:quickdb.a
