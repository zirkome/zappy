dofile("global.lua")
dofile("socket.lua")
dofile("utils/utils_display.lua")
dofile("utils/utils_spec.lua")
dofile("utils/utils_parse.lua")
dofile("movements.lua")
dofile("commands.lua")
dofile("update.lua")

function execute_ia(x, y, level, orientation, host, port)
	X, Y, LEVEL, ORIENTATION = x, y, level, orientation

	local tcp = connect_server(host, port)
	if (tcp ~= nil) then print("connect_server OK") else print("connect_server FAILED") end

	local tab = parse_case("{nourriture 345, sibur 3, phiras 5, deraumere 0, mendiane 0, linemate 0, phiras 0, thystame 0}\n")
	if (tab ~= nil) then print("parse_case OK");display_2dtab(tab) else print("parse_case FAILED") end

	recept_command(tcp)
	send_command(tcp, "toto")
	recept_command(tcp)
	recept_command(tcp)
	while (1) do
		avance(tcp)
		print("forward : " .. X .. " " .. Y)
		droite(tcp)
		print("right : " .. X .. " " .. Y)
		avance(tcp)
		print("forward : " .. X .. " " .. Y)
		avance(tcp)
		print("forward : " .. X .. " " .. Y)
		avance(tcp)
		print("forward : " .. X .. " " .. Y)
		gauche(tcp)
		print("right : " .. X .. " " .. Y)
		avance(tcp)
		print("forward : " .. X .. " " .. Y)
		avance(tcp)
		print("forward : " .. X .. " " .. Y)
	end
	close_server(tcp)
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
