shell:shell.c
	gcc shell.c OpenAndReadFile.c GetUserInput.c -o shell
clean:
	rm shell
