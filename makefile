all:
	make build check

build:
	gcc gof.c libs/*.c -o gof

run:
	bash -c 'for i in $$(seq 1 20); do ./gof "in/data$$i.in" "out/data$$i.out"; done'

check:
	./checker -i

add_files:
	git add gof.c gof headers libs makefile in ref checker config.json PA_proiect_gameoflife.pdf

compress:
	zip gof.zip gof.c gof libs headers makefile .git

delete:
	rm -f gof
	bash -c 'for i in $$(seq 1 20); do rm -f "out/data$$i.out"; done'

	# use the test.in file to make your own tests and run the project
test:
	gcc gof.c libs/*.c -o teste
	./teste in/test.in out/test.out
	cat out/test.out