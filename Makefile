shell:shell.c
	gcc shell.c OpenAndReadFile.c GetUserInput.c ExtractString.c -o shell
clean:
	rm shell
