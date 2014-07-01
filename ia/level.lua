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