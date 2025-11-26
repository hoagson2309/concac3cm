# simple tcp client
# inspiration from www.digitalocean.com/community/tutorials/python-socket-programming-server-client

import socket

def client_program():
    host = "127.0.0.1"      #the server's IP address
    port = 5000             #the server's port number

    #create client server instance
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  

    # connect socket to server
    client_socket.connect((host, port)) #fill in the host and port
     
    # receive initial server response 
    data = client_socket.recv(1024).decode()   #fill in receive method, receive up to 1024 bytes
    print('Received from server: ' + data)  

    # take first input
    message = input(" -> ") +'\n'           # Add a newline character to match the server's expectations
    while message.lower().strip() != 'bye':
        # send message
        client_socket.send(message.encode())    #fill in the send method   
    
        # receive response
        data = client_socket.recv(1024).decode()    #fill in the receive method
        print('Received from server: ' + data)
        
        # again take input  
        message = input(" -> ") + '\n'  

    #close the connection
    client_socket.close()           #fill in the close method

if __name__ == '__main__':
    client_program()