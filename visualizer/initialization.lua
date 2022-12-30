local function init_params()
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
	USING_ALT_COORDS = 1
	IS_FULLSCREEN = true
	DEFAULT_ROOM_COLOR = {0.8, 0.8, 0.8, 0.2}
	DEFAULT_TUBE_COLOR = {1, 1, 1, 1}
	END_ROOM_COLOR  = {0, 0, 0.3, 1}
	TEXT_COLOR = {1, 1, 1, 1}
	ROOM_TEXT_OFFSET_X = -3
	ROOM_TEXT_OFFSET_Y = -7
	DRAGGING = 0
	OVERLAY_FONT = love.graphics.newFont(20)
	DEFAULT_FONT = love.graphics.newFont(12)
end
local function init_graphics()
	love.graphics.setBackgroundColor(0.3,0.3,0.5)
	ANT_IMG = love.graphics.newImage("img/ant.png")
	local lines = love.filesystem.lines("visualize_me.output")
	Parse_lines(lines)
	POLYGON = RegularPoly(love.graphics.getWidth() / 2, love.graphics.getHeight() / 2, ANTFARM.nb_of_rooms, 100 + ANTFARM.nb_of_rooms * 3)
	Polygonize_coordinates()
	Mark_paths()
	Give_rooms_color()
	Give_tubes_color()
end
local function init_antfarm()
	ANTFARM = {}
	ANTFARM.rooms = {}
	ANTFARM.tubes = {}
	ANTFARM.rounds_of_moves = {}
	ANTFARM.nb_of_rooms = 0
	ANTFARM.nb_of_tubes = 0
	ANTFARM.nb_rounds_of_moves = 0
	ANTFARM.ants_at_end = 0
	MOVES_TO_DRAW = {}
end
function Init_visualizer()
	--love.mouse.setRelativeMode(true)
	love.window.setFullscreen(true)
	love.mouse.setVisible(true)

	init_params()
	init_antfarm()
	init_graphics()
end