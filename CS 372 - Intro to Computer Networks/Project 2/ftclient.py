## Jessica Spokoyny
## CS 372
## Program 2 - ft client
## 11/26/2016

#!/bin/python

import socket
import sys
import os
from os import listdir


# set up initial control connection
def initiateContact(serverHost, serverPort):
	# create socket
	controlSocket = socket.socket()
	if (controlSocket == -1):
		return -1

	#connect
	if ((controlSocket.connect((serverHost, serverPort))) == -1):
		return -1

	return controlSocket


# request directory or file over control connection
# 0 for list command
# 1 for get command
def makeRequest(controlSocket, requestType, dataPort, filename):
	ACK = 0
	
	# request directory list
	if (requestType == 0): 
		# send request type
		if (controlSocket.send(str(requestType)) == -1):
			# error
			print >> sys.stderr, 'ERROR: error sending requestType\n\n'
			return -1

		# receive ack
		ACK = controlSocket.recv(4)

		# send data port, add null terminator
		dataPort = dataPort + '\0' 
		if (controlSocket.send(dataPort) == -1):
			# error 
			print >> sys.stderr, 'ERROR: error sending dataPort\n\n'
			return -1

		# receive ack
		ACK = controlSocket.recv(4)

		# get hostname
		clientHost = socket.gethostname()

		if(controlSocket.send(clientHost) == -1):
			# error
			print >> sys.stderr, 'ERROR: error sending hostname\n\n'
			return -1

		# receive ack
		ACK = controlSocket.recv(4)
		
	# request to get file
	elif (requestType == 1): 
		# send request type
		if (controlSocket.send(str(requestType)) == -1):
			# error
			print >> sys.stderr, 'ERROR: error sending requestType\n\n'
			return -1

		# receive ack
		ACK = controlSocket.recv(4)

		# send data port, add null terminator
		dataPort = dataPort + '\0'
		if (controlSocket.send(dataPort) == -1):
			#error
			print >> sys.stderr, 'ERROR: error sending dataPort\n\n'
			return -1

		# receive ack
		ACK = controlSocket.recv(4)

		# get hostname
		clientHost = socket.gethostname()

		# send
		if(controlSocket.send(clientHost) == -1):
			# error
			print >> sys.stderr, 'ERROR: error sending hostname\n\n'
			return -1

		# receive ack
		ACK = controlSocket.recv(4)

		# add null terminator to filename
		filename = filename + '\0'
		
		# send filename
		if (controlSocket.send(filename) == -1):
			#error
			print >> sys.stderr, 'ERROR: error sending filename\n\n'
			return -1
		
		# receive ack
		ACK = controlSocket.recv(4)
	else:
		# invalid request type
		print >> sys.stderr, 'ERROR: error making request to server'
		return -1

	return 0

# receive file from the server on data port
def receiveFile(serverDataSocket, requestType, filename):
	# list directory
	if (requestType == 0): 
		r = 1
		print '\nDirectory Listing:'
		# while directory is not empty
		while(r): 
			# receive
			r = serverDataSocket.recv(40)
			
			# error
			if (r == '-1'):
				print >> sys.stderr, 'ERROR: unable to receive directory\n\n'
				return -1
				
			# end of directory
			elif (r == 0): 
				return 0
				
			# print
			else:
				print '  ' + r

				# send ack
				ACK = 'ACK'
				serverDataSocket.send(ACK)
				
	# get file			
	elif (requestType == 1): 
		#receive length of file
		len = serverDataSocket.recv(15)
		
		#send ack
		ACK = 'ACK'
		serverDataSocket.send(ACK)

		# remove null terminator
		fileLength = int(len.strip('\0'))
		
		# error
		if (fileLength == -1):
			print >> sys.stderr, 'ERROR: file not found\n'
			return -1
			
		#compare name of file to files in directory
		dir = os.listdir('.')

		for file in dir:
			if (file == filename): 
				print "You already have that file..."
				return -1

		# open file
		file = open(filename, "a")

		# receive file
		len = 0 
		
		# while len received < total len expected
		while (len < fileLength): 
			# receive
			r = serverDataSocket.recv(1024)
			
			# error
			if (r == -1):
				print >> sys.stderr, 'ERROR: error receiving file\n\n'
				return -1
				
			# end of file	
			elif (r == 0):
				return 0
			
			# add received portion to file
			else:
				file.write(r.strip('\0'))

				len += 1024

		# send ack
		ACK = 'ACK'
		serverDataSocket.send(ACK)
	
		print 'File transfer complete.'
	return 0

def main(argv):
	# validate command line args
	if (len(sys.argv) < 5):
		print >> sys.stderr, 'ERROR: Too few arguments included\n\n'
		sys.exit(1)
	
	# set up connection
	serverHost = argv[0]
	serverPort = int(argv[1])

	# initiate contact
	controlSocket = initiateContact(serverHost, serverPort)

	if(controlSocket == -1):
		# error
		print >> sys.stderr, 'ERROR: error connection to server\n\n'
		sys.exit(1)
	
	dataPort = 0
	requestType = -1
	filename = -1
	
	#list directory
	if (argv[2] == '-l'): 
		# error
		if (len(sys.argv) != 5):
			print >> sys.stderr, 'ERROR: usage: python ftclient.py <server name> <server port> -l <data port>\n\n'
			sys.exit(1)
	
		# set request type
		requestType = 0;

		# get data port
		dataPort = argv[3]

		# request directory list
		makeRequest(controlSocket, requestType, dataPort, -1)
		
	 # get file	
	elif (argv[2] == '-g'):
		# error
		if (len(sys.argv) != 6):
			print >> sys.stderr, 'ERROR: usage: python ftclient.py <server name> <server port> -g <filename> <data port>\n\n'
		
		# set request type
		requestType = 1

		# get file name
		filename = argv[3]

		# get data port
		dataPort = argv[4]
		
		# request file
		makeRequest(controlSocket, requestType, dataPort, filename)
		
	else: 
		# error
		print >> sys.stderr, 'ERROR: invalid command\n\n'
		sys.exit(1)

	# set up data connection
	dataSocket = socket.socket()
	
	# error
	if (dataSocket == -1):
		print >> sys.stderr, 'ERROR: error creating data socket\n\n'
		exit(1)

	# convert data port to int
	dataPort = int(dataPort)

	# bind
	x = dataSocket.bind(('0.0.0.0', dataPort))
	
	# error
	if(x == -1):
		print >> sys.stderr, 'ERROR: error binding data socket\n\n'
		exit(1)

	# listen
	x = dataSocket.listen(5)
	
	# error 
	if (x == -1):
		print >> sys.stderr, 'ERROR: listening failed for data socket\n\n'
		exit(1)

	# accept
	serverDataSocket, addr = dataSocket.accept()
	
	# error 
	if(serverDataSocket == -1):
		print >> sys.stderr, 'ERROR: error accepteding data socket\n\n'

	receiveFile(serverDataSocket, requestType, filename)

	serverDataSocket.close

	dataSocket.close

	controlSocket.close

	return 0

if __name__ == "__main__":
	main(sys.argv[1:])