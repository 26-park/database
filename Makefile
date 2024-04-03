FLAGS = -Werror -g

main.exe: database.o 
	g++ -o main.exe database.o database.h

database.o: database.cpp database.h
	g++ ${FLAGS} -c database.cpp

