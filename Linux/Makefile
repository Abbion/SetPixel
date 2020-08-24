
output: main.o keyboard.o mouse.o windowBase.o window.o rendererBase.o renderer.o event.o color.o pixel.o spgraphics.o spmath.o spGfxLine.o spGfxCurveLine.o spGfxShapes.o
	g++ main.o keyboard.o mouse.o windowBase.o window.o rendererBase.o renderer.o event.o color.o pixel.o spgraphics.o spmath.o spGfxLine.o spGfxCurveLine.o spGfxShapes.o -o main -lX11

main.o: main.cpp
	@echo building main.cpp...
	g++ -c -std=gnu++17 main.cpp

keyboard.o: ../sp/keyboard.cpp ../sp/keyboard.h
	@echo building keyboard.cpp...
	g++ -c -std=gnu++17 ../sp/keyboard.cpp

mouse.o: ../sp/mouse.cpp ../sp/mouse.h
	@echo building mouse.cpp...
	g++ -c -std=gnu++17 ../sp/mouse.cpp

windowBase.o: ../sp/windowBase.cpp ../sp/windowBase.h
	@echo building windowBase.cpp...
	g++ -c -std=gnu++17 ../sp/windowBase.cpp

window.o: ../sp/window.cpp ../sp/window.h
	@echo building window.cpp...
	g++ -c -std=gnu++17 ../sp/window.cpp

rendererBase.o: ../sp/rendererBase.cpp ../sp/rendererBase.h
	@echo building rendererBase.cpp...
	g++ -c -std=gnu++17 ../sp/rendererBase.cpp 

renderer.o: ../sp/renderer.cpp ../sp/renderer.h
	@echo building renderer.cpp...
	g++ -c -std=gnu++17 ../sp/renderer.cpp

event.o: ../sp/event.cpp ../sp/event.h
	@echo building event.cpp...
	g++ -c -std=gnu++17 ../sp/event.cpp

color.o: ../sp/color.cpp ../sp/color.h
	@echo building color.cpp...
	g++ -c -std=gnu++17 ../sp/color.cpp

pixel.o: ../sp/pixel.cpp ../sp/pixel.h
	@echo building pixel.cpp...
	g++ -c -std=gnu++17 ../sp/pixel.cpp

spgraphics.o: ../sp/spgraphics.cpp ../sp/spgraphics.h
	@echo building spgraphics.cpp...
	g++ -c -std=gnu++17 ../sp/spgraphics.cpp

spmath.o: ../sp/spmath.cpp ../sp/spmath.h
	@echo building spmath.cpp...
	g++ -c -std=gnu++17 ../sp/spmath.cpp

spGfxLine.o: ../sp/spGfxLine.cpp ../sp/spGfxLine.h
	@echo building spGfxLine.cpp...
	g++ -c -std=gnu++17 ../sp/spGfxLine.cpp

spGfxCurveLine.o: ../sp/spGfxCurveLine.cpp ../sp/spGfxCurveLine.h
	@echo building spGfxCurveLine.cpp...
	g++ -c -std=gnu++17 ../sp/spGfxCurveLine.cpp

spGfxShapes.o: ../sp/spGfxShapes.cpp ../sp/spGfxShapes.h
	@echo building spGfxShapes.cpp...
	g++ -c -std=gnu++17 ../sp/spGfxShapes.cpp

clean:
	@echo cleaning...
	rm -f *.o main
