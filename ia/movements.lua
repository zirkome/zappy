function calc_new_position()
	local tab = {1, 1, -1, -1}
	if (ORIENTATION == 1 or ORIENTATION == 3) then
		Y = Y + tab[ORIENTATION]
	else
		X = X + tab[ORIENTATION]
	end
	if (X == 0) then X = MAP_XMAX end
	if (Y == 0) then Y = MAP_YMAX end
	if (X == MAP_XMAX + 1) 	then x = 1 end
	if (Y == MAP_YMAX + 1) 	then y = 1 end
	return modulo(X, MAP_XMAX + 1), modulo(Y, MAP_YMAX + 1)
end

function calc_orientation(where)
	local what_orientation = {
		{["gauche"] = DIR["west"], ["droite"] = DIR["east"]},		-- NORTH
		{["gauche"] = DIR["north"], ["droite"] = DIR["south"]},		-- EAST
		{["gauche"] = DIR["east"], ["droite"] = DIR["west"]},		-- SOUTH
		{["gauche"] = DIR["south"], ["droite"] = DIR["north"]}		-- WEST
	}
	return what_orientation[ORIENTATION][where]
end

function avance()
	X, Y = calc_new_position()
end

function droite()
	ORIENTATION = calc_orientation("droite")
	X, Y = calc_new_position()
end

function gauche()
	ORIENTATION = calc_orientation("gauche")
	X, Y = calc_new_position()
end
