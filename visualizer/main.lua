require "graphics"
require "parser"
require "utils"
require "geometry"

function Polygonize_coordinates()
	local i = 0
	while ANTFARM.rooms[i] do
		ANTFARM.rooms[i].alt_x = POLYGON[i].x
		ANTFARM.rooms[i].alt_y = POLYGON[i].y
		i = i + 1
	end
end

local function init_visualizer()
	--love.mouse.setRelativeMode(true)
	love.window.setFullscreen(true)
	love.mouse.setVisible(true)
	WINDOW = {translate={x=0, y=0}, zoom=1}
	DSCALE = 2^(1/6) -- six times wheel movement changes the zoom twice; exponential zoom only
	ANT_SCALING = 0.2
	MSG_OFFSET = 20
	ROOM_RADIUS = 10
	X_SCALING = 30
	Y_SCALING = 60
	CURRENT_ROUND = -1
	DTOTAL = 0
	UPDTATE_DELAY = 2
	COUNT = 0
	POLYGON_COORDINATES = 1
	USING_ALT_COORDS = 0
	IS_FULLSCREEN = true
	DEFAULT_ROOM_COLOR = {0.8, 0.8, 0.8, 0.2}
	DEFAULT_TUBE_COLOR = {1, 1, 1, 1}
	END_ROOM_COLOR  = {0, 0, 0.3, 1}
	TEXT_COLOR = {1, 1, 1, 1}
	ROOM_TEXT_OFFSET_X = -3
	ROOM_TEXT_OFFSET_Y = -7
	DRAGGING = 0

	ANTFARM = {}
	ANTFARM.rooms = {}
	ANTFARM.tubes = {}
	ANTFARM.rounds_of_moves = {}
	ANTFARM.nb_of_rooms = 0
	ANTFARM.nb_of_tubes = 0
	ANTFARM.nb_rounds_of_moves = 0
	ANTFARM.ants_at_end = 0
	MOVES_TO_DRAW = {}

	love.graphics.setBackgroundColor(0.3,0.3,0.5)
	ANT_IMG = love.graphics.newImage("img/ant.png")
	local lines = love.filesystem.lines("visualize_me.output")
	Parse_lines(lines)
	POLYGON = RegularPoly(1200, 800, ANTFARM.nb_of_rooms, 100 + ANTFARM.nb_of_rooms * 3)
	Polygonize_coordinates()
	Mark_paths()
	Give_rooms_color()
	Give_tubes_color()
end

function love.load()
	init_visualizer()
end

function love.draw()
	love.graphics.translate(WINDOW.translate.x, WINDOW.translate.y)
	love.graphics.scale(WINDOW.zoom)
	love.graphics.setColor(1, 1, 1, 0.5)
	Draw_tubes()
	Draw_rooms()
	Draw_start_ants()
	if CURRENT_ROUND > -1 then
		Draw_moves()
	end
end

function love.mousemoved(x, y, dx, dy)
  -- Drag window on mouse move (does nothing if not currently dragging)
	if DRAGGING == 1 then
		WINDOW.translate.x = WINDOW.translate.x + dx
		WINDOW.translate.y = WINDOW.translate.y + dy
	end
end

function love.keypressed(key, scancode, isrepeat)
	if key == "escape" then
		love.event.quit()
	elseif key == "r" then
		init_visualizer()
	end
end

function love.wheelmoved(x, y)
	local mx = love.mouse.getX()
	local my = love.mouse.getY()
    if not (y == 0) then -- mouse wheel moved up or down
--		zoom in to point or zoom out of point
		local mouse_x = mx - WINDOW.translate.x
		local mouse_y = my - WINDOW.translate.y
		local k = DSCALE^y
		WINDOW.zoom = WINDOW.zoom*k
		WINDOW.translate.x = math.floor(WINDOW.translate.x + mouse_x*(1-k))
		WINDOW.translate.y = math.floor(WINDOW.translate.y + mouse_y*(1-k))
	else
--		print ('wheel x: ' .. x .. ' y: ' .. y)
    end
end

function love.mousereleased()
  	DRAGGING = 0
end

function love.mousepressed(x, y, button, istouch)
	if button == 1 then
		if (CURRENT_ROUND < ANTFARM.nb_rounds_of_moves - 1) then
			CURRENT_ROUND = CURRENT_ROUND + 1
			COUNT = 0
			Update_moves(ANTFARM.rounds_of_moves[CURRENT_ROUND], 1)
		end
	elseif button == 2 then
		print("button 2 pressed")
		if USING_ALT_COORDS == 1 then
			print("using orig coords")
			USING_ALT_COORDS = 0
		else
			print("using alt coords")
			USING_ALT_COORDS = 1
		end
		if CURRENT_ROUND > -1 then
			Update_moves(ANTFARM.rounds_of_moves[CURRENT_ROUND], 0)
		end
	elseif button == 3 then
		DRAGGING = 1
	end
end
function love.update(dt)
	COUNT = COUNT + dt
	DTOTAL = DTOTAL + dt

	if (CURRENT_ROUND == -1) then
		Draw_ant(ANTFARM.start_room.x, ANTFARM.start_room.y)
	end
end