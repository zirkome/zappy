local posix = require "posix"

function fork_p()
	return posix.fork()
end

function get_pid()
	return posix.getpid('pid')
end