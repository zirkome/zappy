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

UPDATE_INVENTORY = nil
BROADCAST = {}

CURRENT_K = nil
CURRENT_RES = nil
NEEDED_STONE = nil
REGAIN_FOODS = false
IS_GROWING = false

ERROR = 0
OK = 1
KO = 2
LEVELUP = 3
