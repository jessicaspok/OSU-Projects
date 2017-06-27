Jessica Spokoyny
CS 372
Program 2 - ftclient and ftserver

Instructions:
	1. place ftserver.c and text files into one folder
	
	2. place ftclient.py into another folder
	
	3. compile ftserver.c on a flip server using: 
		$ gcc -o ftserver ftserver.c
		
	4. run ftserver using:
		$ ./ftserver <port number>
		example: $ ./ftserver 40020
	
	5. run ftclient.py on another flip server using:
		to request the directory structure:
			$ python ftclient.py <server host> <server port number> -l <data port>
			example: $ python ftclient.py flip1.engr.oregonstate.edu 40020 -l 40022
		OR to request a file
			$ python ftclient.py <server host> <server port number> -g <filename> <data port>
			example: $ python ftclient.py flip1.engr.oregonstate.edu 40020 -g shortfile.txt 40022
			
	6. terminate ftserver using:
		'CRTL-C'
		
Extra Credit:
	The program is also able to transfer files which are not text files
	
Resources:
http://beej.us/guide/bgnet/
http://ecampus.oregonstate.edu/videos/index.php?video=cs372/15.mp4
https://docs.python.org/release/2.6.5/library/internet.html 
http://www.linuxhowtos.org/C_C++/socket.htm
https://www.tutorialspoint.com/python/python_networking.htm
http://stackoverflow.com/questions/82831/how-to-check-whether-a-file-exists-using-python