all:
	make build run check
build:
	gcc gof.c libs/*.c -o gof
run:
	bash -c 'for i in $$(seq 17 17); do ./gof "in/data$$i.in" "out/data$$i.out"; done'
check:
	./checker -i
add_files:
	git add gof.c headers libs makefile in ref checker PA_proiect_gameoflife.pdf
compress:
	zip gof.zip gof.c gof libs headers makefile .git
delete:
	rm -f gof
	bash -c 'for i in $$(seq 1 20); do rm -f "out/data$$i.out"; done'
test:
	gcc gof.c libs/*.c -o teste
	./teste test.in test.out
	cat test.out