# provider_Consumber_locking
 
The Producer–Consumer Problem

we presented a semaphore-based solution to the producer–consumer problem using a bounded buffer. 

In this project, you will design a programming solution to the bounded-buffer problem using the producer and consumer processes.
The solution presented uses three semaphores: empty and full, which count the number of empty and full slots in the buffer, and mutex, which is a binary (or mutual-exclusion) semaphore that protects the actual insertion or removal of items in the buffer. 

For this project, you will use standard counting semaphores for empty and full and a mutex lock, rather than a binary semaphore, to represent mutex. 

The producer and consumer—running as separate threads—will move items to and from a buffer that is synchronized with the empty, full, and mutex structures. You can solve this problem using either Pthreads or the Windows API.
