function update_ressource(tab)
	for i = 1, #tab do
		ITEM[tab[i][1]] = tonumber(tab[i][2])
	end
end
