##
## Makefile for nibbler in /home/maxime/projet/actu/cpp_nibbler
##
## Made by Maxime
## Login   <maxime@epitech.net>
##
## Started on  Wed Mar 12 15:15:11 2014 guillaume fillon
## Last update Sat May  3 15:37:43 2014 luc sinet
##

CC 	= gcc

NAME 	= libsocket.a

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
	  ringbuffer.c \
	  queue.c \
	  manage_queue.c

OBJ	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

CFLAGS 	+= -Iinclude -W -Wall -Wextra -fPIC
LDFLAGS +=

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(AR) rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
