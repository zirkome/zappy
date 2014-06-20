function get_word(str)
	local tab = {}
	for w in str:gmatch("%w+") do
		table.insert(tab, w)
	end
	return tab
end

function parse_case(str)
	local tab = {{}}
	if (str) then
		local i = 1
		for w in str:gmatch("%w+.") do
			if (w:find(",") or w:find("}")) then
				for x in w:gmatch("%w+") do
					table.insert(tab[i], x)
				end
				i = i + 1;
				table.insert(tab, {})
			else
				table.insert(tab[i], w)
			end
		end
	end
	return tab
end
