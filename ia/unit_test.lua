dofile("global.lua")
dofile("socket.lua")
dofile("utils/utils_display.lua")
dofile("utils/utils_spec.lua")
dofile("utils/utils_parse.lua")
dofile("utils/utils_getters.lua")
dofile("utils/utils_bool.lua")
dofile("movements.lua")
dofile("execute_commands.lua")
dofile("analyse_reception.lua")
dofile("update.lua")
dofile("level.lua")

function execute_ia(x, y, level, orientation, host, port, team)
	X, Y, LEVEL, ORIENTATION = x, y, level, orientation

	local tab = parse_case("{nourriture 345, sibur 3, phiras 5, deraumere 0}\n")

	display_2dtab(tab)
	update_ressource(tab)
	display_tab(ITEM)

	local tcp = connect_server(host, port)
	if (tcp ~= nil) then print("connect_server OK") else print("connect_server FAILED") end

	local tab = parse_case("{ joueur nourriture mendiane,, linemate deraumere, deraumere, nourriture}\n")
	if (tab ~= nil) then print("parse_case OK");display_2dtab(tab) else print("parse_case FAILED") end

	-- recept_command(tcp)
	-- send_command(tcp, team)
	-- NUM_CLT = tonumber(recept_command(tcp))
	-- local tab = get_word(recept_command(tcp))
	-- X, Y = tab[1], tab[2]
	-- while (1) do
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "gauche")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "droite")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "gauche")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "droite")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- 	execute_cmd(tcp, "avance")
	-- end
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
