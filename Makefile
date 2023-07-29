all: 
	gcc find.c -g -Wall -Wvla -fsanitize=address -o find && gcc ls.c -o ls -g -Wall -Wvla -fsanitize=address && gcc tree.c -o tree -g -Wall -Wvla -fsanitize=address
find: find.c
	gcc find.c -g -Wall -Wvla -fsanitize=address -o find
ls: ls.c
	gcc ls.c -o ls -g -Wall -Wvla -fsanitize=address
tree:tree.c
	gcc tree.c -o tree -g -Wall -Wvla -fsanitize=address
clean:
	rm -rf tree ls find