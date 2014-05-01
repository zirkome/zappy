##
## Makefile for zappy in /home/kokaz/projects/tek2/unix/zappy
## 
## Made by guillaume fillon
## Login   <kokaz@epitech.net>
## 
## Started on  Thu May  1 16:49:19 2014 guillaume fillon
## Last update Thu May  1 16:49:20 2014 guillaume fillon
##

LIBSOCKET	= libsocket
CLIENT		= client
SERVER		= server

zappy:
	$(MAKE) -C $(LIBSOCKET)
	$(MAKE) -C $(CLIENT) BASEPATH=`pwd`
	$(MAKE) -C $(SERVER) BASEPATH=`pwd`

all: zappy

clean:
	$(MAKE) clean -C $(LIBSOCKET)
	$(MAKE) clean -C $(CLIENT)
	$(MAKE) clean -C $(SERVER)

fclean: clean
	$(MAKE) fclean -C $(LIBSOCKET)
	$(MAKE) fclean -C $(CLIENT)
	$(MAKE) fclean -C $(SERVER)

re: fclean all

.PHONY: all clean fclean re zappy