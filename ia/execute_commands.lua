function execute_cmd(tcp, str, arg)
	local tab = {
		["avance"] = avance,
		["droite"] = droite,
		["gauche"] = gauche,
		["voir"] = voir,
		["inventaire"] = inventaire,
		["prend"] = prend_objet,
		["expulse"] = expulse,
		["broadcast"] = broadcast_text,
		["incantation"] = incantation,
		["fork"] = fork,
		["connect_nbr"] = connect_nbr
	}
	if (tab[str] == nil) then
		print("command is nil.")
	else 
		return tab[str](tcp, arg)
	end
end

function avance(tcp)
	X, Y = calc_new_position()
	send_command(tcp, "avance")
	return recept_command(tcp)
end

function droite(tcp)
	ORIENTATION = calc_orientation("droite")
	X, Y = calc_new_position()
	send_command(tcp, "droite")
	return recept_command(tcp)
end

function gauche(tcp)
	ORIENTATION = calc_orientation("gauche")
	X, Y = calc_new_position()
	send_command(tcp, "gauche")
	return recept_command(tcp)
end

function voir(tcp)
	send_command(tcp, "voir")
	return recept_command(tcp)
end

function inventaire(tcp)
	send_command(tcp, "inventaire")
	return recept_command(tcp)
end

function prend_objet(tcp, objet)
	send_command(tcp, "prend " .. objet)
	return recept_command(tcp)
end

function expulse(tcp)
	send_command(tcp, "expulse")
	return recept_command(tcp)
end

function broadcast_text(tcp, text)
	send_command(tcp, "broadcast " .. text)
	return recept_command(tcp)
end

function incantation(tcp)
	send_command(tcp, "incantation")
	return recept_command(tcp)
end

function fork(tcp)
	send_command(tcp, "fork")
	return recept_command(tcp)
end

function connect_nbr(tcp)
	send_command(tcp, "connect_nbr")
	return recept_command(tcp)
end