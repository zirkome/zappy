##
## Makefile for Makefile in /home/sinet_l/Documents/project/zappy/server
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Fri May  2 18:19:19 2014 luc sinet
## Last update Fri May  2 18:46:53 2014 luc sinet
##

CC 		= gcc

BINDIR		= ../bin/
NAME 		= server
BINPATH		= $(addprefix $(BINDIR), $(NAME))

COMMON		= common
COMMONDIR	= ../$(COMMON)
SRCDIR		= src/
OBJDIR		= obj/
INCDIR		= include/
SRCCOMMON	= $(COMMONDIR)/$(SRCDIR)
OBJCOMMON	= $(COMMONDIR)/$(OBJDIR)

SRC 		= main.c \
		  init.c

COMMONSRC	= error.c

OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))
COBJ		= $(addprefix $(OBJCOMMON), $(COMMONSRC:.c=.o))

LIBSOCKET	= ../libsocket

CFLAGS 		+= -W -Wall -Wextra -I../include -I$(LIBSOCKET)/include \
		   -I./include -I$(COMMONDIR)/$(INCDIR)

LDFLAGS 	+= -L$(LIBSOCKET) -lsocket

dummy := $(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
	 $(shell test -d $(OBJCOMMON) || mkdir $(OBJCOMMON)) \
	 $(shell test -d $(BINDIR) || mkdir $(BINDIR))

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "- compilation of: $< (flag: "$(CFLAGS)")"
	@$(CC) -o $@ -c $< $(CFLAGS)

$(OBJCOMMON)%.o: $(SRCCOMMON)%.c
	@echo "- compilation of: $< (flag: "$(CFLAGS)")"
	@$(CC) -o $@ -c $< $(CFLAGS)

$(BINPATH): $(OBJ) $(COBJ)
	@echo "- linking of: $@ (flag: "$(LDFLAGS)")"
	@$(CC) -o $(BINPATH) $(OBJ) $(COBJ) $(LDFLAGS)

all: $(BINPATH)

clean:
	rm -f $(OBJ) $(COBJ)

fclean: clean
	rm -f $(BINPATH)

re: fclean all
