COMPILER := g++
OUTPUT := codfisc.exe

all: main.o cf.o
	${COMPILER} main.o cf.o -o ${OUTPUT}
	
main.o: main.cpp
	${COMPILER} -c $< -o $@

cf.o: cf.cpp
	${COMPILER} -c $< -o $@
	
clean:
	@del *.o
	@echo Intermediate files were deleted successfully.