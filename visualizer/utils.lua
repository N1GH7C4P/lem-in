function Split (inputstr, sep)
	if sep == nil then
			sep = "%s"
	end
	local t={}
	local i = 0
	for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
		t[i] = str
		i = i + 1
	end
	return t
end

local function Get_room_by_round_and_ant_id(round_nb, ant_id)
	local round = ANTFARM.rounds_of_moves[round_nb]
	local i = 0
	if round then
		while round[i] do
			if round[i].ant_id == ant_id then
				return round[i].room
			end
			i = i + 1
		end
	end
	return ANTFARM.start_room
end

function Get_ant_path(ant_id)
	local current_room = Get_room_by_round_and_ant_id(CURRENT_ROUND, ant_id)
	local previous_room
	if CURRENT_ROUND > 0 then
		previous_room = Get_room_by_round_and_ant_id(CURRENT_ROUND - 1, ant_id)
	else
		previous_room = ANTFARM.start_room
	end
	if (previous_room and current_room) then
		local x1 = current_room.x
		local y1 = current_room.y
		local x2 = previous_room.x
		local y2 = previous_room.y
		return x1, y1, x2, y2
	else
		--print("no path for ant id: ", ant_id)
	end
	return nil
end

function Get_room_by_name(name)
	local i = 0
	while ANTFARM.rooms[i] do
		if ANTFARM.rooms[i].name == name then
			return ANTFARM.rooms[i]
		end
		i = i + 1
	end
end