executable1 = search
executable2 = cluster

all : search cluster

search : data.cpp Frechet_LSH.cpp LSH.cpp hypercube.cpp search_main.cc continuous/*.cpp
	g++ -o search data.cpp Frechet_LSH.cpp LSH.cpp hypercube.cpp search_main.cc continuous/*.cpp -O2

cluster: data.cpp LSH.cpp hypercube.cpp clustering.cpp Frechet_LSH.cpp Frechet_clustering.cpp cluster_main.cc continuous/*.cpp
	g++ -o cluster data.cpp LSH.cpp hypercube.cpp clustering.cpp Frechet_LSH.cpp Frechet_clustering.cpp cluster_main.cc continuous/*.cpp -O2

clean:
	rm -f $(executable1) $(executable2)