# OS_Design_Pattern

ID: 209011840 ID: 206795841

This project represent some Designs Pattern (Active-object, Pipeline, Guard, Singleton, Reactor )

**Here is the instruction of how to use:**

- Before you start

<div dir='ltr'>

    make all
   

</div>



### Active Object
<div dir='ltr'>

    ./main
    ./client localhost
        write to serve text to encrypt

</div>

This pattern using a thread safe queue  

#### Queue

- createQ - creating a new queue.
- destoryQ - free the queue form the memory.
- enQ - add new item(void *) to the queue. 
- deQ - delete the first from the queue.


The active object handle few client, by adding to the queue the num of the file descriptor of the client.

The action : 

1. client want to encrypt text
2. enQ to first queue
3. encrypt the text
4. push to second queue to convert the latter (upper --> lower || lower -->upper)
5. push to treed queue 
6. return to client the text 

#### Test 

<div dir='ltr'>

    ./main
    ./test

</div>


### Guard
This Pattern is An app that allows only one thread to enter a function that updates a global pointer .

### Singleton 
The singleton design pattern restricts the instantiation of a class to a single instance

- Instance -  returns a pointer to the singleton .
- Destroy - Destroy the singleton .

#### Test singleton 
- Two object from type singleton return the same address 
<div dir='ltr'>

    ./singleton

</div>

### Reactor 

The server will create a chat between all the clients connected to the server. 

- newReactor - create new Reactor .
- InstallHandler -will get a pointer to Reactor, a pointer to a function and a file descriptor - will install a function that will handle the input only on the file descriptor.
- RemoveHandler - will get a pointer to Reactor will release handler to FD.

<div dir='ltr'>

    ./pollserver
    ./pollclient localhost

</div>
