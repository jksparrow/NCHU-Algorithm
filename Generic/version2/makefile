SHELL=cmd.exe
OBJS=main.o GA.o
main: $(OBJS)
	g++ -o search $(OBJS)
main.o: main.cpp GA.h
	g++ -c main.cpp
GA.o: GA.cpp GA.h
	g++ -c GA.cpp
clean:
	del $(OBJS)