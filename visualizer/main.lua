local function split (inputstr, sep)
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
local function get_room_by_name(name)
	local i = 0
	while ANTFARM.rooms[i] do
		if ANTFARM.rooms[i].name == name then
			return ANTFARM.rooms[i]
		end
		i = i + 1
	end
end

local function parse_room(line)
	local room = {}
	local words = split(line, " ");
	room.name = words[0]
	room.x = words[1]
	room.y = words[2]
	return room
end

local function parse_moves(line)
	local words = {}
	words = split(line, " ");
	return words
end

local function parse_tubes(line)
	local tube = {}
	local words = {}
	words = split(line, "-");
	tube.tube_start = get_room_by_name(words[0])
	tube.tube_end = get_room_by_name(words[1])
	return tube
end
local function draw_rooms()
	local i = 0
	while i < ANTFARM.nb_of_rooms - 1 do
		love.graphics.circle("fill", ANTFARM.rooms[i].x * LENGTH_MULTIPLIER, ANTFARM.rooms[i].y * LENGTH_MULTIPLIER, ROOM_RADIUS)
		i = i + 1
	end
end
function love.load()
	ROOM_RADIUS = 10
	LENGTH_MULTIPLIER = 30
	ANTFARM = {}
	ANTFARM.rooms = {}
	ANTFARM.tubes = {}
	ANTFARM.rounds_of_moves = {}
	ANTFARM.nb_of_rooms = 0
	ANTFARM.nb_of_tubes = 0
	ANTFARM.nb_rounds_of_moves = 0

	local i = 0;
	local next_start, next_end;
	for line in love.filesystem.lines("visualize_me.output") do
		if i == 0 then
			ANTFARM.nb_of_ants = line
		elseif string.find(line, "L") then
			ANTFARM.rounds_of_moves[ANTFARM.nb_rounds_of_moves] = parse_moves(line)
			ANTFARM.nb_rounds_of_moves = ANTFARM.nb_rounds_of_moves + 1
		elseif string.find(line, "-") then
			ANTFARM.tubes[ANTFARM.nb_of_tubes] = parse_tubes(line)
			ANTFARM.nb_of_tubes = ANTFARM.nb_of_tubes + 1
		elseif string.find(line, "##start") then
			next_start = 1
		elseif string.find(line, "##end") then
			next_end = 1
		else
			ANTFARM.rooms[ANTFARM.nb_of_rooms] = parse_room(line)
			ANTFARM.nb_of_rooms = ANTFARM.nb_of_rooms + 1
			if next_start == 1 then
				ANTFARM.start_room = line
				next_start = 0
			elseif next_end == 1 then
				ANTFARM.end_room = line
				next_end = 0
			end
		end
		i = i + 1
	end
end
function love.draw()
	draw_rooms()
end

function love.update()

end