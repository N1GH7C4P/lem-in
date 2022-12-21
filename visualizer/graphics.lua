
function Draw_ant(x, y)
	love.graphics.draw(ANT_IMG, x, y, 0, ANT_SCALING, ANT_SCALING)
end
function Animate_ant(x1, y1, x2, y2)
	--print("x1: ",x1,"y1: ",y1, "x2: ",x2, "y2: ",y2,"dt: ", COUNT)
	if x1 and y1 and x2 and y2 then
		local dx = x2 - x1
		local dy = y2 - y1
		local current_x = x2 - (dx * COUNT)
		local current_y = y2 - (dy * COUNT)
		if COUNT > 1 then
			current_x = x1
			current_y = y1
		end
		--print("dt", dt)
		--print("current_x: ", current_x, "current_y: ", current_y)
		--print("round: ", CURRENT_ROUND)
		Draw_ant(current_x, current_y)
	end
end

local function draw_room(x, y, name, color)
	love.graphics.setColor(color)
	love.graphics.circle("fill", x, y, ROOM_RADIUS)
	love.graphics.setColor(1,1,1,1)
	love.graphics.circle("line", x, y, ROOM_RADIUS)
	love.graphics.print(name, x, y)
	if name == ANTFARM.start_room.name then
		love.graphics.print("START", x, y + 20)
		love.graphics.print(ANTFARM.ants_at_start, x, y + 32)
	elseif name == ANTFARM.end_room.name then
		love.graphics.print("END", x, y + 20)
		love.graphics.print(ANTFARM.ants_at_end, x, y + 32)
	end
end
function Draw_rooms()
	local i = 0
	while i < ANTFARM.nb_of_rooms do
		if USING_ALT_COORDS == 1 then
			draw_room(ANTFARM.rooms[i].alt_x, ANTFARM.rooms[i].alt_y, ANTFARM.rooms[i].name, ANTFARM.rooms[i].color)
		else
			draw_room(ANTFARM.rooms[i].x, ANTFARM.rooms[i].y, ANTFARM.rooms[i].name, ANTFARM.rooms[i].color)
		end
		i = i + 1
	end
end

local function draw_tube(x1, y1, x2, y2, color)
	love.graphics.setColor(color)
	love.graphics.line(x1, y1, x2, y2)
end

function Draw_tubes()
	local i = 0
	while i < ANTFARM.nb_of_tubes - 1 do
		if USING_ALT_COORDS == 1 then
			draw_tube(ANTFARM.tubes[i].tube_start.alt_x, ANTFARM.tubes[i].tube_start.alt_y, ANTFARM.tubes[i].tube_end.alt_x, ANTFARM.tubes[i].tube_end.alt_y, {1, 1, 1, 1})
		else
			draw_tube(ANTFARM.tubes[i].tube_start.x, ANTFARM.tubes[i].tube_start.y, ANTFARM.tubes[i].tube_end.x, ANTFARM.tubes[i].tube_end.y, {1, 1, 1, 1})
		end
		i = i + 1
	end
end

function Draw_start_ants()
	if ANTFARM.ants_at_start > 0 then
		if USING_ALT_COORDS == 1 then
			Draw_ant(ANTFARM.start_room.alt_x, ANTFARM.start_room.alt_y)
		else
			Draw_ant(ANTFARM.start_room.x, ANTFARM.start_room.y)
		end
	end
end
function Draw_moves()
	local i = 0
	while MOVES_TO_DRAW[i] do
		Animate_ant(MOVES_TO_DRAW[i].x1, MOVES_TO_DRAW[i].y1, MOVES_TO_DRAW[i].x2, MOVES_TO_DRAW[i].y2, MOVES_TO_DRAW[i].dt)
		i = i + 1
	end
end
function Update_moves(round_of_moves, update_count)
	local i = 0
	MOVES_TO_DRAW = {}
	while round_of_moves[i] do
		local x1, y1, x2, y2 = Get_ant_path(round_of_moves[i].ant_id, update_count)
		if (x1 and y1 and x2 and y2) then
			--print("updating moves to draw.")
			MOVES_TO_DRAW[i] = {}
			MOVES_TO_DRAW[i].x1 = x1
			MOVES_TO_DRAW[i].x2 = x2
			MOVES_TO_DRAW[i].y1 = y1
			MOVES_TO_DRAW[i].y2 = y2
		else
			print("no coords for ant: ", round_of_moves[i].ant_id, " round: ", CURRENT_ROUND)
		end
		--draw_ant(round_of_moves[i].room.x, round_of_moves[i].room.y)
		--love.graphics.print(round_of_moves[i].ant_id, round_of_moves[i].room.x + 50, round_of_moves[i].room.y)
		i = i + 1
	end
end