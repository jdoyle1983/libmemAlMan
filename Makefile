CC = gcc -g
AR = ar

INC = -Iinclude -Isrc
LIB = -Llib

STATIC_OBJDIR = obj/memAlMan/static
STATIC_OBJ = $(STATIC_OBJDIR)/Manager.o $(STATIC_OBJDIR)/Client.o
STATIC_CFLAGS = -Wall -O2
STATIC_BIN = lib/libmemAlMan.a

SHARED_OBJDIR = obj/memAlMan/shared
SHARED_OBJ = $(SHARED_OBJDIR)/Manager.o $(SHARED_OBJDIR)/Client.o
SHARED_CFLAGS = -Wall -fPIC -DBUILDINGDLL
SHARED_BIN = lib/libmemAlMan.so

all: static shared

static: $(STATIC_BIN)

shared: $(SHARED_BIN)

clean:
	rm -f $(STATIC_BIN)
	rm -f $(SHARED_BIN)
	rm -f $(STATIC_OBJDIR)/*.o
	rm -f $(SHARED_OBJDIR)/*.o
	
$(STATIC_BIN): $(STATIC_OBJ)
	$(AR) rcs $(STATIC_BIN) $(STATIC_OBJ)
	
$(SHARED_BIN): $(SHARED_OBJ)
	$(CC) -shared $(SHARED_OBJ) -o $(SHARED_BIN)
	
$(STATIC_OBJDIR)/Manager.o: src/Manager.c
	$(CC) $(STATIC_CFLAGS) $(INC) -c src/Manager.c -o $(STATIC_OBJDIR)/Manager.o
	
$(STATIC_OBJDIR)/Client.o: src/Client.c
	$(CC) $(STATIC_CFLAGS) $(INC) -c src/Client.c -o $(STATIC_OBJDIR)/Client.o
	
$(SHARED_OBJDIR)/Manager.o: src/Manager.o
	$(CC) $(SHARED_CFLAGS) $(INC) -c src/Manager.c -o $(SHARED_OBJDIR)/Manager.o
	
$(SHARED_OBJDIR)/Client.o: src/Client.c
	$(CC) $(SHARED_CFLAGS) $(INC) -c src/Client.c -o $(SHARED_OBJDIR)/Client.o
	