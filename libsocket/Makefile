##
## Makefile for nibbler in /home/maxime/projet/actu/cpp_nibbler
##
## Made by Maxime
## Login   <maxime@epitech.net>
##
## Started on  Wed Mar 12 15:15:11 2014 guillaume fillon
## Last update Thu May  1 16:23:33 2014 luc sinet
##

CC 	= gcc

NAME 	= libsocket.so

SRCDIR	= src/
OBJDIR	= obj/

SRC 	= accept_inet.c  \
	  connect_inet.c \
	  read_socket_inet.c \
	  socket_inet.c \
	  bind_inet.c \
	  receivefile.c \
	  create_inet_stream_socket.c \
	  create_inet_server_socket.c \
	  write_socket_inet.c \
	  ringbuffer.c

OBJ	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

CFLAGS 	+= -Iinclude -W -Wall -Wextra -fPIC
LDFLAGS += -shared

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
