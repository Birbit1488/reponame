#include <stdio.h>
#include <dirent.h>

int main() {

    DIR *d;
    
    typedef struct dirent dirent;
	
    dirent *dir

    d = opendir("/");
    while ((dir = readdir(d)) != NULL) {

        printf("%s\n", dir->d_name);
    }

    closedir(d);
    return 0;
}
