
function Draw_ant(x, y)
	love.graphics.draw(ANT_IMG, x, y, 0, ANT_SCALING, ANT_SCALING)
end
function Animate_ant(x1, y1, x2, y2, dt)
	--print("x1: ",x1,"y1: ",y1, "x2: ",x2, "y2: ",y2,"dt: ",dt)
	local dx = x2 - x1
	local dy = y2 - y1
	local current_x = x2 - (dx * dt)
	local current_y = y2 - (dy * dt)
	if dt > 1 then
		current_x = x1
		current_y = y1
	end
	--print("dt", dt)
	--print("current_x: ", current_x, "current_y: ", current_y)
	--print("round: ", CURRENT_ROUND)
	Draw_ant(current_x, current_y)
end

function Draw_rooms()
	local i = 0
	while i < ANTFARM.nb_of_rooms do
		love.graphics.setColor(0,0.3,0,1)
		love.graphics.circle("fill", ANTFARM.rooms[i].x, ANTFARM.rooms[i].y, ROOM_RADIUS)
		love.graphics.setColor(1,1,1,1)
		love.graphics.circle("line", ANTFARM.rooms[i].x, ANTFARM.rooms[i].y, ROOM_RADIUS)
		love.graphics.print(ANTFARM.rooms[i].name, ANTFARM.rooms[i].x, ANTFARM.rooms[i].y)
		i = i + 1
	end
end

function Draw_tubes()
	local i = 0
	while i < ANTFARM.nb_of_tubes - 1 do
		love.graphics.line(ANTFARM.tubes[i].tube_start.x, ANTFARM.tubes[i].tube_start.y, ANTFARM.tubes[i].tube_end.x, ANTFARM.tubes[i].tube_end.y)
		i = i + 1
	end
end

function Draw_round_of_moves(round_of_moves, dt)
	local i = 0
	while round_of_moves[i] do
		local x1, y1, x2, y2 = Get_ant_path(round_of_moves[i].ant_id)
		if (x1 and y1 and x2 and y2) then
			Animate_ant(x1, y1, x2, y2, dt)
		else
			print("no coords for ant: ", round_of_moves[i].ant_id, " round: ", CURRENT_ROUND)
		end
		--draw_ant(round_of_moves[i].room.x, round_of_moves[i].room.y)
		--love.graphics.print(round_of_moves[i].ant_id, round_of_moves[i].room.x + 50, round_of_moves[i].room.y)
		i = i + 1
	end
end