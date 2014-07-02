function analyse_command(str)
	if (str ~= nil) then
		local cut = parse_word(str)
		local tab = {
			["message"] = get_message,
			["ok"] = all_right,
			["ko"] = all_bad,
			["elevation"] = growing,
			["niveau"] = get_level,
			["mort"] = exit_program,
			["deplacement"] = get_expulse,
		}
		if (tab[cut[1]] == nil) then
			CURRENT_RES = str
		else
			CURRENT_RES = tab[cut[1]](cut)
		end
	else
		CURRENT_RES = KO
	end
end

function get_message(cut)
	print("received broadcast from", cut[2], "msg: " .. cut[3])
	CURRENT_K = cut[2]
	BROADCAST:insert(cut[3])
	CURRENT_RES = cut[4]
end

function all_right(cut)
	return OK
end

function all_bad(cut)
	return KO
end

function growing(cut)
	IS_GROWING = true
	return KO
end

function get_level(cut)
	IS_GROWING = false
	return OK
end

function exit_program(cut)
	print("i'm dead ! FUCK !")
	os.exit(1)
end

function get_expulse(cut)
	print("expulse at : ", cut[3])
	return CURRENT_RES
end
