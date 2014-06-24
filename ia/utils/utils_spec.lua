require("math")

function modulo(a, b)
	return a - math.floor(a / b) * b
end

function sleep(second)
	local clock = os.clock
	local t0 = clock()
	while clock() - t0 <= second do end
end