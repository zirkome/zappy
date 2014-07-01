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

	while (1) do
		local inventaire = execute_cmd(tcp, "inventaire")
		if (remain_players() == true) then
			execute_cmd(tcp, "fork")
		elseif (ready_to_levelup() == true) then
			execute_cmd(tcp, "incantation")
		elseif (inventaire ~= -42) then
			update_ressource(parse_case(inventaire))
			local view = execute_cmd(tcp, "voir")
			if (view ~= -42) then
				tab = parse_case(view)
				local case, where = update_ressource_if(tab)
				if (case ~= false) then
					if (where == 1) then
						execute_cmd(tcp, "prend", case)
					else
						if (determine_way_to(where) == "gauche") then
							execute_cmd(tcp, "gauche")
							execute_cmd(tcp, "avance")
							execute_cmd(tcp, "droite")
						elseif (determine_way_to(where) == "droite") then
							execute_cmd(tcp, "droite")
							execute_cmd(tcp, "avance")
							execute_cmd(tcp, "gauche")
						elseif (determine_way_to(where) == "avance") then
							execute_cmd(tcp, "avance")
						end
					end
				else
					if (need_to_fork() == true) then
						execute_cmd("fork")
					else
						local case = get_case_on(tab, "nourriture")
						if (case ~= false) then
							if (case == 1) then
								execute_cmd(tcp, "prend", "nourriture")
							else
								random_moove(tcp)
							end
						else
							random_moove(tcp)
						end
					end
				end
			else
				random_moove(tcp)
			end
		else
			random_moove(tcp)
		end
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
