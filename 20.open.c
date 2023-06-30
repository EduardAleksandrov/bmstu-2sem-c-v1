#include <unistd.h> // is the name of the header file that provides access to the POSIX operating system API
#include <fcntl.h>
#define PERMS 0666

int main(void)
{
    // int fd = creat("./20.Hello.txt", PERMS);
    // write(fd, "Hello world\n", 12);

    // int fd = open("20.Hello.txt", O_RDONLY | O_CREAT);
    // write(fd, "Hello world\n", 12);

    int fd = creat("./20.Hello.txt", PERMS);
    write(fd, "Hello world\n", 12);
    close(fd);
    
    fd = open("20.Hello.txt", O_RDONLY);
    int BUFSIZE = 12;
    char buf[BUFSIZE];
    int n = read(fd, buf, BUFSIZE);
    write(1, buf, n);

    // n = read(fd, buf, BUFSIZE);  //указатель текущей позиции в файле существует
    // write(1, buf, n);

    close(fd);

    return 0;
}



