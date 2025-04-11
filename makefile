all:
	make build run check delete
build:
	gcc gof.c generation.c listlib.c stacklib.c treelib.c -o gof
run:
	bash -c 'for i in $$(seq 1 20); do ./gof "in/data$$i.in" "out/data$$i.out"; done'
check:
	./checker -i
add_files:
	git add gof.c generation.c listlib.c stacklib.c treelib.c generation.h listlib.h stacklib.h treelib.h makefile in ref checker PA_proiect_gameoflife.pdf
delete:
	rm -f gof
	bash -c 'for i in $$(seq 1 20); do rm -f "out/data$$i.out"; done'