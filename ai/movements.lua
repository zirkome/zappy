function calc_new_position()
	local tab = {1, 1, -1, -1}
	if (ORIENTATION == 1 or ORIENTATION == 3) then
		Y = Y + tab[ORIENTATION]
	else
		X = X + tab[ORIENTATION]
	end
	if (X == 0) 			then X = MAP_XMAX end
	if (Y == 0) 			then Y = MAP_YMAX end
	if (X == MAP_XMAX + 1) 	then x = 1 end
	if (Y == MAP_YMAX + 1) 	then y = 1 end
	return modulo(X, MAP_XMAX + 1), modulo(Y, MAP_YMAX + 1)
end

function calc_orientation(where)
	local t_orien = {
		{["gauche"] = WEST, ["droite"] = EAST},		-- NORTH
		{["gauche"] = NORTH, ["droite"] = SOUTH},	-- EAST
		{["gauche"] = EAST, ["droite"] = WEST},		-- SOUTH
		{["gauche"] = SOUTH, ["droite"] = NORTH}	-- WEST
	}
	return t_orien[ORIENTATION][where]
end

function avance()
	X, Y = calc_new_position()
	print("avan : " .. X .. " " .. Y)
end

function droite()
	ORIENTATION = calc_orientation("droite")
	X, Y = calc_new_position()
	print("righ : " .. X .. " " .. Y)
end

function gauche()
	ORIENTATION = calc_orientation("gauche")
	X, Y = calc_new_position()
	print("left : " .. X .. " " .. Y)
end
