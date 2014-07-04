dofile("global.lua")
dofile("socket.lua")
dofile("movements.lua")
dofile("execute_commands.lua")
dofile("analyse_reception.lua")
dofile("update.lua")
dofile("level.lua")
dofile("fork.lua")
dofile("utils/utils_display.lua")
dofile("utils/utils_spec.lua")
dofile("utils/utils_parse.lua")
dofile("utils/utils_getters.lua")
dofile("utils/utils_bool.lua")

function get_beginning(tcp, team)
	recept_command(tcp)
	send_command(tcp, team)
	recept_command(tcp)
	NUM_CLT = tonumber(CURRENT_RES)
	recept_command(tcp)
end

-- THIS FUNCTION IS ONLY HERE FOR DEBUG --
function get_tab_name()
	local tab = {
		[1] = "enought_food",
		[2] = "team_message",
		[3] = "determine_way_broadcast",
		[4] = "reach_destination",
		[5] = "enought_trantorian",
		[6] = "start_incantation",
		[7] = "food_in_my_vision",
		[8] = "food_on_my_case",
		[9] = "random_moove",
		[10] = "take_food",
		[11] = "moove_to_food",
		[12] = "enought_stones",
		[13] = "stone_needed_in_vision",
		[14] = "call_help",
		[15] = "random_moove",
		[16] = "stone_on_my_case",
		[17] = "moove_to_stone",
		[18] = "take_stone",
		[19] = "same_level",
		[20] = "enought_stones",
		[21] = "need_to_fork",
		[22] = "ask_fork",
		[23] = "team_message",
		[24] = "same_level",
		[25] = "stone_on_my_case",
		[26] = "take_stone",
		[27] = "stone_needed_in_vision",
		[28] = "slot_opened",
		[30] = "waiting_fork",
		[29] = "fork_p"
	}
	return tab
end
------------------------------------------

function execute_ia(host, port, team)
	local tcp = connect_server(host, port)

	if (tcp ~= nil) then
		local current_state = 42
		local value = OK
		local walktrought_statement = get_tab_walk()
		local function_statement = get_tab_func()
		local what = get_tab_name()

		get_beginning(tcp, team)
		while (value ~= ERROR) do
			current_state = walktrought_statement[current_state][value]
			print(get_pid(), "STATEMENT FUNCTION : ", current_state, what[current_state])
			value = function_statement[current_state](tcp)
			CURRENT_RES = nil
		end
		close_server(tcp)
		return 0
	end
	return 1
end

function main_prg()
	local host = arg[1]
	local port = arg[2]
	local team = arg[3]
	if (host ~= nil and port ~= nil and
		is_valid_ipv4(host) == 0 and team ~= nil)
	then
		return execute_ia(host, port, team)
	else
		print("Usage: lua5.2 ia.out <host> <port> <team>")
		return 1
	end
end

init_global(false)
return main_prg()
