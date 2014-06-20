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
	local s, status, partial = tcp:receive()

	if (s ~= nil) then
		print_bkt("Received : ", s)
		return s
	end
	print_bkt("Error in recept_command : ", status)
	return nil
end

function send_command(tcp, command)
	print_bkt("send : ", command)
	local s = tcp:send(command .. "\n")

	if (s ~= #command + 1) then
		print_bkt("Error in send_command : ", s .. " bytes send instead of " .. #command + 1)
		return -1
	end
	return 0
end

function connect_server(host, port)
	local socket = require("socket")
	local tcp = assert(socket.tcp())
	local success, err = tcp:connect(host, port)

	if (success == nil) then
		print("Error in connect_server : " .. err)
		return nil
	end
	return tcp
end

function close_server(tcp)
	tcp:close()
end