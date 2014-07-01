function update_ressource(tab)
	for i = 1, #tab do
		ITEM[tab[i][1]] = tonumber(tab[i][2])
	end
end

function update_ressource_if(tab_case)
	for i = 1, #tab_case do
		for j = 1, #tab_case[i] do
			if (is_required_at(tab_case[i][j]) == true) then
				return tab_case[i][j], i
			end
		end
	end
	return false
end
