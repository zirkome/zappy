function calc_orientation(where)
	local t_orient = {
		{{["x"] = X, ["y"] = Y + 1}, {["x"] = X + 1, ["y"] = Y}, {["x"] = X - 1, ["y"] = Y}},
		{{["x"] = X - 1, ["y"] = Y}, {["x"] = X, ["y"] = Y + 1}, {["x"] = X, ["y"] = Y - 1}},
		{{["x"] = X, ["y"] = Y - 1}, {["x"] = X - 1, ["y"] = Y}, {["x"] = X + 1, ["y"] = 0}},
		{{["x"] = X + 1, ["y"] = Y}, {["x"] = X, ["y"] = Y - 1}, {["x"] = X, ["y"] = Y + 1}},
	}
	return (t_orient[ORIENTATION][where])
end

function avance()
	local tab = calc_orientation(1)
	X, Y = tab["x"], tab["y"]
	print(X .. " " .. Y)
end

function droite()
	local tab = calc_orientation(2)
	X, Y = tab["x"], tab["y"]
	print(X .. " " .. Y)
end

function gauche()
	local tab = calc_orientation(3)
	X, Y = tab["x"], tab["y"]
	print(X .. " " .. Y)
end