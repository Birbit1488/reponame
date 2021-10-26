#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX 1000


typedef struct 
{
	int inode;
	int n;
	char name[MAX][MAX];	
} node;

node mynode[MAX];
int k = 0;

int main (){
	DIR *dirp = opendir("/Users/tohat/week10/tmp"); // open the directory named by filename
	struct dirent *dp; 

	while ((dp = readdir(dirp)) != NULL){ // readdir() function returns a pointer to the next directory entry
		if (dp -> d_name[0] == '.')
			continue;
			
		struct stat mystat;
		stat(dp -> d_name, &mystat);
		
		if (mystat.st_nlink < 2) // number of hard links to the file less then 2 or more
			continue;
		
		int flag = 1;
		for (int i = 0; i < k; ++i){ //scan nodes by i-node's number
			if (mynode[i].inode == mystat.st_ino){ //st_ino => i-node's number
				strcpy(mynode[i].name[mynode[i].n], dp -> d_name);
				mynode[i].n++;			
				flag = 0;			
			}
		}
		if (flag){
			mynode[k].inode = mystat.st_ino;
			strcpy(mynode[k].name[mynode[k].n], dp -> d_name);
			mynode[k].n++;						
			k++;		
		}
	}

	closedir(dirp);
	for (int i = 0; i < k; ++i){
		printf("#inode: %d\n%d filenames: ", mynode[i].inode, mynode[i].n);
		for (int j = 0; j < mynode[i].n; ++j){
			printf("%s ", mynode[i].name[j]);
		}
		printf("\n");
	}
	return 0;
}