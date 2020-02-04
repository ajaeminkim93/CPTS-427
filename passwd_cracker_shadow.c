#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#define SHDW_LINE_LEN 256
#define WORD_LEN 80


typedef struct users {
	char* id;
	char* hash;
	char* salt;
}users;


int main(){

	FILE *shadow;
	FILE *dict;
	
	// Open Shadow Folder for Read
	shadow = fopen("shadow", "r");
	if(shadow == NULL) {
		fprintf(stderr, "Cannot Open Shadow File \n");
		exit(1);
	}

	dict = fopen("words.txt", "r");
	if(dict == NULL) {
		fprintf(stderr, "Cannot Open Dict File\n");
		exit(1);
	}

	char shdw_line[SHDW_LINE_LEN];
	int num_accounts = 0;

	//PART A
	//Arrays to store the values into

	users parsed_users[100];


	for(;fgets(shdw_line, SHDW_LINE_LEN, shadow)!=NULL;){
		char *token = strtok(shdw_line, ":");
		parsed_users[num_accounts].id = strdup(token);
		char *shdw_hash = strtok(NULL, ":");
		while(strcmp(shdw_hash, "*")!=0 && strcmp(shdw_hash, "!")!=0){
			printf("%s\n", parsed_users[num_accounts].id);
			token = strtok(shdw_hash, "$");
			token = strtok(NULL, "$");

			parsed_users[num_accounts].salt = strdup(token);
			printf("  salt: %s\n", parsed_users[num_accounts].salt);
			token = strtok(NULL, "$");

			parsed_users[num_accounts].hash = strdup(token);
			printf("  hash: %s\n", parsed_users[num_accounts].hash);
			
			printf("num_accounts = %d\n", num_accounts);
			num_accounts++;
			break;	
		}
		

	}
	
	int i;
	char word[WORD_LEN];
	//char *test = "$6$NrF46O1p$.vDnKEtVFC2bXslxkRuT4FcBqPpxLqW05IoECr0XKzEEO5wj8aU3GRHW2BaodUn4K3vgyEjwPspr/kqzAqtcu.";

	int c = 0;
	while(fgets(word, WORD_LEN, dict)!=NULL){
		int i = 0;
		while(i < num_accounts){
			
			char known_salt[256] = "$6$";

			int j = 0;
			while(j < WORD_LEN){
				if(word[j] == '\n'){
					//printf("End Found\n");
					word[j]=0;
				}
				j++;
			}
		
			
			strcat(known_salt, parsed_users[i].salt);
			strcat(known_salt, "$");
			

			char *hash = crypt(word,known_salt);
			
			strcat(known_salt, parsed_users[i].hash);
			
			if(strcmp(known_salt,hash) == 0){
				printf("FOUND PASSWORD at iteration %d:\nUser: %s\nPasswd: %s\n",c,parsed_users[i].id, word);
			}

			
			i++;

		
		}
	}

	void del_last(char word[]){
		
	}
}
