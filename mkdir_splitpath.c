

#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

struct NODE* last;
char* path;

struct NODE* nodeSearch(struct NODE* dir, char* dirName, char* parentName){
	if(dir == NULL){
		return NULL;
	}
	if((dirName != NULL) && (strcmp(dir->name, dirName) == 0) && (strcmp(dir->parentPtr->name, parentName) == 0)){
		return dir;
	}

	struct NODE* foundNode = nodeSearch(dir->siblingPtr, dirName, parentName);
	if(foundNode != NULL){
		return foundNode;
	}
	return nodeSearch(dir->childPtr, dirName, parentName);
}


//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    path = malloc(100);
    if(strcmp(pathName, "/") == 0){
	    printf("MKDIR ERROR: no path provided\n");
	    return;
    }

    char* dirName = malloc(100);
    char* baseName = malloc(100);

    struct NODE* returnNode = splitPath(pathName, baseName, dirName);

    if(returnNode == NULL){
	   char* token = strtok(path, "/");
	   struct NODE* check = nodeSearch(root, token, "/");
	   while(token != NULL){
		  if(check == NULL){
			 break;
		  }
		  token = strtok(NULL, "/");
		  check = nodeSearch(root, token, check->name);
	   }
	   printf("ERROR: directory %s does not exist\n", token);
	   return;
    }

    if(nodeSearch(root, baseName, returnNode->name) != NULL){
	   printf("MKDIR ERROR: directory %s already exists\n", path);
	   return;
    }

    struct NODE* newNode = malloc(sizeof(struct NODE));
    newNode->childPtr = NULL;
    newNode->siblingPtr = NULL;
    newNode->parentPtr = returnNode;
    newNode->fileType = 'D';
    strcpy(newNode->name, baseName);
    if(returnNode->childPtr == NULL){
	    returnNode->childPtr = newNode;
    }
    else{
	   last = returnNode->childPtr;
	   while(1){
		   if(last->siblingPtr == NULL){
			   last->siblingPtr = newNode;
			   break;
		   }
		   last = last->siblingPtr;
	   }
    }
    printf("MKDIR SUCCESS: node %s successfully created\n", path);

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    if(strcmp(pathName, "/") == 0){
	    strcpy(baseName, pathName);
	    strcpy(dirName, "");
	    return root;
    }

    char* lastSlash = strrchr(pathName, '/');
    char* target = malloc(100);
    char* parent = malloc(100);
    
    if(lastSlash == NULL){
	    strcpy(baseName, pathName);
	    strcpy(dirName, "");
	    return cwd;
    }

    strcpy(baseName, lastSlash + 1);
    *lastSlash = '\0';
    strcpy(dirName, pathName);

    lastSlash = strrchr(pathName, '/');
	
    if(lastSlash == NULL){
	strcpy(parent, "/");
	strcpy(target, pathName);
    }
    else{
	    *lastSlash = '\0';
	    strcpy(parent, pathName);
	    strcpy(target, lastSlash + 1);
	    lastSlash = strrchr(pathName, '/');
	    if(lastSlash != NULL){
		    strcpy(parent, lastSlash + 1);
	    }
    }

    strcpy(pathName, path);
    return nodeSearch(root,target,parent);
}
