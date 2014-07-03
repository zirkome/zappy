local posix = require "posix"

function fork_p(tcp)
	execute_command(tcp, "fork")
	if (CURRENT_RES == OK) then
		local pid = posix.fork()
		if (pid == 0) then
			init_global(true)
			main_prg()
		end
		return OK
	end
	return KO
end

function get_pid()
	return posix.getpid('pid')
end