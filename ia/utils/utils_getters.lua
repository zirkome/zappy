function get_tab_level()
	local tab = {
		{["joueur"] = 1, ["nourriture"] = 0, ["linemate"] = 1, ["deraumere"] = 0, ["sibur"] = 0, ["mendiane"] = 0, ["phiras"] = 0, ["thystame"] = 0},
		{["joueur"] = 2, ["nourriture"] = 0, ["linemate"] = 1, ["deraumere"] = 1, ["sibur"] = 1, ["mendiane"] = 0, ["phiras"] = 0, ["thystame"] = 0},
		{["joueur"] = 2, ["nourriture"] = 0, ["linemate"] = 2, ["deraumere"] = 0, ["sibur"] = 1, ["mendiane"] = 0, ["phiras"] = 2, ["thystame"] = 0},
		{["joueur"] = 4, ["nourriture"] = 0, ["linemate"] = 1, ["deraumere"] = 1, ["sibur"] = 2, ["mendiane"] = 0, ["phiras"] = 1, ["thystame"] = 0},
		{["joueur"] = 4, ["nourriture"] = 0, ["linemate"] = 1, ["deraumere"] = 2, ["sibur"] = 1, ["mendiane"] = 3, ["phiras"] = 0, ["thystame"] = 0},
		{["joueur"] = 6, ["nourriture"] = 0, ["linemate"] = 1, ["deraumere"] = 2, ["sibur"] = 3, ["mendiane"] = 0, ["phiras"] = 1, ["thystame"] = 0},
		{["joueur"] = 6, ["nourriture"] = 0, ["linemate"] = 2, ["deraumere"] = 2, ["sibur"] = 2, ["mendiane"] = 2, ["phiras"] = 2, ["thystame"] = 1}
	}
	return tab
end

function get_nb_case_of(what, str)
	local case = 1

	for c in str:gmatch(".") do
		if (c == what) then case = case + 1 end
	end
	return case
end

function get_case_on(case, item)
	for i = 1, #case do
		for j = 1, #case[i] do
			if (case[i][j] == item) then
				return i
			else
				return false
			end
		end
	end
end
