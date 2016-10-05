#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

void listdir(const char *name, int level)
{
    DIR *dir;
    struct dirent *entry;
   
    if (!(dir = opendir(name))){
        //entry = readdir(dir);
    	printf("find : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(entry = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
 	printf("%s\n",name);

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
	    //printf("%s\n", path);
            listdir(path, level + 1);
        }
        else
            printf("%*s/%s\n", level*2, name, entry->d_name);
    } while (entry = readdir(dir));
    closedir(dir);
}
void findfile(const char *name, char *fname, int level)
{
    DIR *dir;
    struct dirent *entry;
    //printf("%s\n", fname);
    //printf("%s\n",name);

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
	    //printf("%s\n", path);
            findfile(path, fname, level + 1);
        }
        else if(strcmp(entry->d_name, fname) == 0)
            printf("%*s/%s\n", level*2, name, entry->d_name);
    } while (entry = readdir(dir));
    closedir(dir);
}
void findfile1(const char *name, char *fname, int level)
{
    DIR *dir;
    struct dirent *entry;
    //printf("%s\n", fname);
    //printf("%s\n",name);

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
	    //printf("%s\n", path);
            findfile1(path, fname, level + 1);
        }
        else if(strcasecmp(entry->d_name, fname) == 0)
            printf("%*s/%s\n", level*2, name, entry->d_name);
    } while (entry = readdir(dir));
    closedir(dir);
}

int main(int argc,char *argv[])
{
int ch;
char dname[50], fname[50];
/*do{
printf("1.Only find Command\n2.find with filename in current directory\n3.find with directory name and file name\n");
printf("Enter Your Option :- ");
scanf("%d", &ch);
switch(ch){
    case 1:*/
    		//printf("%d\n",argc);
    		if(argv[1] == NULL){
    		       return 0;
    		}
		if(argv[1] == NULL || strcmp(argv[1], "find") != 0){
			printf("Invalid Command name\n");
			return 0;    
		}
		if(argc == 2){
    			if(strcmp(argv[1], "find") == 0)
	    		listdir(".", 0);		
		}
		if(argc == 3){
			//printf("%s\n",argv[2]);
    			if(strcmp(argv[1], "find") == 0 && argv[2] == NULL)
	    		listdir(".", 0);
    			if(strcmp(argv[1], "find") == 0 && argv[2] != NULL)
    			
    			listdir(argv[2], 0);
    		}
    		if(argc == 5 || argc == 4){
      			/*printf("%s%s\n", argv[3], argv[4]);
      			if(strcmp(argv[3],"-iname") == 0){
      				printf("-iname\n");
      			}*/
      			if(strcmp(argv[1], "find") == 0 && strcmp(argv[2], ".") == 0 && strcmp(argv[3], "-name") == 0 && argv[4] != NULL)
	    		findfile(argv[2],argv[4], 0);
      			if(strcmp(argv[1], "find") == 0 && strcmp(argv[2], ".") != 0 && strcmp(argv[3], "-name") == 0 && argv[4] != NULL)
	    		findfile(argv[2],argv[4], 0);
      			if(strcmp(argv[1], "find") == 0 && strcmp(argv[2], ".") == 0 && strcmp(argv[3], "-iname") == 0 && argv[4] != NULL)
	    		findfile1(argv[2],argv[4], 0);	 	    		
      			if(strcmp(argv[1], "find") == 0 && strcmp(argv[2], ".") != 0 && strcmp(argv[3], "-iname") == 0 && argv[4] != NULL)
	    		findfile1(argv[2],argv[4], 0);	    			    					
	    		if(argv[4] == NULL)
	    		printf("find : missing argument to '%s'\n",argv[3]);
    		}
    return 0;
}
