##
## Makefile for Makefile in /home/sinet_l/Documents/project/zappy/server
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Fri May  2 18:19:19 2014 luc sinet
## Last update Fri Jul  4 00:33:16 2014 luc sinet
##

CC 		= gcc

BINDIR		= ../bin/
NAME 		= zappyd
BINPATH		= $(addprefix $(BINDIR), $(NAME))

COMMON		= common
COMMONDIR	= ../$(COMMON)
SRCDIR		= src/
OBJDIR		= obj/
INCDIR		= include/
SRCCOMMON	= $(COMMONDIR)/$(SRCDIR)
OBJCOMMON	= $(COMMONDIR)/$(OBJDIR)
LIBSOCKET	= ../libsocket

SRC 		= main.c \
		  generic_list.c \
		  init.c \
		  welcome.c \
		  map.c \
		  map_box.c \
		  map_player.c \
		  client.c \
		  events_handling.c \
		  connection.c \
		  getopt.c \
		  util.c \
		  epoll.c \
		  monitoring.c \
		  parse.c \
		  parse_type.c \
		  player_actions.c \
		  player_commands.c \
		  player_movement.c \
		  player_broadcast.c \
		  player_view.c \
		  player_inventory.c \
		  player_incantation.c \
		  player_life.c \
		  incantation_calcul.c \
		  incantation_ressources.c \
		  geometry.c \
		  broadcast_calculs.c \
		  strings.c \
		  vectors.c \
		  vectors_get.c \
		  gui_misc.c \
		  gui_map.c \
		  gui_player.c \
		  gui_time.c \
		  authentication.c \
		  scheduler.c \
		  time.c

COMMONSRC	= error.c

OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))
COBJ		= $(addprefix $(OBJCOMMON), $(COMMONSRC:.c=.o))

CFLAGS 		+= -g -W -Wall -Wextra
CFLAGS		+= -I../include -I./include -I$(COMMONDIR)/$(INCDIR) -I$(LIBSOCKET)/$(INCDIR)

LDFLAGS 	= -Wl,-O2 -L$(LIBSOCKET) -lsocket -lm

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
