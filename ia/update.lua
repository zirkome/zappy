function update_ressource(tab)
	for i = 1, #tab do
		for k, v in pairs(ITEM) do
			if (tab[i][1] == v["name"]) then
				ITEM[k]["qte"] = tonumber(tab[i][2])
			end
		end
	end
end
