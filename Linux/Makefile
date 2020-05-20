
output: main.o keyboard.o mouse.o windowBase.o window.o rendererBase.o renderer.o event.o color.o pixel.o spgraphics.o spmath.o
	g++ main.o keyboard.o mouse.o windowBase.o window.o rendererBase.o renderer.o event.o color.o pixel.o spgraphics.o spmath.o -o main -lX11

main.o: main.cpp
	@echo building main.cpp...
	g++ -c main.cpp

keyboard.o: ../sp/keyboard.cpp ../sp/keyboard.h
	@echo building keyboard.cpp...
	g++ -c ../sp/keyboard.cpp

mouse.o: ../sp/mouse.cpp ../sp/mouse.h
	@echo building mouse.cpp...
	g++ -c ../sp/mouse.cpp

windowBase.o: ../sp/windowBase.cpp ../sp/windowBase.h 
	@echo building windowBase.cpp...
	g++ -c ../sp/windowBase.cpp

window.o: ../sp/window.cpp ../sp/window.h
	@echo building window.cpp...
	g++ -c ../sp/window.cpp

rendererBase.o: ../sp/rendererBase.cpp ../sp/rendererBase.h
	@echo building rendererBase.cpp...
	g++ -c ../sp/rendererBase.cpp 

renderer.o: ../sp/renderer.cpp ../sp/renderer.h
	@echo building renderer.cpp...
	g++ -c ../sp/renderer.cpp

event.o: ../sp/event.cpp ../sp/event.h
	@echo building event.cpp...
	g++ -c ../sp/event.cpp

color.o: ../sp/color.cpp ../sp/color.h
	@echo building color.cpp...
	g++ -c ../sp/color.cpp

pixel.o: ../sp/pixel.cpp ../sp/pixel.h
	@echo building pixel.cpp...
	g++ -c ../sp/pixel.cpp

spgraphics.o: ../sp/spgraphics.cpp ../sp/spgraphics.h
	@echo building spgraphics.cpp...
	g++ -c ../sp/spgraphics.cpp

spmath.o: ../sp/spmath.cpp ../sp/spmath.h
	@echo building spmath.cpp...
	g++ -c ../sp/spmath.cpp

clean:
	@echo cleaning...
	rm -f *.o main
