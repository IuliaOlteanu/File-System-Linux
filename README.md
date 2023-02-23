# File - System Linux

The goal of this theme is to implement a minimal file system with lots of operations associated with the CLI, very similar to those on the terminal of a UNIX system, to manipulate that file system. Its structure will be similar to that of a system UNIX-based, by dividing into files and directories, starting from 
the root directory.

**Structure used for describing a directory**

typedef struct Dir {\
char *name;\
    struct Dir* parent;\
	  struct File* head_children_files;\
	  struct Dir* head_children_dirs;\
	  struct Dir* next;\
	  int lung_fisiere;\
	  int lung_dir;\
};

**Structure for describing a file**

typedef struct File {\
	  char *name;\
	  struct Dir* parent;\
	  struct File* next;\
};


**➢touch** 

I allocated memory for a new File node and added it to the end of the file list. If the directory didn't have any files (long_files=0), I added the new file: parent->head_children_files = new. I also checked if there is already a file or directory with this name by going through the list of files, displaying the error message in the affirmative and freeing the allocated memory

**➢mkdir**

Similar to the touch method, memory is allocated for a new Dir type node, and the insertion is all done at the end of the directory list. Check if you want to create a folder with an already existing name, in which case the memory allocated to the Dir node is released and the corresponding error message is displayed

**➢ls**

2 scans are performed: a scan of the list of directories and the display of folder names and a scan of the list of files and a display of file names.

**➢cd** 

Firstly, it is checked if the user wants to change the current directory to the parent directory by the character string "..", in which case the links between parent directories are changed. Then, I go through the list of directories and if they find the name of the director that must be changed with the parent, the change takes place. If after going through the list of directories, the name of the directory is not found, the corresponding error message is displayed.

**➢pwd**

It recursively returns a string representing the path from the root directory to the current directory. I created an auxiliary string s, in which I copy "/" and concatenate the current directory, to be able to put the resulting string in p by concatenating pwd(target->parent) and s.

**➢tree**

It recursively displays the inside of the current directory, respecting the format in the statement: four spaces * level + name file/folder. Go through the list of directories, display the 4 spaces and the name of the current directory, then call the function recursively via
level increase. To display the files, it is proceeded similarly.

**➢stop**

It aims to release the memory allocated for creating the directory list and the file list. The first time, I release the memory for the list of files in the current directory, later I go through the list of directories, free the memory for the files in directories, in the end I release the memory for the directories.

**➢rm**

It deletes the file with the name name received as a parameter from the current directory. I go through the list of files, if I don't find the name
name I display the error message, otherwise I delete the file, free the allocated memory and restore the links between the pointers.

**➢rmdir**

It is similar to the rm function. I go through the list of directories, check if there is a folder with the name name. In case yes, delete the directory together with its list of files, free the memory allocated for the directory and the list of files, otherwise the error message from the statement is displayed.

**➢mv**

It replaces oldname with newname. First of all, I search through newname directories and files, if I find newname I display it error message: "File/Directory already exists\n". Then, I look for oldname through the list of directories and files, if I find it oldname, then I make the change by adding the directory/file to the list of directories/files at the end.

**➢Main**

For reading the orders to be given, I considered 2 types of orders: simple ones, which are not followed by other arguments (such as file/directory names): pwd, ls, tree and composite ones, followed by names in the case of touch commands, mkdir, rm, rmdir, cd, mv. With strtok I copied the file/directory names in aux1 and aux2 in the case of compound commands. The commands are read until the character string "stop" is encountered, at which point the program stops. Finally, the call for releasing the allocated memory and the character strings for which memory was allocated in main: commands, aux1 and aux2.
