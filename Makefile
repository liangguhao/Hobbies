shell:shell.c
	gcc shell.c OpenAndReadFile.c GetUserInput.c SubstringExecute.c -o shell
clean:
	rm shell
