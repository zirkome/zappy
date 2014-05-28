function view(str)
	local tab = {{}}
	if (str) then
		local i = 1
		for w in str:gmatch("%w+.") do
			if (w:find(",") or w:find("}")) then
				for x in w:gmatch("%a+") do
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
