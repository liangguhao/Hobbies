shell:shell.c
	gcc shell.c OpenAndReadFile.c GetUserInput.c SubstringExecute.c MyCd.c MyPwd.c -o shell
clean:
	rm shell
