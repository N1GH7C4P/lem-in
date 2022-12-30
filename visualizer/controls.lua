local function reset_view()
	WINDOW.translate.x = 0
	WINDOW.translate.y = 0
	WINDOW.zoom = 1
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
	elseif key == "space" then
		reset_view()
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