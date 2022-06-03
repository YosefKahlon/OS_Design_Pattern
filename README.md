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
        

</div>

This pattern using a thread safe queue  

#### Queue

- createQ - creating a new queue.
- destoryQ - free the queue form the memory.
- enQ - add new item(void *) to the queue. 
- deQ - delete the first from the queue.


The active object handle multiple client, by adding to the queue the num of the file descriptor of the client.

The action : 

1. client is sending text to the server 
2. enQ to the first queue
3. encrypt the text
4. push to the second queue to convert the letters (upper --> lower || lower --> upper)
5. push to the third queue 
6. server return to the client the encrypted text

#### Test 

<div dir='ltr'>

    ./main
    ./activeTest localhost


</div>


### Guard
This Pattern is an app that allows only one thread to enter a function that updates a global pointer .
- Two threads trying to increase global number 
#### Test Guard
<div dir='ltr'>

    ./guardTest


</div>


### Singleton 
The singleton design pattern restricts the instantiation of an object to a single instance .

- Instance -  returns a pointer to the singleton .
- Destroy - Destroy the singleton .

#### Test Singleton 
- Two object from type singleton return the same address 
<div dir='ltr'>

    ./singleton

</div>

### Reactor 

Thread that calls poll

Receives function pointer to call on event

Allows adding and removing file descriptor

A thread that calls poll and calls the registered function.

The server will create a chat between all the client that connect to the server. 

- newReactor - create new Reactor .
- InstallHandler -will get a pointer to Reactor, a pointer to a function and a file descriptor - will install a function that will handle the input only on the file descriptor.
- RemoveHandler - will get a pointer to Reactor will release handler to FD.

<div dir='ltr'>

    ./pollserver
    ./pollclient localhost

</div>


### End 

<div dir='ltr'>

    ./make clean

</div>
