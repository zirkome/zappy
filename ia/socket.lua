function is_valid_ipv4(ip)
	local chunks = {ip:match("(%d+)%.(%d+)%.(%d+)%.(%d+)")}

	if (#chunks == 4) then
		for l, v in pairs(chunks) do
			if (tonumber(v) < 0 or tonumber(v) > 255) then return -1 end
		end
	else
		local chunks = {ip:match("%w+")}
		if (#chunks == 1) then return 0 end
		return -1
	end
	return 0
end

function recept_command(tcp)
	tcp:settimeout(0)
	local s, status, partial = tcp:receive()

	while (status == "timeout") do
		s, status, partial = tcp:receive()
		CURRENT_RES = nil
	end
	print_bkt(get_pid(), "Received : ", s)
	analyse_command(s)
end

function send_command(tcp, command)
	print_bkt(get_pid(), "send : ", command)
	local s = tcp:send(command .. "\n")

	if (s ~= #command + 1) then
		print_bkt(get_pid(), "Error in send_command : ", s ," bytes send instead of " .. #command + 1)
		return -1
	end
	return 0
end

function connect_server(host, port)
	local socket = require("socket")
	local tcp = assert(socket.tcp())

	if (tcp ~= nil) then
		local success, err = tcp:connect(host, port)

		if (success == nil) then
			print(get_pid(), "Error in connect_server : Can't connect to server")
			return nil
		end
		return tcp
	end
	print(get_pid(), "Error in connect_server : Can't connect to server")
	return nil
end

function close_server(tcp)
	tcp:close()
end