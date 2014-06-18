require("math")

function modulo(a, b)
	return a - math.floor(a / b) * b
end