function need_to_fork()
	local tab = get_tab_level()

	if (ITEM["nourriture"] < 10) then
		FOOD_FORK = true
		return NEED_FOOD
	elseif (tab[LEVEL]["joueur"] > ITEM["joueur"]) then
		return OK
	else
		return KO
	end
end

function ready_to_levelup()
	local tab = get_tab_level()

	for k, v in pairs(tab[LEVEL]) do
		if (tab[LEVEL][k] > ITEM[k]) then
			return false
		end
	end
	return true
end

function enought_food(tcp)
	execute_command(tcp, "inventaire")
	update_ressource(UPDATE_INVENTORY)
	if ((ITEM["nourriture"] < 5 and REGAIN_FOODS == false) or FOOD_FORK == true) then
		REGAIN_FOODS = true
		return KO
	elseif (REGAIN_FOODS == true and ITEM["nourriture"] < 15) then
		return KO
	else
		if (ITEM["nourriture"] == 15) then
			REGAIN_FOODS = false
			FOOD_FORK = false
		end
		return OK
	end
end

function team_message()
	if (#BROADCAST > 0) then
		return OK
	else
		return KO
	end
end

function determine_way_broadcast(tcp)
	if (CURRENT_K ~= nil) then
		local tab = {
			[1] = "avance",
			[2] = "gauche avance",
			[3] = "gauche avance",
			[4] = "gauche avance",
			[5] = "gauche gauche",
			[6] = "droite avance",
			[7] = "droite avance",
			[8] = "droite avance"
		}
		if (CURRENT_K ~= 0) then
			execute_movements(tcp, tab[CURRENT_K])
			CURRENT_K = nil
			return CURRENT_RES
		else
			execute_movements(tcp, "avance")
			return CURRENT_RES
		end
	end
	return KO
end

function reach_destination(tcp)
	if (CURRENT_K == 0) then
		ITEM["joueur"] = ITEM["joueur"] + 1
		return OK
	else
		return KO
	end
end

function enought_trantorian()
	local tab = get_tab_level()

	if (ITEM["joueur"] == tab[LEVEL]["joueur"]) then
		return OK
	else
		return KO
	end
end

function start_incantation(tcp)
	local res = false
	while (res == false) do
		execute_command(tcp, "incantation")
	end
	return CURRENT_RES
end

function food_in_my_vision(tcp)
	execute_command(tcp, "voir")
	local tab = parse_case(CURRENT_RES)
	local case = get_case_on(tab, "nourriture")

	if (case ~= false) then
		return OK
	else
		return KO
	end
end

function food_on_my_case(tcp)
	execute_command(tcp, "voir")
	local tab = parse_case(CURRENT_RES)
	local case = get_case_on(tab, "nourriture")

	if (case == 1) then
		return OK
	else
		return KO
	end
end

function take_food(tcp)
	execute_command(tcp, "prend", "nourriture")
	return CURRENT_RES
end

function moove_to_food(tcp)
	execute_command(tcp, "voir")
	local tab = parse_case(CURRENT_RES)
	local moove = {
		["gauche"] = "gauche avance droite",
		["avance"] = "avance",
		["droite"] = "droite avance gauche",
	}
	local case = get_case_on(tab, "nourriture")
	if (case ~= false) then
		local where = determine_way_to(case)
		if (where ~= nil) then
			return execute_movements(tcp, moove[where])
		else
			return KO
		end
	end
	return KO
end

function enought_stones(tcp)
	execute_command(tcp, "inventaire")
	update_ressource(UPDATE_INVENTORY)
	local tab = get_tab_level()

	for k, v in pairs(tab[LEVEL]) do
		if (k ~= "joueur" and ITEM[k] < v) then
			return KO
		end
	end
	return OK
end

function stone_needed_in_vision(tcp)
	execute_command(tcp, "voir")
	local level = get_tab_level()
	local tab = parse_case(CURRENT_RES)

	for k, v in pairs(tab) do
		for l, w in pairs(v) do
			if (w ~= "X") then
				if (w ~= "joueur" and level[LEVEL][w] > ITEM[w]) then
					NEEDED_STONE = w
					return OK
				end
			end
		end
	end
	return KO
end

function call_help(tcp)
	execute_command(tcp, "broadcast", "HELP " .. LEVEL)
	return CURRENT_RES
end

function stone_on_my_case(tcp)
	execute_command(tcp, "voir")
	local tab = parse_case(CURRENT_RES)
	local case = get_case_on(tab, NEEDED_STONE)

	if (case == 1) then
		return OK
	else
		return KO
	end
end

function moove_to_stone(tcp)
	execute_command(tcp, "voir")
	local tab = parse_case(CURRENT_RES)
	local moove = {
		["gauche"] = "gauche avance droite",
		["avance"] = "avance",
		["droite"] = "droite avance gauche"
	}
	local case = get_case_on(tab, NEEDED_STONE)
	if (case ~= false) then
		local where = determine_way_to(case)
		if (where ~= nil) then
			return execute_movements(tcp, moove[where])
		else
			return KO
		end
	end
	return KO
end

function take_stone(tcp)
	execute_command(tcp, "prend", NEEDED_STONE)
	NEEDED_STONE = nil
	return CURRENT_RES
end

function same_level(tcp)
	if (BROADCAST[1] ~= nil) then
		local tab = parse_word(BROADCAST[1])
		if (tab[1] ~= nil and tab[1] == "HELP" and tab[2] ~= nil and tab[2] == LEVEL) then
			return OK
		else
			return KO
		end
	end
	return KO
end

function ask_fork(tcp)
	execute_command(tcp, "fork")
	WAITING_FORK = true
	return CURRENT_RES
end

function slot_opened(tcp)
	execute_command(tcp, "connect_nbr")
	if (tonumber(CURRENT_RES) > 0 and WAITING_FORK == true) then
		WAITING_FORK = false
		return OK
	else
		return KO
	end
end

function waiting_fork(tcp)
	if (WAITING_FORK == true) then
		return OK
	else
		return KO
	end
end