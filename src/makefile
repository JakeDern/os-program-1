CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out

all: main.o ArgReader.o Parser.o ProcessFetcher.o
	$(CC) -o $(EXE) main.o ArgReader.o ProcessFetcher.o Parser.o

main.o: main.c 
	$(CC) $(WARNING_FLAGS) -c main.c

ArgReader.o:  
	$(CC) $(WARNING_FLAGS) -c ./modules/ArgReader.c

ProcessFetcher.o: 
	$(CC) $(WARNING_FLAGS) -c ./modules/ProcessFetcher.c

Parser.o:  
	$(CC) $(WARNING_FLAGS) -c ./modules/Parser.c

clean:
	rm $(EXE) *.o

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
