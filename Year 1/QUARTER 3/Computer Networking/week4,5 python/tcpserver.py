# simple tcp server
# inspiration from www.digitalocean.com/community/tutorials/python-socket-programming-server-client

import socket

def server_program():
    host = "127.0.0.1"
    port = 5000  # initiate port above 1024

    # create server socket instance
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   
    # addtional options to enable more robust experimentation
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
  
    # bind host address and port together
    server_socket.bind((host, port))  

    # configure how many client the server can listen simultaneously
    server_socket.listen(2)
    print("listening on: "+str(port))
    
    # accept new connection (3-way handshake)
    conn, address = server_socket.accept()  
    data = "Connected to: " + str(address)+"\n"
    print(data)
    # send data to the client
    conn.send(data.encode("utf8"))  
    
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(1024).decode()
        if not data or data.strip().lower() == 'bye':
            print(" Client requested to close the connection.")
            # if data is not received break
            break
        print("received from client: " + str(data))

        #send respond to the client
        data = input(' -> ') + '\n'
        # send data to the client
        conn.send(data.encode("utf8"))  

    conn.close()  # close the connection
    print("Connection closed.")

if __name__ == '__main__':
    server_program()