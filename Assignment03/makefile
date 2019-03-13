# For this makefile,
# 	$ make
# 			would compile seach.cpp for part 1 and search for keywords in run
#
# 	$ make search_dat
# 			would compile seach_dat.cpp for part 2, and construct a database called
# 			"database"
# 	$ make search
# 			would compile seach_dat.cpp for part 2, search for keywords in run, and
# 			remove the excutable
# 	$ make clear
# 			would remove the excutable

all : compile run

dat : compile_dat run_dat

search: compile_dat run
	rm search

compile:
	g++ search.cpp -o search

compile_dat:
	g++ search_dat.cpp -o search

clear:
	rm search

run:
	./search fool I am good

run_dat:
	./search --make-database
