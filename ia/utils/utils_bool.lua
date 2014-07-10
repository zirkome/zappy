function is_match_tab(tab, elem)
	for k, v in pairs(tab) do
		if (v == elem) then 
			return true
		end
	end
	return false
end
