CXX=g++
# CXXFLAGS=-Wall -Werror -std=c++20 -fsanitize=address
CXXFLAGS=-Wall -Werror -fconcepts -fsanitize=address -std=c++2a
PATH_1=./src/task_1/
PATH_2=./src/task_2/
PATH_3=./src/task_3/
PATH_4=./src/task_4/


smoke_task_1:
	${CXX} ${CXXFLAGS} ${PATH_1}concat.cpp ${PATH_1}test.cpp -o smoke_task_1
	./smoke_task_1


smoke_task_2:
	${CXX} ${CXXFLAGS} ${PATH_2}int_vector.cpp ${PATH_2}test.cpp -o smoke_task_2
	./smoke_task_2


smoke_task_3:
	${CXX} ${CXXFLAGS} ${PATH_3}node_utils.cpp ${PATH_3}test.cpp -o smoke_task_3
	./smoke_task_3


smoke_task_4:
	${CXX} ${CXXFLAGS} ${PATH_4}first.cpp ${PATH_4}second.cpp ${PATH_4}singleton.cpp ${PATH_4}test.cpp -o smoke_task_4
	./smoke_task_4