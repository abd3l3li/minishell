#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
 int main()
 { 
    // Checking file descriptors 0 to 255 (commonly used range)
     for (int fd = 0; fd < 256; fd++) 
     { // Try to get the file statusflags for each file descriptor
      if (fcntl(fd, F_GETFD) != -1) 
      { // If fcntl doesn't return -1, the file descriptor is open
       printf("File descriptor %d is open.\n", fd); }
       } 
       return 0; 
}