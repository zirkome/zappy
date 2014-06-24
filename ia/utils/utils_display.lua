function print_bkt(title, inner)
	if (inner ~= nil) then print(title .. "[" .. inner .. "]") 
	else print("Error : print_bkt : inner is nil") end
end

function display_2dtab(tab)
	for k, v in pairs(tab) do
		for w, x in pairs(tab[k]) do
			print(k, "[" .. x .. "]")
		end
	end
end

function display_tab(tab)
	for k, v in pairs(tab) do
		print(k, v)
	end
end

function display_item()
	for k, v in pairs(ITEM) do
		print_bkt(v["name"], v["qte"])
	end
end
