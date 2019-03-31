#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <string.h> /* memcpy, memset */
#include <time.h> /*time */
#include <ctype.h> /*toupper*/
#include "onlinestuff.h" //COMMENT THIS IF YOU WANT TO DEBUG OFFLINE

#define onlineMode 1 //CHANGE THIS TO 0 IF YOU WANT TO DEBUG OFFLINE

//PROTOTYPES
int randomRange(int min, int max);
char randomChar(const char * pool);
int isBlacklisted(char * string, const char ** blacklist, const int blacklist_size);
int isPresent(char src, const char * pool);

//MAIN
int main(void) {
    const char word[] = "Terrone";
    const char * blacklist[] = {
        "Terrone",
        "Terrona",
        "Terroni"
    };
    const int blacklist_size = 3;
    const char vowels_p[] = "aeiou"; //all characters missing from this pool are considered consonants
    const char consonants_p[] = "bcdfghlmnpqrstvz";

    const int wordsize = strlen(word);
    char tempword[wordsize];
    time_t clk = time(NULL);
    int words, i, j, n_changes, up = 0, dub = 0;
	srand((unsigned int)time(NULL));

	//read config from config.txt
	FILE * fp;
	fp = fopen("config.txt", "r");
	if (fp == NULL){
		perror("Please create a file named 'config.txt' as explained in the README.");
		exit(EXIT_FAILURE);
	}
	char accesstoken[200];
	char pageid[20];
	fscanf(fp, "%s\n", accesstoken);
	fscanf(fp, "%s\n", pageid);
	fclose(fp);
	
    for (words = 0; words < 100;) {
    	n_changes = randomRange(1, wordsize); //pick a random no. of letters to change
        strcpy(tempword, word);
        for (j = 0; j < n_changes; j++) {
            //pick a random character position
            i = randomRange(0, wordsize - 1);

            //uppercase check
            if (tempword[i] >= 65 && tempword[i] <= 90)
                up = 1;

            /*two-ways double letter check: this always preserves couples of characters
            if (tempword[i + 1] && tempword[i - 1]) {
                if (tempword[i + 1] == tempword[i])
                    dub = 1;
                else if (tempword[i - 1] == tempword[i]) {
                    dub = -1;
                }
            }*/
            
            /*one-way double letter check: this can lose some couples of characters*/
            if(tempword[i - 1]){
            	if(tempword[i - 1] == tempword[i])
            		dub = -1;
			}
			
            //RANDOMIZE
            if (isPresent(tempword[i], vowels_p))
                tempword[i] = randomChar(vowels_p);
            else
                tempword[i] = randomChar(consonants_p);

            //fix couples of letters
            if (dub) {
                tempword[i + dub] = tempword[i];
                dub = 0;
            }

            //fix uppercase characters
            if (up) {
                tempword[i] = toupper(tempword[i]);
                up = 0;
            }
        }
        
        //check if the result is blacklisted
        if (!isBlacklisted(tempword, blacklist, blacklist_size)) {
            if (!onlineMode){
            	printf("%d. %s changing %d letters.\n", words, tempword, n_changes);
                words++; //this generates a finite amount of words in debug mode
            }
            else {
                sendPost(tempword, accesstoken, pageid); //COMMENT THIS IF YOU WANT TO DEBUG OFFLINE
                clk = time(NULL);
                printf("%s%s changing %d letters.\n", ctime(&clk), tempword, n_changes);
                sleep(3600); //1 hour = 60 * 60 seconds
            }
        } else
            puts("Discarded.");
    }
    return 0;
}

//FUNCTIONS
int randomRange(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

char randomChar(const char * pool) {
	return pool[randomRange(0, strlen(pool) - 1)];
}

int isBlacklisted(char * string, const char ** blacklist, const int blacklist_size) {
	int i = 0;
	for (i = blacklist_size - 1; i >= 0; i--) {
		if (!strcmp(string, blacklist[i])) {
			return 1;
		}
	}
	return 0;
}

int isPresent(char src, const char * pool){
	int i;
	for(i = 0; i < strlen(pool); i++){
		if (pool[i] == src)
			return 1;
	}
	return 0;
}

