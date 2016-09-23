TARGET	=	${BIN_DIR}/asm-sim

OBJS	=	${wildcard ${OBJ_DIR}/*.o}

${TARGET}:${OBJS}
	${CC} $^ -o $@
	mkdir -p ../build
	cp ${TARGET} ../build/
	cp ../test_files/*.txt ../build/

clean:
	rm asm-sim
	rm -rf ../build
