g++ -c quickdb-cli.cpp -I../ -o quickdb-cli.o
g++ -o quickdb-cli.exe quickdb-cli.o -L../quickdb -l:quickdb.a