local posix = require "posix"

function fork_p()
	local pid = posix.fork()
	if (pid == 0) then
		init_global(true)
		main_prg()
	end
	return OK
end

function get_pid()
	return posix.getpid('pid')
end