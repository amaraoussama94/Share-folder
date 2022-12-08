
# Application 
app :serveur.o   Client.o  
	gcc serveur.o  -o Serveur 
	gcc Client.o  -o Client  
	 
#serveur

Serveur.o:serveur.c
	gcc -c serveur.c

#Client

Client.o:Client.c
	gcc -c Client.c



clean:
#cleanup all object file
	  -rm *.o $(objects) 
	  -rm  Serveur Client