# YADRO-Task

Implementation of a test task for YADRO software engineer position

## Task:

The Tape data storage device is designed to write and read data sequentially. The read-write magnetic head is stationary during reading and writing, while the tape has the ability to move in both directions. Information can be written and read to the tape cell on which the magnetic head is currently located. Moving the tape is a time-consuming operation - the tape is not designed for arbitrary access. There is an input tape of length N (where N is large) containing elements of type integer (2^32). There is an output tape of the same length. It is necessary to write into the output tape the elements sorted in ascending order from the input tape. There is a limitation on RAM usage - no more than M bytes (M may be < N, i.e. you cannot load all the data from the tape into RAM). To implement the algorithm, you can use a reasonable number of temporary tapes, i.e. tapes where you can store some temporary information needed during the algorithm's operation.

You need to create a C++ project compiled into a console application that implements an algorithm for sorting data from the input tape to the output tape. The following needs to be done:

- Define an interface to work with a tape type device.
- Write a class that implements this interface and emulates working with the tape by means of a regular file. It should be possible to configure (without recompilation - for example, via an external configuration file that will be read at the start of the application). Delays for writing/reading an item from tape, rewinding tape, and shifting the tape by one position.
- Temporary tape files can be saved to the tmp directory.
- Write a class that implements an algorithm for sorting data from an input tape to an output tape.
- The console application should take as input the name of the input and output files and perform sorting.
- It is desirable to write unit tests.
