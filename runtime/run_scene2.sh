#!/bin/bash
	# 1. sleep_time 										
	# 2. sheep_count 									
	# 3. boundary_padding 
	# 4. random_seed 
	# 5. Level 


./scene2 &

sleep 10s;
echo Running flock-solve;
#flock-solve  1   2  3  4    5
./flock-solve 1000 10 10 123 2
