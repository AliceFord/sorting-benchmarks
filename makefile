all:
	g++.exe timer.cpp -o timer
	./timer
	python flatten.py
	python plotter.py

v1:
	g++.exe timer.cpp -o timer
	./timer
	python mergedata.py
	python plotter.py

v2:
	g++.exe timer.cpp -o timer
	./timer
	copy merge.csv data.csv /Y
	python plotter.py
