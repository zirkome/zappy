function is_required_at(case)
	local tab = get_tab_level()

	if (case ~= "X") then
		return ITEM[case] < tab[LEVEL][case]
	end
	return false
end

function need_to_fork()
	local tab = get_tab_level()

	if (tab[LEVEL]["joueur"] > ITEM["joueur"]) then
		return OK
	else
		return KO
	end
end

function remain_players()
	local tab = get_tab_level()

	for k, v in pairs(tab[LEVEL]) do
		if (k ~= "nourriture" and k ~= "joueur") then
			if (tab[LEVEL][k] <= ITEM[k]) then
				return false
			end
		end
	end
	return tab[LEVEL]["joueur"] < ITEM["joueur"]
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
	if (ITEM["nourriture"] < 11 and REGAIN_FOODS == false) then
		REGAIN_FOODS = true
		return KO
	elseif (REGAIN_FOODS == true and ITEM["nourriture"] < 15) then
		if (ITEM["nourriture"] == 20) then
			REGAIN_FOODS = false
		end
		return KO
	else
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
			[1] = av,
			[2] = ga_av,
			[3] = ga_av,
			[4] = ga_av,
			[5] = ga_ga,
			[6] = dr_av,
			[7] = dr_av,
			[8] = dr_av
		}
		if (CURRENT_K ~= 0) then
			local ret = tab[CURRENT_K](tcp)
			CURRENT_K = nil
			return ret
		else
			av(tcp)
			return OK
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
		["gauche"] = ga_av_dr,
		["avance"] = av,
		["droite"] = dr_av_ga,
	}
	local case = get_case_on(tab, "nourriture")
	if (case ~= false) then
		local where = determine_way_to(case)
		if (where ~= nil) then
			return moove[where](tcp)
		else
			return KO
		end
	end
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
		["gauche"] = ga_av_dr,
		["avance"] = av,
		["droite"] = dr_av_ga,
	}
	local case = get_case_on(tab, NEEDED_STONE)
	if (case ~= false) then
		local where = determine_way_to(case)
		if (where ~= nil) then
			return moove[where](tcp)
		else
			return KO
		end
	end
end

function take_stone(tcp)
	execute_command(tcp, "prend", NEEDED_STONE)
	NEEDED_STONE = nil
	return CURRENT_RES
end

function same_level(tcp)
	if (BROADCAST[1] ~= nil) then
		local tab = parse_word(BROADCAST[1])
		if (tab[1] ~= nil and tab[1] == "HELP" and tab[1] ~= nil and tab[1] == LEVEL) then
			return OK
		else
			return KO
		end
	end
end
