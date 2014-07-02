local posix = require "posix"

function fork_p()
	if (IS_GROWING == false) then
		posix.fork()
	end
	IS_GROWING = true
	return OK
end

function get_pid()
	return posix.getpid('pid')
end