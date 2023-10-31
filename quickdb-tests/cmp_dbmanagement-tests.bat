g++ -c dbmanagement-tests.cpp -I../ -o dbmanagement-tests.o
g++ -o dbmanagement-tests.exe dbmanagement-tests.o  -L../quickdb -l:quickdb.a
