
build: walsh.cpp statistics.cpp fortificatii.cpp curatare.cpp
	g++ -o walsh walsh.cpp
	g++ -o fortificatii fortificatii.cpp
	g++ -o statistics statistics.cpp
	g++ -o curatare curatare.cpp
clean: walsh fortificatii crypto curatare
	rm walsh
	rm statistics
	rm curatare
	rm fortificatii
run-p1: walsh
	./walsh
run-p2: statistics
	./statistics
