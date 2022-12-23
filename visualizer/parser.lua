require "utils"
function Parse_room(line)
	local room = {}
	local words = Split(line, " ");
	if words[0] and words[1] and words[2] then
		room.name = words[0]
		room.x = words[1] * X_SCALING
		room.y = words[2] * Y_SCALING
		return room
	end
	return nil
end

function Parse_move(word)
	local split_word = Split(word, '-')
	local move = {}
	move.ant_id = string.match(split_word[0], "%d+")
	move.room = Get_room_by_name(split_word[1])
	return(move)
end

function Parse_moves(line)
	local words = {}
	local moves = {}
	words = Split(line, " ");
	local i = 0
	while words[i] do
		moves[i] = Parse_move(words[i])
		i = i + 1
	end
	return moves
end

function Parse_tubes(line)
	local tube = {}
	local words = {}
	words = Split(line, "-");
	tube.tube_start = Get_room_by_name(words[0])
	tube.tube_end = Get_room_by_name(words[1])
	return tube
end

function Parse_lines(lines)
	local i = 0;
	local next_start, next_end;
	for line in lines do
		if i == 0 then
			ANTFARM.nb_of_ants = line * 1
			ANTFARM.ants_at_start = ANTFARM.nb_of_ants
		elseif string.find(line, "##start") then
			next_start = 1
		elseif string.find(line, "##end") then
			next_end = 1
		elseif string.find(line, "#" or line.len < 3) then

		elseif string.find(line, "L") then
			ANTFARM.rounds_of_moves[ANTFARM.nb_rounds_of_moves] = Parse_moves(line)
			ANTFARM.nb_rounds_of_moves = ANTFARM.nb_rounds_of_moves + 1
		elseif string.find(line, "-") then
			ANTFARM.tubes[ANTFARM.nb_of_tubes] = Parse_tubes(line)
			ANTFARM.nb_of_tubes = ANTFARM.nb_of_tubes + 1
		else
			ANTFARM.rooms[ANTFARM.nb_of_rooms] = Parse_room(line)
			if ANTFARM.rooms[ANTFARM.nb_of_rooms] then
				if next_start == 1 then
					ANTFARM.start_room = ANTFARM.rooms[ANTFARM.nb_of_rooms]
					ANTFARM.rooms[ANTFARM.nb_of_rooms].color = {0.3, 0, 0, 1}
					next_start = 0
				elseif next_end == 1 then
					ANTFARM.end_room = ANTFARM.rooms[ANTFARM.nb_of_rooms]
					ANTFARM.rooms[ANTFARM.nb_of_rooms].color = {0, 0, 0.3, 1}
					next_end = 0
				end
				ANTFARM.nb_of_rooms = ANTFARM.nb_of_rooms + 1
			end
		end
		i = i + 1
	end
end