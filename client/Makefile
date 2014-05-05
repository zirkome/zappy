##
## Makefile for  in /home/fritsc_h/zappy/client
## 
## Made by Harold Fritsch
## Login   <fritsc_h@epitech.net>
## 
## Started on  Sun May  4 15:17:27 2014 Harold Fritsch
## Last update Sun May  4 21:38:36 2014 Harold Fritsch
##

CC 		=	g++

NAME 		=	client

LIBGDLDIR	=	./libGDL

LIBSOCKET	=	../libsocket

SRCDIR		=	src/
OBJDIR		= 	obj/
INCDIR		= 	-I./include/ -I../include -I$(LIBSOCKET)/include -I$(LIBGDLDIR)/includes

SRC 		=	main.cpp \
			Cube.cpp \
			Player.cpp \
			AObject.cpp \
			Exception.cpp \
			LaunchGfx.cpp \
			GameEngine.cpp \
			ModelObject.cpp \
			Camera.cpp

OBJ		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS 	+=	-W -Wall -Wextra

LDFLAGS 	+=	-L$(LIBSOCKET) -lsocket -L$(LIBGDLDIR)/libs/ -Wl,-whole-archive -lgdl_gl -Wl,-no-whole-archive -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -ldl


dummy := $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@echo "- compilation of: $< (flag: "$(CXXFLAGS)")"
	@$(CC) -o $@ -c $< $(CXXFLAGS) $(INCDIR) $(LDFLAGS)

$(NAME): $(OBJ)
	@echo "- linking of: $@ (flag: "$(LDFLAGS)")"
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
