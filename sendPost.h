#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

int sendPost(char * message, char * accesstoken, char * pageid){
  CURL *curl;
  CURLcode res;
	char body[300];
	char url[60];
	int risultato;
	
  curl_global_init(CURL_GLOBAL_ALL);
  
	strcpy(body, "message=");
	strcat(body, message);
	strcat(body, "&access_token=");
	strcat(body, accesstoken);
	
	strcpy(url, "https://graph.facebook.com/");
	strcat(url, pageid);
	strcat(url, "/feed");
	

  curl = curl_easy_init();
  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);

    res = curl_easy_perform(curl);
    
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      risultato = 0;
	} else risultato = 1;
	
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return risultato;
}
