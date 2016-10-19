#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

void files(const char *name)
{
    DIR *dir;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("find : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
 	printf("%s\n",name);

	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            files(path);
        }
        else
            printf("%s/%s\n",name, filename->d_name);
    } while ((filename = readdir(dir)));
    closedir(dir);
}
void printhelp(void){
	FILE *fp;
	char c, *s="help.txt";
	fp = fopen(s,"r");
	if(fp == NULL){
		printf("cann't open file");
		exit(0);
	}
	c=fgetc(fp);
	while(c != EOF){
		printf("%c",c);
		c=fgetc(fp);
	}
	fclose(fp);
}
int main(int argc,char *argv[])
{
    		if(argv[1] == NULL){
    		       return 0;
    		}
		if(argv[1] == NULL || strcmp(argv[1], "find") != 0){
			printf("Invalid Command name\n");
			return 0;    
		}
		if(argc == 2){
    			if(strcmp(argv[1], "find") == 0)
	    		files(".");		
		}
		if(argc == 3){
    			if(strcmp(argv[1], "find") == 0 && argv[2] == NULL)
	    		files(".");
    			if(strcmp(argv[1], "find") == 0 && strcmp(argv[2], "-h") == 0){
				printhelp();
				return 0;
			}
    			if(strcmp(argv[1], "find") == 0 && argv[2] != NULL)   			
    			files(argv[2]);
    		}
    		if(argc > 3)
    			return 0;
return 0;
}
