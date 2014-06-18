##
## Makefile for  in /home/fritsc_h/zappy/client
## 
## Made by Harold Fritsch
## Login   <fritsc_h@epitech.net>
## 
## Started on  Sun May  4 15:17:27 2014 Harold Fritsch
## Last update Wed Jun 18 12:25:26 2014 Parallels
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

LDFLAGS		+=	-L$(LIBGDLDIR)/libs/
LDFLAGS		+=	-lgdl_gl -lGL -lGLEW -lfbxsdk -llua -lSDL2_mixer -lSDL2 -lpthread -lm -ldl -lrt

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
