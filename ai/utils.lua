function display_2dtab(tab)
	for k, v in pairs(tab) do
		for w, x in pairs(tab[k]) do
			print(k, x)
		end
	end
end