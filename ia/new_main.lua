dofile("global.lua")
dofile("socket.lua")
dofile("movements.lua")
dofile("execute_commands.lua")
dofile("analyse_reception.lua")
dofile("update.lua")
dofile("level.lua")
dofile("utils/utils_display.lua")
dofile("utils/utils_spec.lua")
dofile("utils/utils_parse.lua")
dofile("utils/utils_getters.lua")
dofile("utils/utils_bool.lua")

function execute_ia(x, y, level, orientation, host, port, team)
	local tcp = connect_server(host, port)
	recept_command(tcp)
	send_command(tcp, team)
	NUM_CLT = tonumber(recept_command(tcp))
	local tab = parse_word(recept_command(tcp))
	X, Y = tab[1], tab[2]
	local current_state = 42
	local value = OK

	while (value ~= ERROR) do
		current_state = WALTROUGHT_STATEMENT[current_state][value]
		value = FUNCTION_STATEMENT[current_state](tcp)
	end
	close_server(tcp)
	return 0
end

function main_prg()
	local host = arg[1]
	local port = arg[2]
	local team = arg[3]
	if (host ~= nil and port ~= nil and is_valid_ipv4(host) == 0 and team ~= nil) then
		return execute_ia(1, 1, 1, 1, host, port, team)
	else
		print("Usage: lua5.2 ia.out <host> <port> <team>")
		return 1
	end
end

return main_prg()
