CC=gcc
CFLAGS= -std=c99
SCHESS = server/chess/

server: server/server

client: client/client

wrapper: wrapper/boardwrapper

server/server: $(SCHESS)board.o $(SCHESS)display.o server/player.o server/server.c server/server.h
	$(CC) $(CFLAGS) server/server.c $(SCHESS)board.o $(SCHESS)piece.o $(SCHESS)display.o server/player.o -o server/server

$(SCHESS)board.o: $(SCHESS)board.c $(SCHESS)piece.o $(SCHESS)display.o
	$(CC) $(CFLAGS) $(SCHESS)board.c -c -o $@;

$(SCHESS)display.o: $(SCHESS)display.c
	$(CC) $(SCHESS)display.c -c -o $@;

$(SCHESS)piece.o: $(SCHESS)display.c
	$(CC) $(SCHESS)piece.c -c -o $@;

server/player.o: server/player.c
	$(CC) server/player.c -c -o $@

client/client: client/clientview.o client/display.o client/client.c client/client.h client/instructions.o client/instructions.c
	$(CC) client/client.c client/clientview.o client/display.o client/instructions.o -o client/client

client/clientview.o: client/clientview.c client/clientview.h
	$(CC)  client/clientview.c -c -o $@

client/display.o: client/display.c
	$(CC) client/display.c -c -o $@

client/instructions.o: client/instructions.c client/instructions.h
	$(CC) client/instructions.c -c -o $@

wrapper/boardwrapper: $(SCHESS)board.o $(SCHESS)display.o wrapper/boardwrapper.c wrapper/boardwrapper.h
	$(CC) $(CFLAGS) wrapper/boardwrapper.c $(SCHESS)board.o $(SCHESS)piece.o $(SCHESS)display.o -o wrapper/boardwrapper
