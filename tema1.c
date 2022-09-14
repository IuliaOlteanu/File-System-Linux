#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir {
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
	int lung_fisiere;
	int lung_dir;
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File;

// creare nou fisier in directorul curent
void touch (Dir* parent, char* name) {
	File* nou = (File*)calloc(1, sizeof(File));
	File* aux;
	nou->name = (char*)calloc((strlen(name) + 1), sizeof(char));
	strcpy(nou->name, name);
	nou->parent = parent;
// creare primul fisier 
	if (parent->lung_fisiere == 0) {
		parent->head_children_files = nou;
		parent->lung_fisiere++;
		return;
	}
// verific daca fisierul exista deja in lista de fisiere
	aux = parent->head_children_files;
	while (aux->next != NULL) {
		if (strcmp(aux->name, name) == 0) {
			printf("File already exists\n");
			free(nou->name);
			free(nou);
			return;
		}
	aux = aux->next;
	}
	if (strcmp(aux->name, name) == 0) {
		printf("File already exists\n");
		free(nou->name);
		free(nou);
		return;
	}
// adaugare fisier la finalul listei de fisiere
	parent->lung_fisiere++;
	aux->next = nou;
}

// creare nou director in directorul curent
void mkdir (Dir* parent, char* name) {
	Dir* nou = (Dir*)calloc(1, sizeof(Dir));
	Dir* aux;
	nou->name = (char*)calloc((strlen(name) + 1), sizeof(char));
	strcpy(nou->name, name);
	nou->parent = parent;
// creare primul director
	if (parent->lung_dir == 0) {
		parent->head_children_dirs = nou;
		parent->lung_dir++;
		return;
	}
// verific daca exista deja un fisier/director cu numele dat
	aux = parent->head_children_dirs;
	while (aux->next != NULL) {
		if(strcmp(aux->name, name) == 0) {
			printf("Directory already exists\n");
			free(nou->name);
			free(nou);
			return;
		}
		aux = aux->next;
	}
	if (strcmp(aux->name, name) == 0) {
		printf("Directory already exists\n");
		free(nou->name);
		free(nou);
		return;
	}
// adaugare director nou la sfarsitul listei de directoare
	parent->lung_dir++;
	aux->next = nou;
}

// afisarea tuturor directoarelor si fisierelor din directorul curent
void ls (Dir* parent) {
	Dir* aux;
	int i;

// afisare directoare
	aux = parent->head_children_dirs;
	for (i=0; i < parent->lung_dir; i++) {
		printf("%s\n", aux->name);
		aux = aux->next;
	}

// afisare fisiere
	File* aux1;
	aux1 = parent->head_children_files;
	for (i=0; i < parent->lung_fisiere; i++) {
		printf("%s\n", aux1->name);
		aux1 = aux1->next;
	}		
}

// stergerea fisierului cu numele name din directorul curent
void rm (Dir* parent, char* name) {
	File* sters;
	File* aux;
	int ok = 0;
	int i;

// daca nu exista fisiere 
	if (parent->lung_fisiere == 0) {
		printf("Could not find the file\n");
		return;
	}

	aux = parent->head_children_files;
// sterg primul fisier , daca are numele name dat ca parametru
	if (parent->lung_fisiere == 1 && strcmp(aux->name, name) == 0) {
		parent->lung_fisiere--;
		free(parent->head_children_files->name);
		free(parent->head_children_files);
		parent->head_children_files = NULL;
		return;
	}
// caut si sterg fisierul cu numele name in lista de fisiere
	if (parent->head_children_files != NULL) {
		if (strcmp(aux->name, name) == 0) {
			parent->head_children_files = aux->next;
			parent->lung_fisiere--;
			aux->next = NULL;
			free(aux->name);
			free(aux);
			return;
		} else {
			for (i = 0; i < parent->lung_fisiere - 1; i++) {
				if (strcmp(aux->next->name, name) == 0) {
					ok = 1;
					break;
				}
				aux = aux->next;
			}
		}	
	}
	if (ok == 0)
		printf("Could not find the file\n");
	else if (ok == 1) {
		sters = aux->next;
		aux->next = sters->next;
		sters->next = NULL;
		free(sters->name);
		free(sters);
		parent->lung_fisiere--;
	}
}

// stergerea directorului impreuna cu toate fisierele care se regasesc in el
void rmdir (Dir* parent, char* name) {
	Dir* sters;
	Dir* aux;
	int ok = 0;
	int i;
// daca nu exista directoare
	if (parent->lung_dir == 0) {
		printf("Could not find the dir\n");
		return;
	}
// caut in lista de directoare daca exista un director cu numele name
	if (parent->head_children_dirs != NULL) {
		aux = parent->head_children_dirs;
		if (strcmp(aux->name, name) == 0) {
			if (aux->head_children_dirs != NULL) {
				free(aux->head_children_dirs->name);
				free(aux->head_children_dirs);
			}
			if (aux->head_children_files != NULL) {
				free(aux->head_children_files->name);
				free(aux->head_children_files);
			}
			parent->head_children_dirs = aux->next;
			parent->lung_dir--;
			aux->next = NULL;
			free(aux->name);
			free(aux);
			return;
		} else {
			for (i = 0; i < parent->lung_dir - 1; i++) {
				if (strcmp(aux->next->name, name) == 0) {
					ok = 1;
					break;
				}
				aux = aux->next;
			}
		}	
	}
	if (ok == 0)
		printf("Could not find the dir\n");
// elimin directorul alaturi de toate fisierele existente in acesta
	else if (ok == 1) {
		sters = aux->next;
		if (sters->head_children_dirs != NULL) {
			free(sters->head_children_dirs->name);
			free(sters->head_children_dirs);
		}
		if (sters->head_children_files != NULL) {
			free(sters->head_children_files->name);
			free(sters->head_children_files);
		}
		aux->next = sters->next;
		sters->next = NULL;
		free(sters->name);
		free(sters);
		parent->lung_dir--;
	}
	 
}

// schimbare director curent in directorul cu numele name
void cd (Dir** target, char *name) {
	Dir* aux;
	aux = (*target)->head_children_dirs;
// verific daca se doreste schimbarea directorului curent in directorul parinte
	if (strcmp(name,"..") == 0) {
		if ((*target)->name == NULL)
			return;
		*target = (*target)->parent;
		return;
	}
	int i;
// parcurg lista de directoare si caut directorul cu numele name in lista
	for (i = 0; i < (*target)->lung_dir; i++) {
		if (strcmp(aux->name, name) == 0) {
			*target = aux;
			return;
		}
		aux = aux->next;
	}
	printf("No directories found!\n");
}

// intoarcere sir care contine calea de la home pana la directorul curent
char *pwd (Dir* target) {
	char* s = malloc(MAX_INPUT_LINE_SIZE);
	char* p;
	if (target->name == NULL){
		strcpy(s, "/home");
		return s;
	}
	strcpy(s, "/");
	strcat(s, target->name);
	p = strcat(pwd(target->parent), s);
	free(s);
	return p;

}

// seliberarea memoriei alocate pentru crearea listelor de directoare si fisiere
void stop (Dir* target) {
	Dir *cr2, *aux2;
	File *cr1, *aux1;
	cr2 = target->head_children_dirs;
	cr1 = target->head_children_files;
// eliberez memoria din lista de fisiere
	while(cr1 != NULL) {
		aux1 = cr1;
		cr1 = cr1->next;
		free(aux1->name);
		free(aux1);
	}
// eliberez memoria din lista de directoare 
	while (cr2 != NULL) {
		aux2 = cr2;
		stop(cr2);
		cr2 = cr2->next;
		free(aux2->name);
		free(aux2);
	}
}

// afisare in forma arborescenta a interiorului directorului curent
void tree (Dir* target, int level) {
	Dir* aux;
	File* aux1;
	int i, j;
// afisare directoare din lista de directoare
	aux = target->head_children_dirs;
	for (i = 0; i < target->lung_dir; i++) {
		for (j = 0; j < level; j++)
			printf("    ");
		printf("%s\n", aux->name);
		tree(aux, level+1);
		aux = aux->next;
	}
// afisare fisiere din lista de fisiere
	aux1 = target->head_children_files;
	for (i = 0; i < target->lung_fisiere; i++) {
		for (j = 0; j < level; j++)
			printf("    ");
		printf("%s\n", aux1->name);
		aux1 = aux1->next;
	}
}

// schimbare numele directorului/fisierului oldname in newname
void mv (Dir* parent, char *oldname, char *newname) {
	Dir* aux;
	File* aux1;
	Dir* cr;
	aux = parent->head_children_dirs;
	aux1 = parent->head_children_files;
	int i, j, ok = 0;
// caut newname printre directoare
	for (i = 0; i < parent->lung_dir; i++) {
		if (strcmp(aux->name, newname) == 0) {
			printf("File/Director already exists\n");
			return;
		}
		aux = aux->next;
	}
// caut newname printre fisiere
	for (i = 0; i < parent->lung_fisiere; i++) {
		if (strcmp(aux1->name, newname) == 0) {
			printf("File/Director already exists\n");
			return;
		}
		aux1 = aux1->next;
	}
// readaugarea directorului/fisierului in lista de directoare/fisiere
	aux = parent->head_children_dirs;
	aux1 = parent->head_children_files;
	for (i = 0; i < parent->lung_dir; i++) {
		if(strcmp(aux->name, oldname) == 0) {
				ok = 1;
				strcpy(aux->name, newname);
				break;
			}
		aux = aux->next;
	}
	if (ok == 0) {
		for (j = 0; j < parent->lung_fisiere; j++) {
			if (strcmp(aux1->name, oldname) == 0 ) {
				ok = 1;
				strcpy(aux1->name, newname);
			}
			aux1 = aux1->next;
		}
	}
	if (ok == 0) {
		printf("File/Director not found\n");
		return;
	}
}

// comenzi simple , neurmate de alte argumente: pwd , ls, tree
// comenzi urmate de nume : touch , mkdir , rm , rmdir , cd 
int main () {
	Dir* parent = (Dir*)calloc(1, sizeof(Dir));
	Dir* aux;
	aux = parent;
	parent->lung_dir = 0;
	parent->lung_fisiere = 0;

	char *comenzi = malloc(MAX_INPUT_LINE_SIZE);
	char *p ;
	char *q ;
	char *r ;
	char *aux1 = malloc(MAX_INPUT_LINE_SIZE);
	char *aux2 = malloc(MAX_INPUT_LINE_SIZE);
	char *Pwd;

	do {
		fgets(comenzi, MAX_INPUT_LINE_SIZE, stdin);
		comenzi[strlen(comenzi) - 1] = '\0';
		
//afisare directoare + fisiere din folderul curent
		if (strcmp(comenzi,"ls") == 0) 
			ls(parent);
		
//afisare cale de la radacina pana la target
		if (strcmp(comenzi, "pwd") == 0){
			Pwd = pwd(parent);
			printf("%s\n", Pwd);
			free(Pwd);
		}
// afisare arborescenta 
		if (strcmp(comenzi, "tree") == 0)
			tree(parent,0);
// pun in aux1 numele care urmeaza dupa comanda (nume de fisier , nume de director)
// pun in aux2 newname pentru comanda mv
		p = strtok(comenzi, " ");
		q = strtok(NULL, " ");
		if (q != NULL) 
			strcpy(aux1, q);
		r = strtok(NULL, " ");
		if (r != NULL)
			strcpy(aux2, r);

// schimba directorul 
		if (strcmp(p, "cd") == 0)
			cd(&parent, aux1);

// sterge un fisier
		if (strcmp(p, "rm") == 0)
			rm(parent, aux1);

// stergerea unui director impreuna cu fisierele sale
		if (strcmp(p, "rmdir") == 0)
			rmdir(parent, aux1);

// crearea unui nou director
		if (strcmp(p, "mkdir") == 0)
			mkdir(parent, aux1);

// crearea unui nou fisier
		if (strcmp(p, "touch") == 0)
			touch(parent, aux1);

// mutare dir/fisier din oldname in newname
		if (strcmp(p, "mv") == 0)
			mv(parent, aux1, aux2);
		
	}while (strcmp(comenzi, "stop") != 0);
// eliberare memorie
	stop(aux);
	free(aux->name);
	free(aux);

	free(comenzi);
	free(aux1);
	free(aux2);

	return 0;
}
