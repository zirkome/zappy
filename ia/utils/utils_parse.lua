function parse_word(str)
	local tab = {}
	for w in str:gmatch("%w+") do
		table.insert(tab, w)
	end
	return tab
end

function parse_case(str)
	local number = get_nb_case_of(",", str)
	local tab = {}
	local j = 1
	local k = 1
	local dep = 1
	local coma = false

	for i = 1, number do table.insert(tab, {}) end
	tab[1][1] = ""
	if (str:sub(2, 2) == " ") then dep = 3 end
	for i = dep, #str do
		local c = str:sub(i,i)
		if (c == ",") then
			k = 1
			j = j + 1
			tab[j][k] = ""
			if (str:sub(i + 1, i + 1) == "," or str:sub(i + 1, i + 1) == "}") then
				tab[j][k] = "X"
			elseif (str:sub(i + 1, i + 1) == " ") then
				coma = true
			end
		elseif (c == " " and coma == false) then
			k = k + 1
			tab[j][k] = ""
		else
			if (c ~= "{" and c ~= "}" and c ~= "\n" and c ~= " ") then
				coma = false
				tab[j][k] = tab[j][k] .. c
			end
		end
	end
	return tab
end
