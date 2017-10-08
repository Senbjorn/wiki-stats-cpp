cc=g++

app: wiki_stats.o wiki_graph.o utf8.o
	$(cc) -o wiki wiki_stats.o wiki_graph.o utf8.o

wiki_stats.o: wiki_stats.cpp
	$(cc) -c -std=c++11 -o wiki_stats.o wiki_stats.cpp

wiki_graph.o: wiki_graph.cpp
	$(cc) -c -std=c++11 -o wiki_graph.o wiki_graph.cpp
	
utf8.o: utf8.cpp
	$(cc) -c -std=c++11 -o utf8.o utf8.cpp