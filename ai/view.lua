function view(str)
	if (str) then
		local i = 1
		local tab = {}
		for d in str:gmatch("[^,]([^{,]*[,}])") do
			if (d ~= ",") then
				tab[i] = d
				i = i +1
			end
		end
		local k = 1
		local tab2 = {}
		for i = 1, #tab do
			for j in tab[i]:gmatch(".+[^}]") do
				for x in j:gmatch("[^ ]*") do
					if (x ~= "") then
						tab2[k] = x
						k = k + 1
					end
				end
			end
		end
		d_tab = {{}}
		local d1 = 1
		local d2 = 1
		for i=1, #tab2 do
			if (tab2[i]:find(",")) then
				print(tab2[i])
				d_tab[d1][d2] = tab2[i]
				d2 = 1
				d1 = d1 + 1
			else
				d_tab[d1][d2] = tab2[i]
				d2 = d2 + 1
			end
		end
		for i=1, #d_tab do
			for j=1, #d_tab[i] do
				print(d_tab[i][j])
			end
		end
	end
end
