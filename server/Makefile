##
## Makefile for MyFTP in /home/kokaz/projects/tek2/unix/PSU_2013_myftp
## 
## Made by guillaume fillon
## Login   <kokaz@epitech.net>
## 
## Started on  Sat Mar 22 23:12:17 2014 guillaume fillon
## Last update Fri May  2 09:49:54 2014 luc sinet
##

CC 		= gcc

NAME 		= server

SRCDIR		= src/
OBJDIR		= obj/

SRC 		= main.c \
		  init.c \
		  error.c

OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))

LIBSOCKET	= ../libsocket

CFLAGS 		+= -W -Wall -Wextra -I../include -I$(LIBSOCKET)/include -I./include

LDFLAGS 	+= -L$(LIBSOCKET) -lsocket

dummy := $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "- compilation of: $< (flag: "$(CFLAGS)")"
	@$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
	@echo "- linking of: $@ (flag: "$(LDFLAGS)")"
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
