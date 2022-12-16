local function draw_ant(x, y)
	love.graphics.draw(ANT_IMG, x, y, 0, ANT_SCALING, ANT_SCALING)
end
local function get_room_by_round_and_ant_id(round_nb, ant_id)
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
	return nil
end
local function animate_ant(x1, y1, x2, y2, dt)
	--print("x1: ",x1,"y1: ",y1, "x2: ",x2, "y2: ",y2,"dt: ",dt)
	local dx = x2 - x1
	local dy = y2 - y1
	local current_x = x1 + dx * dt
	local current_y = y1 + dy * dt
	print("current_x: ", current_x, "current_y: ", current_y)
	print("round: ", CURRENT_ROUND)
	draw_ant(current_x, current_y)
end
local function get_ant_path(ant_id)
	local current_room = get_room_by_round_and_ant_id(CURRENT_ROUND, ant_id)
	local previous_room
	if CURRENT_ROUND > 0 then
		previous_room = get_room_by_round_and_ant_id(CURRENT_ROUND - 1, ant_id)
	else
		previous_room = ANTFARM.start_room
	end
	if (previous_room and current_room) then
		local x1 = current_room.x
		local y1 = current_room.y
		local x2 = previous_room.x
		local y2 = previous_room.y
		return x1, y1, x2, y2
	end
	return nil
end

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
	if words[0] and words[1] and words[2] then
		room.name = words[0]
		room.x = words[1] * X_SCALING
		room.y = words[2] * Y_SCALING
		return room
	end
	return nil
end

local function parse_move(word)
	local split_word = split(word, '-')
	local move = {}
	move.ant_id = string.match(split_word[0], "%d+")
	move.room = get_room_by_name(split_word[1])
	return(move)
end

local function parse_moves(line)
	local words = {}
	local moves = {}
	words = split(line, " ");
	local i = 0
	while words[i] do
		moves[i] = parse_move(words[i])
		i = i + 1
	end
	return moves
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
	while i < ANTFARM.nb_of_rooms do
		love.graphics.circle("line", ANTFARM.rooms[i].x, ANTFARM.rooms[i].y, ROOM_RADIUS)
		love.graphics.print(ANTFARM.rooms[i].name, ANTFARM.rooms[i].x, ANTFARM.rooms[i].y)
		i = i + 1
	end
end

local function draw_tubes()
	local i = 0
	while i < ANTFARM.nb_of_tubes - 1 do
		love.graphics.line(ANTFARM.tubes[i].tube_start.x, ANTFARM.tubes[i].tube_start.y, ANTFARM.tubes[i].tube_end.x, ANTFARM.tubes[i].tube_end.y)
		i = i + 1
	end
end

local function draw_round_of_moves(round_of_moves, dt)
	local i = 0
	while round_of_moves[i] do
		local x1, y1, x2, y2 = get_ant_path(round_of_moves[i].ant_id)
		if (x1 and y1 and x2 and y2) then
			animate_ant(x1, y1, x2, y2, dt)
		end
		--draw_ant(round_of_moves[i].room.x, round_of_moves[i].room.y)
		--love.graphics.print(round_of_moves[i].ant_id, round_of_moves[i].room.x + 50, round_of_moves[i].room.y)
		i = i + 1
	end
end
function love.load()

	ANT_SCALING = 0.3
	ROOM_RADIUS = 30
	X_SCALING = 30
	Y_SCALING = 60
	CURRENT_ROUND = 0
	CLICK_MODE = 0
	DTOTAL = 0
	UPDTATE_DELAY = 2
	COUNT = 0

	ANTFARM = {}
	ANTFARM.rooms = {}
	ANTFARM.tubes = {}
	ANTFARM.rounds_of_moves = {}
	ANTFARM.nb_of_rooms = 0
	ANTFARM.nb_of_tubes = 0
	ANTFARM.nb_rounds_of_moves = 0

	ANT_IMG = love.graphics.newImage("img/ant.png")
	local i = 0;
	local next_start, next_end;
	for line in love.filesystem.lines("visualize_me.output") do
		if i == 0 then
			ANTFARM.nb_of_ants = line * 1
		elseif string.find(line, "##start") then
			next_start = 1
		elseif string.find(line, "##end") then
			next_end = 1
		elseif string.find(line, "#" or line.len < 3) then

		elseif string.find(line, "L") then
			ANTFARM.rounds_of_moves[ANTFARM.nb_rounds_of_moves] = parse_moves(line)
			ANTFARM.nb_rounds_of_moves = ANTFARM.nb_rounds_of_moves + 1
		elseif string.find(line, "-") then
			ANTFARM.tubes[ANTFARM.nb_of_tubes] = parse_tubes(line)
			ANTFARM.nb_of_tubes = ANTFARM.nb_of_tubes + 1
		else
			ANTFARM.rooms[ANTFARM.nb_of_rooms] = parse_room(line)
			if ANTFARM.rooms[ANTFARM.nb_of_rooms] then
				if next_start == 1 then
					ANTFARM.start_room = ANTFARM.rooms[ANTFARM.nb_of_rooms]
					next_start = 0
				elseif next_end == 1 then
					ANTFARM.end_room = ANTFARM.rooms[ANTFARM.nb_of_rooms]
					next_end = 0
				end
				ANTFARM.nb_of_rooms = ANTFARM.nb_of_rooms + 1
			end
		end
		i = i + 1
	end
end

function love.draw()
	draw_tubes()
	draw_rooms()
	draw_round_of_moves(ANTFARM.rounds_of_moves[CURRENT_ROUND], COUNT)
end

function love.update(dt)

	COUNT = COUNT + dt
	DTOTAL = DTOTAL + dt

	if (CLICK_MODE == 1) then
		function love.mousepressed(x, y, button, istouch)
			if button == 1 then
				if (CURRENT_ROUND < ANTFARM.nb_rounds_of_moves - 1) then
					CURRENT_ROUND = CURRENT_ROUND + 1
				end
			end
		end
	else
		if COUNT > UPDTATE_DELAY and CURRENT_ROUND < ANTFARM.nb_rounds_of_moves - 1 then
			CURRENT_ROUND = CURRENT_ROUND + 1
			COUNT = 0
		end
	end
	if (CURRENT_ROUND > -1) then
	else
		draw_ant(ANTFARM.start_room.x, ANTFARM.start_room.y)
	end
end