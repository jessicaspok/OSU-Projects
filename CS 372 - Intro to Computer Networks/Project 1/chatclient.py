## Jessica Spokoyny
## CS 372
## Program 1 - chat client
## 10/29/2016

from socket import *
import sys
import signal

# close connection when SIGINT
def signal_handler(signal, frame):
	print("Closing connection...")
	print("Closing client...")

	# tell server that client closed connection
	clientSocket.send("\quit")
	sys.exit(0)

# if SIGINT received, use signal handler function
signal.signal(signal.SIGINT, signal_handler)

# validates args
if(len(sys.argv) != 3):
	print("Usage: python chatclient.py <server host name> <port number> ")
	sys.exit(0)
else:
	ip_address = sys.argv[1]
	serverPort = int(sys.argv[2])

# create TCP socket 
clientSocket = socket(AF_INET, SOCK_STREAM)
server_address = (ip_address, serverPort)

# try to connect with server
try:
	clientSocket.connect(server_address)
except:
	print "Connection unsuccessful..."
	sys.exit()

print "Connection established with " + ip_address + " on port " + str(serverPort)

print ""

# validate user handle
while True:
	handle = raw_input('Enter a user handle: ')
	if (len(handle) < 11) and ((' ' in handle) == False):
		break;
	else:
		print "User handle can be at most 10 characters, no whitespace allowed"

print ""

# send message and wait for a response
while True:
	message = raw_input(str(handle) + '> ')
	
	if (len(message) > 512):
		print "Message can be at most 500 characters"

	# if outgoing message is \quit, tell server, close connection
	if message == "\\quit":
		clientSocket.send(message)
		print "\nClient closing connection..."
		print "Server closing connection...\n"
		clientSocket.close()
		break

	# prepend handle to client's message
	message = handle + "> " + message + "\0"

	# send message
	clientSocket.send(message)

	# clear variable storing incoming messages
	newincoming = ""

	# receive messages from the server
	newincoming = clientSocket.recv(1024)
	
	if (len(newincoming) > 520):
		print "Message can be at most 500 characters"
		print ""

	# if incoming message is \quit, close connection
	if newincoming[:5] == "\\quit":
		print "\nServer closing connection..."
		print "Client closing connection...\n"
		clientSocket.close()
		break
	
	# display incoming message
	else:
		sys.stdout.write(newincoming)