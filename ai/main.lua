dofile("utils.lua")
dofile("utils_math.lua")
dofile("global.lua")
dofile("view.lua")
dofile("movements.lua")

function execute_ia(x, y, level, orientation)
	X = x
	Y = y
	LEVEL = level
	ORIENTATION = orientation

	local tab = view("{coco,,, phalis,,,, joueur deraumere, joueur joueur phalis, genial aussi,,,,,lol}")
	display_2dtab(tab)
end

execute_ia(1, 1, 1, 1)
return (0) -- success