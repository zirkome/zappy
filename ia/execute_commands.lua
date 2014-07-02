function execute_command(tcp, str, arg)
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
	send_command(tcp, "avance")
	recept_command(tcp)
end

function droite(tcp)
	send_command(tcp, "droite")
	recept_command(tcp)
end

function gauche(tcp)
	send_command(tcp, "gauche")
	recept_command(tcp)
end

function voir(tcp)
	send_command(tcp, "voir")
	recept_command(tcp)
end

function inventaire(tcp)
	send_command(tcp, "inventaire")
	recept_command(tcp)
	UPDATE_INVENTORY = parse_case(CURRENT_RES)
end

function prend_objet(tcp, objet)
	send_command(tcp, "prend " .. objet)
	recept_command(tcp)
end

function expulse(tcp)
	send_command(tcp, "expulse")
	recept_command(tcp)
end

function broadcast_text(tcp, text)
	send_command(tcp, "broadcast " .. text)
	recept_command(tcp)
end

function incantation(tcp)
	send_command(tcp, "incantation")
	recept_command(tcp)
end

function fork(tcp)
	send_command(tcp, "fork")
	recept_command(tcp)
end

function connect_nbr(tcp)
	send_command(tcp, "connect_nbr")
	recept_command(tcp)
end