require "graphics"
require "parser"
require "utils"
require "geometry"
require "initialization"
require "controls"

function love.load()
	Init_visualizer()
end

function love.draw()
	love.graphics.push()
	love.graphics.translate(WINDOW.translate.x, WINDOW.translate.y)
	love.graphics.scale(WINDOW.zoom)
	love.graphics.setColor(1, 1, 1, 0.5)
	love.graphics.setFont(DEFAULT_FONT)
	Draw_tubes()
	Draw_rooms()
	Draw_start_ants()
	if CURRENT_ROUND > -1 then
		Draw_moves()
	else
		if USING_ALT_COORDS == 1 then
			Draw_ant(ANTFARM.start_room.alt_x, ANTFARM.start_room.alt_y)
		else
			Draw_ant(ANTFARM.start_room.x, ANTFARM.start_room.y)
		end
	end
	love.graphics.pop()
	Draw_overlay()
end

function love.update(dt)
	COUNT = COUNT + dt
	DTOTAL = DTOTAL + dt
end