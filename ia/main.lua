dofile("global.lua")
dofile("socket.lua")
dofile("utils/utils_display.lua")
dofile("utils/utils_spec.lua")
dofile("utils/utils_parse.lua")
dofile("movements.lua")
dofile("execute_commands.lua")
dofile("analyse_reception.lua")
dofile("update.lua")

function execute_ia(x, y, level, orientation, host, port)
	local tcp = connect_server(host, port)
	display_item()
	close_server(tcp)
	return 0
end

function main_prg()
	local host = arg[1]
	local port = arg[2]
	if (host ~= nil and port ~= nil and is_valid_ipv4(host) == 0) then
		return execute_ia(1, 1, 1, 1, host, port)
	else
		print("Usage: lua5.2 ia.out <host> <port>")
		return 1
	end
end

return main_prg()
