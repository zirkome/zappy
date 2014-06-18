dofile("global.lua")
dofile("socket.lua")
dofile("utils.lua")
dofile("utils_math.lua")
dofile("view.lua")
dofile("movements.lua")

function execute_ia(x, y, level, orientation, host, port)
	local tcp = connect_server(host, port)
	local cmd = nil

	-- implement that when server could send responses
	-- while 1 == 1 do
	-- 	local str = io.read("*line")
	-- 	print_bkt("Typing : ", str)
	-- 	send_command(tcp, str)
	-- 	if (recept_command(tcp) == nil) then return 1 end
	-- end

	local tab = view("{coco,,, phalis,,,, joueur deraumere, joueur joueur phalis, genial aussi,,,,,lol}")
	display_2dtab(tab)
	return 0
end

function main_prg()
	local host = arg[1]
	local port = arg[2]
	if (host ~= nil and port ~= nil and is_valid_ipv4(host) == 0) then
		return execute_ia(1, 1, 1, 1, host, port)
	else
		print("Usage: lua5.2 ia.out <host> <port>")
		return 1
	end
end

return main_prg()