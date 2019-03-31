#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <time.h>
#include "requests.h"

//MAIN
int main(void){
	const char word[] = "hello world!";
	req_t req;
	CURL *curl = requests_init(&req);
	
	char *data[] = {
    "message",  "Hello world",
    "access_token", "EAAMRbGEjSYwBAAQaLd7mXO2igptlUZBgSQhwAoQDpZCkqdgaYSS3xrDVwFshZBzt9C5dFdn7m1t4kwz9KMvB9kbGFq8KJZAELXQJuewE3RzfOGELWc6omAh67u7fvButJaEtMQHHdUXnUdZC7BjAXbQQC1LHT9ClraZB5WTqrAcbpvgcf19nG7pb4gIkNBqNKSZCnuVcKPUoQZDZD"
	};
	
	int data_size = sizeof(data)/sizeof(char*);
	char *body = requests_url_encode(curl, data, data_size);
	
	requests_put(curl, &req, "https://graph.facebook.com/", body);
	puts("fatto!");
    return 0;
}

