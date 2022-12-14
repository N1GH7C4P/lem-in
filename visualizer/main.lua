
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
	for room in ANTFARM.rooms do
		if room.name == name then
			return room
		end
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

function love.load()
	ANTFARM = {}
	ANTFARM.rooms = {}
	ANTFARM.tubes = {}
	ANTFARM.moves = {}
	ANTFARM.nb_of_rooms = 0
	ANTFARM.nb_of_tubes = 0
	ANTFARM.nb_of_moves = 0

	local i = 0;
	local next_start, next_end;
	for line in love.filesystem.lines("visualize_me.output") do
		if i == 0 then
			ANTFARM.nb_of_ants = line
		elseif string.find(line, "L") then
			ANTFARM.moves[ANTFARM.nb_of_moves] = line
			ANTFARM.nb_of_moves = ANTFARM.nb_of_moves + 1
		elseif string.find(line, "-") then
			ANTFARM.tubes[ANTFARM.nb_of_tubes] = line
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
	print(ANTFARM.rooms[1].x)
end
function love.draw()
	
end

function love.update()

end