-- CHARACTER ATTRIBUTES --

TEAM = ""
LEVEL = 1
NUM_CLT = 0

TIME_T = 100
TIME_SURVEY = 1260 * 1 / TIME_T

-- UTILS ATTRIBUTES --

ITEM = {
	["joueur"] = 0,
	["nourriture"] = 10,
	["linemate"] = 0,
	["deraumere"] = 0,
	["sibur"] = 0,
	["mendiane"] = 0,
	["phiras"] = 0,
	["thystame"] = 0
}

COMMANDS = {{["send"] = "", ["response"] = ""}}
BROADCAST = {}

CURRENT_K = nil
CURRENT_RES = nil
NEEDED_STONE = nil

ERROR = 0
OK = 1
KO = 2
LEVELUP = 3

FUNCTION_STATEMENT = {
	enought_food,				-- 1
	team_message,				-- 2
	determine_way_broadcast,	-- 3
	reach_destination,			-- 4
	enought_trantorian,			-- 5
	start_incantation,			-- 6
	food_in_my_vision,			-- 7
	food_on_my_case,			-- 8
	random_moove,				-- 9
	take_food,					-- 10
	moove_to_food,				-- 11
	enought_stones,				-- 12
	stone_needed_in_vision,		-- 13
	call_help,					-- 14
	random_moove,				-- 15
	stone_on_my_case,			-- 16
	moove_to_stone,				-- 17
	take_stone,					-- 18
	same_level,					-- 19
	enought_stones,				-- 20
	need_to_fork,				-- 21
	fork_p,						-- 22
	team_message,				-- 23
	same_level,					-- 24
}

WALKTROUGHT_STATEMENT = {
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