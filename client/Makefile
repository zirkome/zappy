##
## Makefile for  in /home/fritsc_h/zappy/client
## 
## Made by Harold Fritsch
## Login   <fritsc_h@epitech.net>
## 
## Started on  Sun May  4 15:17:27 2014 Harold Fritsch
## Last update Thu May 15 11:07:32 2014 Harold Fritsch
##

CC 		=	g++

NAME 		=	client

LIBGDLDIR	=	./libGDL

LIBSOCKET	=	../libsocket

SRCDIR		=	src/
OBJDIR		= 	obj/
INCDIR		= 	-I./include -I../include -I$(LIBSOCKET)/include -I$(LIBGDLDIR)/includes

SRC 		=	main.cpp

OBJ		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS 	+=	-W -Wall -Wextra

LDFLAGS 	+=	-L$(LIBSOCKET) -L$(LIBGDLDIR)/libs/ -Wl,-whole-archive -lgdl_gl -Wl,-no-whole-archive -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -lsocket -ldl


dummy := $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@echo "- compilation of: $< (flag: "$(CXXFLAGS)")"
	@$(CC) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

$(NAME): $(OBJ)
	@echo "- linking of: $@ (flag: "$(LDFLAGS)")"
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
