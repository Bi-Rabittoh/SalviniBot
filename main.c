#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <string.h> /* memcpy, memset */
#include <time.h> /*time */
#include <ctype.h> /*toupper*/
#include "sendPost.h"

//PROTOTYPES
int randomRange(int min, int max);
char randomChar(const char * pool);
int isBlacklisted(char * string, const char ** blacklist, const int blacklist_size);

//MAIN
int main(void){
	const char word[] = "Terrone";
	const char * blacklist[]  = {"Terrone", "Terrona", "Terroni"};
	const int blacklist_size = 3;
    const char vowels_p[] = "aeiou";
    const char consonants_p[] = "bcdfghjklmnpqrstvwxyz";
    const char accesstoken[] = "EAAMRbGEjSYwBAKVGcqPpgZBTQOuDvdHZC9JwCgkrAitvYpbglkGYB69FfAJgtr7fTciCkJC0TwyHnGiolRu4aE4F6AbpRpGQyvrcfHK0egnWjzmZAjCtZCdTLsZB6Cnu2YXj32bk6wIbN0q168XaMXEyMdZBYugafDbQWww1EZBl8DxUc9yQmTiSUFwsUvAcDglBZBTaxZB8LOwZDZD";
    const char pageid[] = "2059873757645281";
    const int wordsize = strlen(word);
    char tempword[wordsize];
    int words, i, j, n_changes, up, doppia;
	
	const int onlineMode = 1;
	
	srand((unsigned int)time(NULL));
	
    for(words = 0; words < 100;) {
   		strcpy(tempword, word);
    	n_changes = randomRange((wordsize / 2) - 1, wordsize); //randomizzo il numero di lettere da cambiare
    	for(j = 0; j < n_changes; j++){
    		//ottengo un carattere casuale nella parola
    		i = randomRange(0, wordsize - 1);
    		
    		//controllo se e' maiuscolo
    		if(tempword[i] >= 65 && tempword[i] <= 90)
				up = 1;
			else
				up = 0;
			
			//controllo se la lettera precedente e' uguale
			if(tempword[i - 1] != NULL){
				if(tempword[i - 1] == tempword[i])
					doppia = 1;
				else
					doppia = 0;
			}
			
			//RANDOMIZZO
    		if(tempword[i] == 'a' || tempword[i] == 'e' || tempword[i] == 'i' || tempword[i] == 'o' || tempword[i] == 'u')
				tempword[i] = randomChar(vowels_p);
			else
				tempword[i] = randomChar(consonants_p);
			
			//uguaglio le doppie se necessario
			if(doppia)
				tempword[i - 1] = tempword[i];
			
			//lo rimetto maiuscolo se necessario
   		 	if(up){
   		 		tempword[i] = toupper(tempword[i]);
			}
		}
		printf("%d. %s cambiando %d lettere.\n", words, tempword, n_changes);
		
		//pubblico il risultato
		if(!isBlacklisted(tempword, blacklist, blacklist_size)){
			 if(!onlineMode){
				words++;
			} else {
				sendPost(tempword, accesstoken, pageid)
				sleep(3600);
			}
		}
	}
	return 0;
}

//FUNCTIONS
int randomRange(int min, int max) {
    return ( rand() % ( max - min + 1 ) ) + min;
}

char randomChar(const char * pool){
	return pool[randomRange(0, strlen(pool) - 1)];
}

int isBlacklisted(char * string, const char ** blacklist, const int blacklist_size){
	int i = 0;
	for(i = blacklist_size - 1; i >= 0; i--){
		if(!strcmp(string, blacklist[i])){
			return 1;
		}
	}
	return 0;
}
