CUR_PATH = $(shell pwd)

SRC_DIR=${CUR_PATH}/src
LIB_DIR=${CUR_PATH}/lib
INC_DIR=${CUR_PATH}/include
OBJ_DIR=${CUR_PATH}/obj
BIN_DIR=${CUR_PATH}/bin

CC       = gcc 
CXX       = g++
CFLAGS   = -Wall -O -g

CXXFLAGS = 

INCLUDE  = -I ${INC_DIR}

TARGET   = demo
BIN_TARGET = ${BIN_DIR}/${TARGET}
LIBVAR   = -lsqlite3             

SRC = ${wildcard ${SRC_DIR}/*.cpp}

OBJ = $(patsubst %.cpp,${OBJ_DIR}/%.o,$(notdir ${SRC})) 
#OBJ = ${patsubst %.c, %.o, ${SRC}}
#LIBPATH  = -L./dynamiclib/libs  指明 libmytest.so 的路径

#${BIN_TARGET}: ${OBJ} $(LIBVAR)
${TARGET}: ${OBJ} $(LIBVAR)
	${CXX} ${OBJ} -o $@ $(CFLAGS) $(INCLUDE) $(LIBVAR)
	@echo "Compile done."

#下行的 apue.h，可以不必写出来
#${OBJ}:${SRC}
#	$(CC) $(CFLAGS) $(INCLUDE) -c $^
#$(OBJ):%.o:%.c
${OBJ_DIR}/%.o:${SRC_DIR}/%.cpp 
	@echo "Compiling $< ==> $@"
	${CXX} ${CCFLAGS} -c $< -o $@ $(INCLUDE)

#all:$(OBJ) $(LIBVAR)
#	$(CC) $(OBJ) -o $@ $(CFLAGS) $(INCLUDE) $(LIBVAR)

clean:
	rm -f ${OBJ_DIR}/$(OBJ)
	rm -f $(BIN_TARGET)
