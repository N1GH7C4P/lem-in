require "graphics"
require "parser"
require "utils"
require "geometry"

function Polygonize_coordinates()
	local i = 0
	while ANTFARM.rooms[i] do
		ANTFARM.rooms[i].x = POLYGON[i].x
		ANTFARM.rooms[i].y = POLYGON[i].y
		i = i + 1
	end
end
function love.load()

	ANT_SCALING = 0.3
	ROOM_RADIUS = 30
	X_SCALING = 30
	Y_SCALING = 60
	CURRENT_ROUND = -1
	CLICK_MODE = 1
	DTOTAL = 0
	UPDTATE_DELAY = 2
	COUNT = 0
	POLYGON_COORDINATES = 1

	ANTFARM = {}
	ANTFARM.rooms = {}
	ANTFARM.tubes = {}
	ANTFARM.rounds_of_moves = {}
	ANTFARM.nb_of_rooms = 0
	ANTFARM.nb_of_tubes = 0
	ANTFARM.nb_rounds_of_moves = 0

	love.graphics.setBackgroundColor(0.3,0.3,0.5)
	ANT_IMG = love.graphics.newImage("img/ant.png")
	local lines = love.filesystem.lines("visualize_me.output")
	Parse_lines(lines)
	POLYGON = RegularPoly(400, 300, ANTFARM.nb_of_rooms, 250)
	Polygonize_coordinates()
end

function love.draw()
	Draw_tubes()
	Draw_rooms()
	Print_polygon(POLYGON)
	if CURRENT_ROUND > -1 then
		Draw_round_of_moves(ANTFARM.rounds_of_moves[CURRENT_ROUND], COUNT)
	end
end

function love.update(dt)

	COUNT = COUNT + dt
	DTOTAL = DTOTAL + dt

	if (CLICK_MODE == 1) then
		function love.mousepressed(x, y, button, istouch)
			if button == 1 then
				if (CURRENT_ROUND < ANTFARM.nb_rounds_of_moves - 1) then
					CURRENT_ROUND = CURRENT_ROUND + 1
					COUNT = 0
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
		Draw_ant(ANTFARM.start_room.x, ANTFARM.start_room.y)
	end
end