function is_required_at(case)
	local tab = get_tab_level()

	if (case ~= "X") then
		return ITEM[case] < tab[LEVEL][case]
	end
	return false
end

function need_to_fork()
	local tab = get_tab_level()

	return tab[LEVEL]["joueur"] > ITEM["joueur"]
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

function enought_food()
	if (ITEM["nourriture"] < 10) then
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
			[2] = ga_av,
			[3] = ga_av,
			[4] = ga_av,
			[5] = ga_ga,
			[6] = dr_av,
			[7] = dr_av,
			[8] = dr_av
		}
		if (CURRENT_K ~= 0) then
			return tab[CURRENT_K](tcp)
		else
			KO
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
	execute_command(tcp, "incantation")
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
	local case = get_case_on(tab, "nourriture")
	local moove = {
		["gauche"] = ga_av_dr,
		["avance"] = avance,
		["droite"] = dr_av_ga,
	}
	local where = determine_way_to(case)
	if (case ~= false and where ~= nil) then
		return moove[where]
	else
		KO
	end
end

function enought_stones()
	local tab = get_tab_level()

	for k, v in pairs(tab[LEVEL]) do
		if (k ~= "joueur" and ITEM[k] ~= v) then
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
		if (v ~= "joueur" and level[LEVEL][v] > ITEM[v]) then
			NEEDED_STONE = v
			return OK
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
	local case = get_case_on(tab, NEEDED_STONE)
	local moove = {
		["gauche"] = ga_av_dr,
		["avance"] = avance,
		["droite"] = dr_av_ga,
	}
	local where = determine_way_to(case)
	if (case ~= false and where ~= nil) then
		return moove[where]
	else
		KO
	end
end

function take_stone(tcp)
	execute_command(tcp, "prend", NEEDED_STONE)
	return CURRENT_RES
end

function same_level(tcp)
	if (BROADCAST[1] ~= nil) then
		local tab = get_word(BROADCAST[1])
		if (tab[3] ~= nil and tab[3] == "HELP" and tab[4] ~= nil and tab[4] == LEVEL) then
			return OK
		else
			return KO
		end
	end
end
