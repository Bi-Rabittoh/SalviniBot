#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <time.h>
#include "requests.h" /*randomRange, lists, ...*/

//PROTOTYPES
int randomRange(int min, int max);

//MAIN
int main(void){
	const char word[] = "bartolo gay";
    const char pool[] = "abcdefghilmnopqrstuvz";
    const int poolsize = strlen(pool);
    const int wordsize = strlen(word);
    char tempword[wordsize];
    int i, j, n_changes;

	srand((unsigned int)time(NULL));
    req_t req;
	CURL *curl = requests_init(&req);

    for(i = 0; i < 1000; ++i) {
   		strcpy(tempword, word);
    	n_changes = randomRange(1, wordsize / 2); //randomizzo il numero di lettere da cambiare
    	for(j = 0; j < n_changes; j++){
    		tempword[randomRange(0, wordsize - 1)] = pool[randomRange(0, poolsize - 1)];
		}
		
		//stampo il risultato di tempword
		/*if(strcmp(tempword, word)){
			printf("Ho ottenuto %s cambiando %d lettere.\n", tempword, n_changes);
    	} else {
    		printf("Jackpot!!\n");
  		}*/
  		printf("Ho ottenuto %s cambiando %d lettere.\n", tempword, n_changes);
  		
        //sleep(1);
	}
	return 0;
}

//FUNCTIONS
int randomRange(int min, int max) {
    return ( rand() % ( max - min + 1 ) ) + min;
}
