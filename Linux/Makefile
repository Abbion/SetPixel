
output: main.o spKeyboard.o spMouse.o spWindowBase.o spWindow.o spRendererBase.o spRenderer.o spEvent.o spColor.o spPixel.o spMath.o spLine.o spCurveLine.o spShapes.o spModelLoader.o spModel.o spMatrix.o spFragmentsMapper.o spClippingAlgorithms.o spCamera.o spBitMap.o spBitMapLoader.o 
	g++ main.o spKeyboard.o spMouse.o spWindowBase.o spWindow.o spRendererBase.o spRenderer.o spEvent.o spColor.o spPixel.o spMath.o spLine.o spCurveLine.o spShapes.o spModelLoader.o spModel.o spMatrix.o spFragmentsMapper.o spClippingAlgorithms.o spCamera.o spBitMap.o spBitMapLoader.o -o main -lX11

main.o: main.cpp
	@echo building main.cpp...
	g++ -c -std=gnu++17 main.cpp

spKeyboard.o: ../sp/spKeyboard.cpp ../sp/spKeyboard.h
	@echo building spKeyboard.cpp...
	g++ -c -std=gnu++17 ../sp/spKeyboard.cpp

spMouse.o: ../sp/spMouse.cpp ../sp/spMouse.h
	@echo building spMouse.cpp...
	g++ -c -std=gnu++17 ../sp/spMouse.cpp

spWindowBase.o: ../sp/spWindowBase.cpp ../sp/spWindowBase.h
	@echo building spWindowBase.cpp...
	g++ -c -std=gnu++17 ../sp/spWindowBase.cpp

spWindow.o: ../sp/spWindow.cpp ../sp/spWindow.h
	@echo building spWindow.cpp...
	g++ -c -std=gnu++17 ../sp/spWindow.cpp

spRendererBase.o: ../sp/spRendererBase.cpp ../sp/spRendererBase.h
	@echo building spRendererBase.cpp...
	g++ -c -std=gnu++17 ../sp/spRendererBase.cpp 

spRenderer.o: ../sp/spRenderer.cpp ../sp/spRenderer.h
	@echo building spRenderer.cpp...
	g++ -c -std=gnu++17 ../sp/spRenderer.cpp

spEvent.o: ../sp/spEvent.cpp ../sp/spEvent.h
	@echo building spEvent.cpp...
	g++ -c -std=gnu++17 ../sp/spEvent.cpp

spColor.o: ../sp/spColor.cpp ../sp/spColor.h
	@echo building spColor.cpp...
	g++ -c -std=gnu++17 ../sp/spColor.cpp

spPixel.o: ../sp/spPixel.cpp ../sp/spPixel.h
	@echo building spPixel.cpp...
	g++ -c -std=gnu++17 ../sp/spPixel.cpp

spMath.o: ../sp/spMath.cpp ../sp/spMath.h
	@echo building spMath.cpp...
	g++ -c -std=gnu++17 ../sp/spMath.cpp

spLine.o: ../sp/spLine.cpp ../sp/spLine.h
	@echo building spLine.cpp...
	g++ -c -std=gnu++17 ../sp/spLine.cpp

spCurveLine.o: ../sp/spCurveLine.cpp ../sp/spCurveLine.h
	@echo building spCurveLine.cpp...
	g++ -c -std=gnu++17 ../sp/spCurveLine.cpp

spShapes.o: ../sp/spShapes.cpp ../sp/spShapes.h
	@echo building spShapes.cpp...
	g++ -c -std=gnu++17 ../sp/spShapes.cpp

spModelLoader.o: ../sp/spModelLoader.cpp ../sp/spModelLoader.h
	@echo building spModelLoader.cpp...
	g++ -c -std=gnu++17 ../sp/spModelLoader.cpp

spModel.o: ../sp/spModel.cpp ../sp/spModel.h
	@echo building spModel.cpp...
	g++ -c -std=gnu++17 ../sp/spModel.cpp

spMatrix.o: ../sp/spMatrix.cpp ../sp/spMatrix.h
	@echo building spMatrix.cpp...
	g++ -c -std=gnu++17 ../sp/spMatrix.cpp

spFragmentsMapper.o: ../sp/spFragmentsMapper.cpp ../sp/spFragmentsMapper.h
	@echo building spFragmentsMapper.cpp...
	g++ -c -std=gnu++17 ../sp/spFragmentsMapper.cpp

spClippingAlgorithms.o: ../sp/spClippingAlgorithms.cpp ../sp/spClippingAlgorithms.h
	@echo building spClippingAlgorithms.cpp...
	g++ -c -std=gnu++17 ../sp/spClippingAlgorithms.cpp

spCamera.o: ../sp/spCamera.cpp ../sp/spCamera.h
	@echo building spCamera.cpp...
	g++ -c -std=gnu++17 ../sp/spCamera.cpp

spBitMap.o: ../sp/spBitMap.cpp ../sp/spBitMap.h
	@echo building spBitMap.cpp...
	g++ -c -std=gnu++17 ../sp/spBitMap.cpp

spBitMapLoader.o: ../sp/spBitMapLoader.cpp ../sp/spBitMapLoader.h
	@echo building spBitMapLoader.cpp...
	g++ -c -std=gnu++17 ../sp/spBitMapLoader.cpp

clean:
	@echo cleaning...
	rm -f *.o main
