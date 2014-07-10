function print_bkt(pid, title, inner)
	if (inner ~= nil) then print(pid, title .. "[" .. inner .. "]") 
	else print(pid, "Error : print_bkt : inner is nil") end
end

function display_2dtab(tab)
	for k = 1, #tab do
		for w = 1, #tab[k] do
			print(k, "[" .. tab[k][w] .. "]")
		end
	end
end

function display_tab(tab)
	for k = 1, #tab do
		print(k, "[" .. tab[k] .. "]")
	end
end
