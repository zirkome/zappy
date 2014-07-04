function random_moove(tcp)
	local mooves = {"avance", "gauche avance", "droite avance"}
	local rand = math.random(1, 3)
	execute_movements(tcp, mooves[rand])
	return OK
end

function determine_way_to(nb)
	local old = 0
	local rank_y = 0
	while (nb > old + 2 * (rank_y + 1)) do
		old = 1 + 2 * (rank_y + 1)
		rank_y = rank_y + 1
	end
	local rank_x = nb - old
	if (rank_x == 0) then
		return "avance"
	elseif (rank_x > 0) then
		return "droite"
	else
		return "gauche"
	end
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