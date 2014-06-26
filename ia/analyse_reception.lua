function special_case(str)
	return str
end

function analyse_command(str)
	-- message K: msg (k = case nb), ok, ko, elevation en cours, niveau actuel : K, mort, {, deplacement : K

	local cut = get_word(str)
	local tab = {
		["message"] = get_message,
		["ok"] = all_right,
		["ko"] = all_bad,
		["elevation"] = growing,
		["niveau"] = get_level,
		["mort"] = exit_program,
		["deplacement"] = get_expulse,
	}
	if (tab[cut[1]] == nil) then return special_case(str)
	else
		return tab[cut[1]](cut)
	end
end

function get_message(cut)
	print("received broadcast from", cut[2], "msg: " .. cut[3])
end

function all_right(cut)
	return true
end

function all_bad(cut)
	return -42
end

function growing(cut)
	print("is growing !")
end

function get_level(cut)
	print("my level is : ", cut[4])
end

function exit_program(cut)
	print("i'm dead !")
	return -42
end

function get_expulse(cut)
	print("expulse at : ", cut[3])
end
