dofile("global.lua")
dofile("socket.lua")
dofile("utils_display.lua")
dofile("utils_math.lua")
dofile("utils_parse.lua")
dofile("movements.lua")
dofile("get_cmd.lua")
dofile("update.lua")

function execute_ia(x, y, level, orientation, host, port)
	local tcp = connect_server(host, port)
	local tab = parse_case("{nourriture 345, sibur 3, phiras 5, deraumere 0}\n")

	display_2dtab(tab)
	update_ressource(tab)
	display_item()
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
