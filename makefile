all:
	g++ timer.cpp -o timer
	timer
	python mergedata.py
	python plotter.py

v2:
	g++.exe timer.cpp -o timer
	./timer
	copy merge.csv data.csv /Y
	python plotter.py
