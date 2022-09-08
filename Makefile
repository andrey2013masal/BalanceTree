a.exe: task6_9_main.o  
	wg++ -fno-elide-constructors -std=c++11 task6_9_main.o  


task6_9_main.o: task6_9_main.cpp task6_9_tree.h task6_9_string.h
	wg++ -fno-elide-constructors -std=c++11 task6_9_main.cpp -c
					                  