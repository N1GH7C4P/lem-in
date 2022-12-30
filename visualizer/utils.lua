Color = require("color")
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

function Give_rooms_color()
	local i = 0
	local j
	while ANTFARM.rooms[i] do
		if ANTFARM.rooms[i] == ANTFARM.end_room then
			--print("end room: ", ANTFARM.rooms[i].name)
			ANTFARM.rooms[i].color = END_ROOM_COLOR
		else
			j = 0
			--print("room_name: ", ANTFARM.rooms[i].name, "path_id: ", ANTFARM.rooms[i].path_id)
			for k, v in pairs(Color) do
				if j == tonumber(ANTFARM.rooms[i].path_id) then
					ANTFARM.rooms[i].color = v
					--print("color: ", k)
				end
				j = j + 1
			end
		end
		i = i + 1
	end
end

function Give_tubes_color()
	local i = 0
	while ANTFARM.tubes[i] do
		local t = ANTFARM.tubes[i]
		if t.tube_end.color then
			--print("tube end color: ",t.tube_end.color)
			if t.tube_start.color == t.tube_end.color or ANTFARM.start_room == ANTFARM.tubes[i].tube_start or ANTFARM.end_room == t.tube_start then
				t.color = t.tube_end.color
			end
		end
		if t.tube_start.color then
			if t.tube_end.color == t.tube_start.color or ANTFARM.end_room == t.tube_end then
				t.color = t.tube_start.color
			end
		end
		i = i + 1
	end
end

function Mark_paths()
	local i;
	local j;

	i = 0
	while i < ANTFARM.nb_rounds_of_moves do
		j = 0
		while ANTFARM.rounds_of_moves[i][j] do
			if not ANTFARM.rounds_of_moves[i][j].room.path_id then
				--print("room: ", ANTFARM.rounds_of_moves[i][j].room.name, "id: ", ANTFARM.rounds_of_moves[i][j].ant_id)
				ANTFARM.rounds_of_moves[i][j].room.path_id = ANTFARM.rounds_of_moves[i][j].ant_id
			end
			j = j + 1
		end
		i = i + 1
	end
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

local function update_ant_counts(current_room, previous_room)
	if current_room == ANTFARM.end_room then
			ANTFARM.ants_at_end = ANTFARM.ants_at_end + 1
		end
		if previous_room == ANTFARM.start_room then
			ANTFARM.ants_at_start = ANTFARM.ants_at_start - 1
		end
end
function Get_ant_path(ant_id, update_count)
	local current_room = Get_room_by_round_and_ant_id(CURRENT_ROUND, ant_id)
	local previous_room
	if CURRENT_ROUND > 0 then
		previous_room = Get_room_by_round_and_ant_id(CURRENT_ROUND - 1, ant_id)
	else
		previous_room = ANTFARM.start_room
	end
	if (previous_room and current_room) then
		if update_count == 1 then
			update_ant_counts(current_room, previous_room)
		end
		local x1, y1, x2, y2
		if USING_ALT_COORDS == 1 then
			x1 = current_room.alt_x
			y1 = current_room.alt_y
			x2 = previous_room.alt_x
			y2 = previous_room.alt_y
		else
			x1 = current_room.x
			y1 = current_room.y
			x2 = previous_room.x
			y2 = previous_room.y
		end
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