SRC = 	main.lua \
	utils_math.lua \
	global.lua \
	view.lua \
	movements.lua \
	socket.lua \
	utils.lua

NAME = ia.out

LUA = luac5.2

all:
	$(LUA) -o $(NAME) $(SRC)

clean:
	rm -rf ia.out
