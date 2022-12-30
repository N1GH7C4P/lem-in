-- Generates a regular polygon given a circumradius (r)
require("graphics")

function RegularPoly(x, y, n, r)
	local out = {}
	for i = 0, n - 1 do
		local a = (i - 1)/n*math.pi * 2
		out[i] = { x = (math.cos(a) * r) + x, y = (math.sin(a)*r) + y }
		--print(out[i].x, ", ", out[i].y)
	end
	return out
end
function Polygonize_coordinates()
	local i = 0
	while ANTFARM.rooms[i] do
		ANTFARM.rooms[i].alt_x = POLYGON[i].x
		ANTFARM.rooms[i].alt_y = POLYGON[i].y
		i = i + 1
	end
end