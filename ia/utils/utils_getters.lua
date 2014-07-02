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

function get_tab_walk()
	local tab = {
		[1] = {2, 7},
		[2] = {19, 12},
		[3] = {4, 1},
		[4] = {20, 2},
		[5] = {6, 14},
		[6] = {1, 6},
		[7] = {8, 9},
		[8] = {10, 11},
		[9] = {7, 9},
		[10] = {1, 10},
		[11] = {7, 11},
		[12] = {23, 13},
		[13] = {16, 15},
		[14] = {5, 14},
		[15] = {13, 15},
		[16] = {18, 17},
		[17] = {16, 17},
		[18] = {12, 18},
		[19] = {20, 12},
		[20] = {3, 12},
		[21] = {22, 5},
		[22] = {21, 22},
		[23] = {24, 21},
		[24] = {3, 21},
		[42] = {1}
	}
	return tab
end

function get_tab_func()
	local tab = {
		[1] = enought_food,
		[2] = team_message,
		[3] = determine_way_broadcast,
		[4] = reach_destination,
		[5] = enought_trantorian,
		[6] = start_incantation,
		[7] = food_in_my_vision,
		[8] = food_on_my_case,
		[9] = random_moove,
		[10] = take_food,
		[11] = moove_to_food,
		[12] = enought_stones,
		[13] = stone_needed_in_vision,
		[14] = call_help,
		[15] = random_moove,
		[16] = stone_on_my_case,
		[17] = moove_to_stone,
		[18] = take_stone,
		[19] = same_level,
		[20] = enought_stones,
		[21] = need_to_fork,
		[22] = fork_p,
		[23] = team_message,
		[24] = same_level
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
			end
		end
	end
	return false
end
