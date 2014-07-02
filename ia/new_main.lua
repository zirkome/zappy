dofile("global.lua")
dofile("socket.lua")
dofile("movements.lua")
dofile("execute_commands.lua")
dofile("analyse_reception.lua")
dofile("update.lua")
dofile("level.lua")
dofile("fork.lua")
dofile("utils/utils_display.lua")
dofile("utils/utils_spec.lua")
dofile("utils/utils_parse.lua")
dofile("utils/utils_getters.lua")
dofile("utils/utils_bool.lua")

function get_beginning(tcp, team)
	recept_command(tcp)
	send_command(tcp, team)
	recept_command(tcp)
	NUM_CLT = tonumber(CURRENT_RES)
	recept_command(tcp)
end

function execute_ia(x, y, level, orientation, host, port, team)
	local tcp = connect_server(host, port)
	get_beginning(tcp, team)
	local tab = parse_word(CURRENT_RES)
	X, Y = tab[1], tab[2]

	local current_state = 42
	local value = OK
	local walktrought_statement = get_tab_walk()
	local function_statement = get_tab_func()

	while (value ~= ERROR) do
		current_state = walktrought_statement[current_state][value]
		print(get_pid(), "STATEMENT FUNCTION : ", current_state)
		value = function_statement[current_state](tcp)
		CURRENT_RES = nil
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
