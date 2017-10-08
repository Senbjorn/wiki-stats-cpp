app: wiki_stats.o wiki_graph.o utf8.o
		g++ -o wiki wiki_stats.o wiki_graph.o utf8.o

wiki_stats.o: wiki_stats.cpp
	g++ -std=c++11 -o wiki_stat.o wiki_stat.cpp

wiki_graph.o: wiki_graph.cpp
	g++ -std=c++11 -o wiki_graph.o wiki_graph.cpp
	
utf8.o: utf8.cpp
	g++ -std=c++11 -o utf8.o utf8.cpp