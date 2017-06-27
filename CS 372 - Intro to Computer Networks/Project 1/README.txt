Jessica Spokoyny
Program 1
CS 372

INSTRUCTIONS
To make the program, enter the command: 
	$ make
To remove executables, enter the command:
	$ make clean
If using localhost, both the chat server and the chat client must be running on the same server. I.e. if the server is open on flip2, the client must also be open on flip2. (testing was performed on flip1, flip2, and flip3)

SET UP
First, run the chat server by entering the command:
	$ server <port number>
	Example: $ server 30022
By default, the server runs with the host IP localhost. 
The server will then display a message showing it is waiting for connections on the selected port number.
Next, run the chat client by entering the command:
	$ python chatclient.py <host name> <port number> 
	Example: $ python chatclient.py localhost 30022
For testing purposes, the host name used was ‘localhost’.
Note that the port number entered for the chat client must be the same as the one entered for the chat server.

USAGE
Once the connection is established, both server and client are notified that the connection was successful.
The client must enter a username (no longer than 10 characters and without any whitespace).
Then, the client must enter the first message (up to 500 characters) to be sent to the server.
Upon receiving that message, the server can type out a message to the client.
This process of alternating communication repeats until either the client or server sends the message: “\quit”.
After a “\quit” message, the client closes the connection and exits, but the server closes the connection and stays open on the port listening for new connections.
To close the server program, the command “CTRL-C” must be entered.

RESOURCES
http://beej.us/guide/bgnet/
http://ecampus.oregonstate.edu/videos/index.php?video=cs372/15.mp4
https://docs.python.org/release/2.6.5/library/internet.html 
http://www.linuxhowtos.org/C_C++/socket.htm
https://www.tutorialspoint.com/python/python_networking.htm


