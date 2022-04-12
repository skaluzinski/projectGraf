#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graph.h"
#include "dijkstra.h"
#include "bfs.h"
#include "bfs.c"
    int main(int argc, char **argv){
        srand(time(NULL));
        char *help = "\nhelp\n";
        if(argc < 3){
            fprintf(stderr,"%s",help);
            return 1;
        }
        if(!strcmp(argv[1],"--read")){
            if(argc != 3){
                printf("Podano niepoprawny sposób wywołania programu.\n %s",help);
                return 1;
            }
            Graph *graph = readGraph(argv[2]);
            if(graph == NULL){
                printf("Nie udało się odczytać pliku %s.\n",argv[2]);
                return 1;
            }
            printf("Udało się odczytać graf z pliku %s.\n ",argv[2]);
           return 0; 
        }
        if(!strcmp(argv[1],"--generate")){
            if(argc != 7){
                printf("Podano niepoprawny sposób wywołania programu.\n %s",help);
                return 1;
            }
            double min,max;
            int cols,rows;
            if (sscanf (argv[2], "%lf", &min) != 1) {
                fprintf(stderr, "Podano niepoprawną wartość %s \n.",argv[2]);
                printf("%s",help);
                return 1;
	        }
            if (sscanf (argv[3], "%lf", &max) != 1) {
                fprintf(stderr, "Podano niepoprawną wartość %s \n.",argv[2]);
                printf("%s",help);
                return 1;
	        }
            if (sscanf (argv[4], "%i", &cols) != 1) {
                fprintf(stderr, "Podano niepoprawną wartość %s \n.",argv[2]);
                printf("%s",help);
                return 1;
	        }
            if (sscanf (argv[5], "%i", &rows) != 1) {
                fprintf(stderr, "Podano niepoprawną wartość %s \n.",argv[2]);
                printf("%s",help);
                return 1;
	        }
                               
            Graph *graph = genGraph(min,max,cols,rows);
            if(writeGraphToFile(graph,argv[6]) != 0){
                printf("Nie udało się zapisać do pliku grafu.");
                return 1;
            }
            printf("Graf został zapisany pomyślnie w pliku %s. \n",argv[6]);
	    return 0;
        }

        if(!strcmp(argv[1],"--checkIntegrity")){
            if(argc != 3){
                printf("Podano niepoprawny sposób wywołania programu.\n %s",help);
                return 1;
            }
	    char* name;
	    name = malloc(32);
	   // printf("%s",argv[2]);
	    //sscanf(argv[2],"%s",name);
	    strcpy(name, argv[2]);
            Graph *graph = readGraph(name);

	    printf("%s\n", name);
	    printf("%d\n",graph->nOfVert);
            if (bfs(0,*graph) != 0){
                printf("Graf nie jest spójny.\n");
                return -1;
            }

            printf("Graf jest spójny.\n");
            return 0;
        }
        if(!strcmp(argv[1],"--findPath")){
            if(argc!=5){
                printf("%s\n",help);
                return 1;
            }
            int from,to;
	        if (sscanf (argv[3], "%i", &from) != 1) {
            fprintf(stderr, "error - not an integer");
	        }
	        if (sscanf (argv[4], "%i", &to) != 1) {
            fprintf(stderr, "error - not an integer");
            }
            Graph *graph = readGraph(argv[2]);
	        findPath(*graph,from,to);
        }
        
        return 0;
}
