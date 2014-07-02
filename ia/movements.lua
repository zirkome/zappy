function random_moove(tcp)
	local mooves = {"avance", "gauche", "droite"}
	local rand = math.random(1, 3)
	execute_command(tcp, mooves[rand])
	return OK
end

function determine_way_to(nb)
	local tab_avance = {1, 3, 7, 13, 21, 31, 43, 57, 73}
	local tab_gauche = {2, 5, 6, 10, 11, 12, 17, 18, 19, 20, 26, 27, 28, 29, 30, 37, 38, 39, 40,
						41, 42, 50, 51, 52, 53, 54, 55, 56, 65, 66, 67, 68, 69, 70, 71, 72}
	local tab_droite = {4, 8, 9, 14, 15, 16, 22, 23, 24, 25, 32, 33, 34, 35, 36, 44, 45, 46, 47,
						48, 49, 58, 59, 60, 61, 62, 63, 64, 74, 75, 76, 77, 78, 79, 80, 81}

	if (is_match_tab(tab_avance, nb) == true) then return "avance" end
	if (is_match_tab(tab_gauche, nb) == true) then return "gauche" end
	if (is_match_tab(tab_droite, nb) == true) then return "droite" end
	return nil
end

function execute_movements(tcp, str)
	local tab = parse_word(str)

	for k, v in pairs(tab) do
		moove_at(tcp, v)
	end
	return CURRENT_RES
end

function moove_at(tcp, where)
	CURRENT_RES = KO
	while (CURRENT_RES == KO) do
		execute_command(tcp, where)
	end
	return CURRENT_RES
end