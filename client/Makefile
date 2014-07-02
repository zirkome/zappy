##
## Makefile for  in /home/fritsc_h/zappy/client
##
## Made by Harold Fritsch
## Login   <fritsc_h@epitech.net>
##
## Started on  Sun May  4 15:17:27 2014 Harold Fritsch
## Last update Wed Jul  2 23:57:38 2014 enzo de gregorio
##

CC 		=	g++

NAME 		=	client

LIBGDL		=	./libGDL

LIBSOCKET	=	../libsocket

SRCDIR		=	src/
OBJDIR		= 	obj/
INCDIR		= 	-I./include/ -I../include/ -I$(LIBSOCKET)/include/ -I$(LIBGDL)/includes/

SRC 		=	main.cpp \
			GameEngine.cpp \
			ATransformation.cpp \
			Camera.cpp \
			Cube.cpp \
			Exception.cpp \
			GNetwork.cpp \
			Protocol.cpp \
			Map.cpp \
			Mutex.cpp \
			Input.cpp \
			Menu.cpp \
			Settings.cpp \
			Text.cpp \
			Square.cpp \
			AWidget.cpp \
			ImageWidget.cpp \
			QuitWidget.cpp \
			TextWidget.cpp \
			TextImgWidget.cpp \
			LoadWidget.cpp \
			InputWidget.cpp \
			ConnectWidget.cpp


OBJ		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS 	+=	-W -Wall -Wextra -g

LDFLAGS		+=	-L$(LIBGDL)/libs/ -lgdl_gl -lGLEW -lGL -lfbxsdk -lSDL2 -lpthread -lm -ldl -lrt
LDFLAGS		+=	-Wl,-O2 -L$(LIBSOCKET)/ -lsocket


dummy := $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@echo "- compilation of: $< (flag: "$(CXXFLAGS)")"
	@$(CC) -o $@ -c $< $(INCDIR) $(CXXFLAGS)

$(NAME): $(OBJ)
	@echo "- linking of: $@ (flag: "$(LDFLAGS)")"
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
