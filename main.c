/*************************************************************************
*   <find_command>
*   Copyright (C) 2017  Pravin Narayan Tati tatipn16.it@coep.ac.in
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>
**************************************************************************/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "header.h"

int main(int argc,char *argv[]){
			/* ./project  print current directory */
				
			if(argv[1] == NULL){ 
				files(".");
				return 0;
			}
			
			/* ./project -h  print help file */
			
			if(strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-help") == 0){
				printhelp();
				return 0;
			}
				
			if(strcmp(argv[1],"-name") == 0 && argv[2] == NULL){
   				printf("./project : missing argument to '%s'\n", argv[1]);
   				return 0;
			}							
			   	
			if(strcmp(argv[1],"-iname") == 0 && argv[2] == NULL){
   				printf("./project : missing argument to '%s'\n", argv[1]);
   				return 0;
			}
			   				   	
			if(strcmp(argv[1],"-size") == 0  && argv[2] == NULL){
   				printf("./project : missing argument to '%s'\n", argv[1]);
   				return 0;
			}				
			   	
			/* ./project [directory]  print the files form the directory */
			if(argc == 2 &&  argv[1] != NULL){
				files(argv[1]);
				return 0;
			}
			if(argc == 3 && strcmp(argv[2],"-size") == 0  && argv[3] == NULL){
   				printf("./project : missing argument to '%s'\n", argv[2]);
   				return 0;
		   	}				
			   	
		   	/* ./project -size [value]k print files have size as value in current directory */
			if(argc == 3 && strcmp(argv[1],"-size") == 0 && argv[2][strlen(argv[2])-1] == 'k'){
				sizekfile(".", atol(argv[2]));
				return 0;
			}
				
			   /* ./project -size [value]M print files have size as value in current directory */
			if(argc == 3 && strcmp(argv[1],"-size") == 0 && argv[2][strlen(argv[2])-1] == 'M'){
				sizeMfile(".", atol(argv[2]));
				return 0;
			}			
					
			if(argc == 3){
				optional(argv[1],argv[2]);
			}				
				
			/* ./project [directory] -size [value]k print files have size as value in current directory */
			if(argc == 4 && strcmp(argv[2],"-size") == 0 && argv[3][strlen(argv[3])-1] == 'k'){
				sizekfile(argv[1], atol(argv[3]));
				return 0;
			}		
				
			/* ./project [directory] -size [value]M print files have size as value in current directory */
			if(argc == 4 && strcmp(argv[2],"-size") == 0 && argv[3][strlen(argv[3])-1] == 'M'){
				sizeMfile(argv[1], atol(argv[3]));
				return 0;
			}
				
			/* ./project [directory] -name [filename] print files mathches name specified from the directory*/
			if(strcmp(argv[2],"-name") == 0 || strcmp(argv[2],"-iname") == 0){
				namefile(argv[1], argv[3], argv[2]);
				return 0;
			}
				
			/* ./project -name [filename] print files mathches name specified from the directory*/
			if(strcmp(argv[1],"-name") == 0 || strcmp(argv[1],"-iname") == 0){
				namefile(".", argv[2], argv[1]);
				return 0;
			}
				
			/* ./project -type f -empty print empty files from the specified directory*/
			if(argc == 4 && strcmp(argv[1],"-type") == 0 && strcmp(argv[2],"f") == 0 && strcmp(argv[3],"-empty") == 0){
				emptyfile(".");
				return 0;
			}
				
			/* ./project [directory] -type f -empty */			  		
			if(argc == 5 && strcmp(argv[2],"-type") == 0 && strcmp(argv[3],"f") == 0 && strcmp(argv[4],"-empty") == 0){
				emptyfile(argv[1]);
				return 0;
			}  				  	
				
			/* ./project -type f -size [value]k */	
  			if(argc == 5 && strcmp(argv[1],"-type") == 0 && strcmp(argv[2],"f") == 0 && strcmp(argv[3],"-size") == 0 && argv[4][strlen(argv[4])-1] == 'k'){
				sizekfile(".", atol(argv[4]));
				return 0;
			}
				
			/* ./project -type f -size [value]M */
			if(argc == 5 && strcmp(argv[1],"-type") == 0 && strcmp(argv[2],"f") == 0 && strcmp(argv[3],"-size") == 0 && argv[4][strlen(argv[4])-1] == 'M'){
				sizeMfile(".", atol(argv[4]));
				return 0;
			}  				   
				
			/* ./project [directory] -type d -name [filename] */ 			
			if(argc == 6 && strcmp(argv[2],"-type") == 0 && strcmp(argv[3],"d") == 0 && (strcmp(argv[4],"-name") == 0 || strcmp(argv[4],"-iname") == 0)){
				nameFolder(argv[1], argv[5], argv[4]);
				return 0;
			}
				
			/* ./project [directory] -type f -name [filename] */
			if(argc == 6 && strcmp(argv[2],"-type") == 0 && strcmp(argv[3],"f") == 0 && (strcmp(argv[4],"-name") == 0 || strcmp(argv[4],"-iname") == 0)){
				namefile(argv[1], argv[5], argv[4]);
				return 0;
			}
				
			/* ./project [directory] -type f -size [value]k */
			if(argc == 6 && strcmp(argv[2],"-type") == 0 && strcmp(argv[3],"f") == 0 && strcmp(argv[4],"-size") == 0 && argv[5][strlen(argv[5])-1] == 'k'){
				sizekfile(argv[1], atol(argv[5]));
				return 0;
			}
				
			/* ./project [directory] -type f -size [value]M */
			if(argc == 6 && strcmp(argv[2],"-type") == 0 && strcmp(argv[3],"f") == 0 && strcmp(argv[4],"-size") == 0 && argv[5][strlen(argv[5])-1] == 'M'){
				sizeMfile(argv[1], atol(argv[5]));
				return 0;
			}
		return 0;
}
