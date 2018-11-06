SHELL=cmd.exe
OBJS=main.o TS.o
main: $(OBJS)
	g++ -o search $(OBJS)
main.o: main.cpp TS.h
	g++ -c main.cpp
TS.o: TS.cpp TS.h
	g++ -c TS.cpp
clean:
	del $(OBJS)