./generator --flow-thousand > ./maps/visualize_me.map
tail -1 [-b] ./maps/visualize_me.map > ./visualizer/required
sh ./visualizer/run_visualizer.sh