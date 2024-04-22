#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


#ifdef __APPLE__
#include "./endian.h"
#else
#include <endian.h>
#endif

#include "./networking.h"
#include "./sha256.h"

char server_ip[IP_LEN];
char server_port[PORT_LEN];
char my_ip[IP_LEN];
char my_port[PORT_LEN];

int c;

/*
 * Gets a sha256 hash of specified data, sourcedata. The hash itself is
 * placed into the given variable 'hash'. Any size can be created, but a
 * a normal size for the hash would be given by the global variable
 * 'SHA256_HASH_SIZE', that has been defined in sha256.h
 */
void get_data_sha(const char* sourcedata, hashdata_t hash, uint32_t data_size, 
    int hash_size){
  SHA256_CTX shactx;
  unsigned char shabuffer[hash_size];
  sha256_init(&shactx);
  sha256_update(&shactx, sourcedata, data_size);
  sha256_final(&shactx, shabuffer);

  for (int i=0; i<hash_size; i++){
      hash[i] = shabuffer[i];
  }
}

/*
 * Gets a sha256 hash of specified data file, sourcefile. The hash itself is
 * placed into the given variable 'hash'. Any size can be created, but a
 * a normal size for the hash would be given by the global variable
 * 'SHA256_HASH_SIZE', that has been defined in sha256.h
 */
void get_file_sha(const char* sourcefile, hashdata_t hash, int size){
    int casc_file_size;

    FILE* fp = Fopen(sourcefile, "rb");
    if (fp == 0){
        printf("Failed to open source: %s\n", sourcefile);
        return;
    }

    fseek(fp, 0L, SEEK_END);
    casc_file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char buffer[casc_file_size];
    Fread(buffer, casc_file_size, 1, fp);
    Fclose(fp);

    get_data_sha(buffer, hash, casc_file_size, size);
}



/*
 * Combine a password and salt together and hash the result to form the 
 * 'signature'. The result should be written to the 'hash' variable. Note that 
 * as handed out, this function is never called. You will need to decide where 
 * it is sensible to do so.
 */
void get_signature(char* password, char* salt, hashdata_t* hash){
    char buffer[PASSWORD_LEN+SALT_LEN+1];
    strcat(buffer, password);
    strcat(buffer, salt);
    get_data_sha(buffer, *hash, strlen(buffer), SHA256_HASH_SIZE);
}


void get_file(char* username, hashdata_t hash, char* to_get){

    //set up connection and buffer and clear previous files
    remove(to_get);
    int clientfd;
    char *buffer = malloc(RESPONSE_HEADER_LEN);
    clientfd = open_clientfd(server_ip, server_port);
    rio_t rio;
    Rio_readinitb(&rio, clientfd);
    
    // create header
    struct RequestHeader header;
    memcpy(header.username, username, USERNAME_LEN);
    memcpy(header.salted_and_hashed, hash, SHA256_HASH_SIZE);
    header.length = htonl(strlen(to_get));   


    // create request
    struct Request package;
    package.header = header;
    memcpy(package.payload, to_get, strlen(to_get));


    //send buffer to server
    memcpy(buffer, &package, sizeof(package));
    Rio_writen(clientfd, buffer, MAX_MSG_LEN); 
    Rio_readnb(&rio, buffer, MAX_MSG_LEN);


    //get codes from server
    char responseCodes[4];
    memcpy(responseCodes, &buffer[0], 4);
    int length = ntohl(*(int*)responseCodes);
    memcpy(responseCodes, &buffer[4], 4);
    int statusCode = ntohl(*(int*)responseCodes);
    memcpy(responseCodes, &buffer[8], 4);
    int blockNumber = ntohl(*(int*)responseCodes);
    memcpy(responseCodes, &buffer[12], 4);
    int totalBlocks = ntohl(*(int*)responseCodes);
    // hashdata_t responsehash;
    // hashdata_t responsefilehash;
    // memcpy(responsefilehash, &buffer[48], SHA256_HASH_SIZE);
    // hashdata_t blockhash;
    if (statusCode != 1){
        return;
    }


    //set up response and file handler
    char *response = malloc(length);
    FILE *file;
    file = fopen(to_get, "a");
    int n = 0;
    //Print to designated file until there are no more unique blocks
    while(n != totalBlocks){
        if(n != blockNumber){
            printf("wrong order\n");
            break;
        }
        

        //Checking if hash values match but it does not work
        // get_data_sha(response, blockhash, length, SHA256_HASH_SIZE);
        // memcpy(responsehash, &buffer[16], SHA256_HASH_SIZE);
        // for (int i = 0; i < SHA256_HASH_SIZE; i++){
        //     if (memcmp(blockhash[i], responsehash[i], SHA256_HASH_WORDS), 0){
        //         printf("fail\n");
        //         printf("blockhash: %02x\n", blockhash);
        //         printf("responsehash: %02x\n", responsehash);
        //         remove(to_get);
        //         return;
        //     }
        // }

        printf("Number of blocks: %d\n", n);
        n++;
        printf("blockNumber: %d\n\n", blockNumber);
        memcpy(response, &buffer[RESPONSE_HEADER_LEN], length+1);
        fprintf(file, response);

        Rio_readnb(&rio, buffer, MAX_MSG_LEN);
        memcpy(responseCodes, &buffer[8], 4);
        blockNumber = ntohl(*(uint32_t*)responseCodes);
    } 

    //close the connection to file and server and free
    fclose(file);
    Close(clientfd);

    //Should check if the hashed files match but does not work
    // hashdata_t hashfile;
    // get_file_sha(to_get, hashfile, SHA256_HASH_SIZE);
    // for (int i = 0; i < SHA256_HASH_SIZE; i++){
    //         if (memcmp(hashfile[i], responsefilehash[i], SHA256_HASH_WORDS), 0){
    //         printf("fail\n");
    //         printf("blockhash: %02x\n", blockhash);
    //         printf("responsehash: %02x\n", responsehash);
    //         remove(to_get);
    //         return;
    //         }
    // }

    free(response);
    free(buffer);
}

/*
 * Register a new user with a server by sending the username and signature to 
 * the server
 */
int register_user(char* username, hashdata_t hash){
    //set up connection and buffer
    int clientfd;
    char *buffer = malloc(RESPONSE_HEADER_LEN);
    clientfd = open_clientfd(server_ip, server_port);
    rio_t rio;
    Rio_readinitb(&rio, clientfd);
    
    //create request
    struct RequestHeader header;
    memcpy(header.username, username, 16);
    memcpy(header.salted_and_hashed, hash, SHA256_HASH_SIZE);
    header.length = 0;

    //load request to buffer, send and read
    memcpy(buffer, &header, sizeof(header));
    Rio_writen(clientfd, buffer, MAX_MSG_LEN); 
    Rio_readnb(&rio, buffer, MAX_MSG_LEN);
    
    //Extract response from sever
    char responseCodes[4];
    memcpy(responseCodes, &buffer[0], 4);
    int length = ntohl(*(int*)responseCodes);
    memcpy(responseCodes, &buffer[4], 4);
    int statusCode = ntohl(*(int*)responseCodes);
    char *response = malloc(length);
    memcpy(response, &buffer[RESPONSE_HEADER_LEN], length);
    for (int i = 0; i < (int)length; i++){
        printf("%c", response[i]);
    }
    putchar('\n'); 

    //close connection and free
    Close(clientfd);
    free(response);
    free(buffer);
    return statusCode;
}


int main(int argc, char **argv){
    
    // Users should call this script with a single argument describing what 
    // config to use
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <config file>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 

    // Read in configuration options. Should include a client_directory, 
    // client_ip, client_port, server_ip, and server_port
    char buffer[128];
    fprintf(stderr, "Got config path at: %s\n", argv[1]);
    FILE* fp = Fopen(argv[1], "r");
    while (fgets(buffer, 128, fp)) {
        if (starts_with(buffer, CLIENT_IP)) {
            memcpy(my_ip, &buffer[strlen(CLIENT_IP)], 
                strcspn(buffer, "\r\n")-strlen(CLIENT_IP));
            if (!is_valid_ip(my_ip)) {
                fprintf(stderr, ">> Invalid client IP: %s\n", my_ip);
                exit(EXIT_FAILURE);
            }
        }else if (starts_with(buffer, CLIENT_PORT)) {
            memcpy(my_port, &buffer[strlen(CLIENT_PORT)], 
                strcspn(buffer, "\r\n")-strlen(CLIENT_PORT));
            if (!is_valid_port(my_port)) {
                fprintf(stderr, ">> Invalid client port: %s\n", my_port);
                exit(EXIT_FAILURE);
            }
        }else if (starts_with(buffer, SERVER_IP)) {
            memcpy(server_ip, &buffer[strlen(SERVER_IP)], 
                strcspn(buffer, "\r\n")-strlen(SERVER_IP));
            if (!is_valid_ip(server_ip)) {
                fprintf(stderr, ">> Invalid server IP: %s\n", server_ip);
                exit(EXIT_FAILURE);
            }
        }else if (starts_with(buffer, SERVER_PORT)) {
            memcpy(server_port, &buffer[strlen(SERVER_PORT)], 
                strcspn(buffer, "\r\n")-strlen(SERVER_PORT));
            if (!is_valid_port(server_port)) {
                fprintf(stderr, ">> Invalid server port: %s\n", server_port);
                exit(EXIT_FAILURE);
            }
        }        
    }
    fclose(fp);

    fprintf(stdout, "Client at: %s:%s\n", my_ip, my_port);
    fprintf(stdout, "Server at: %s:%s\n", server_ip, server_port);
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char user_salt[SALT_LEN+1];
    
    fprintf(stdout, "Enter a username to proceed: ");
    scanf("%16s", username);
    while ((c = getchar()) != '\n' && c != EOF);
    // Clean up username string as otherwise some extra chars can sneak in.
    for (int i=strlen(username); i<USERNAME_LEN; i++) {
        username[i] = '\0';
    }
 
    fprintf(stdout, "Enter your password to proceed: ");
    scanf("%16s", password);
    while ((c = getchar()) != '\n' && c != EOF);
    // Clean up password string as otherwise some extra chars can sneak in.
    for (int i = (int)strlen(password); i<PASSWORD_LEN; i++) {
        password[i] = '\0';
    }

    // Note that a random salt should be used, but you may find it easier to
    // repeatedly test the same user credentials by using the hard coded value
    // below instead, and commenting out this randomly generating section.


    //Seeding the randomiser using username and password to create a unique salt for each user
    srand(strlen(username)+4+strlen(password)*13);
    for (int i=0; i<SALT_LEN; i++){
        // user_salt[i] = saltvalues[SaltAlgorithm(password, i)];
        user_salt[i] = 'a' + (random() % 26);
    }
    user_salt[SALT_LEN] = '\0';  
    printf("%s", user_salt);  


    // Hashing and salting password
    hashdata_t hash;
    get_signature(password, user_salt, &hash);
    printf("%s\n", my_ip);
    printf("%s\n", my_port);


    //overwriting password and salt to erase them for security
    for (int i = 0; i < (int)strlen(password); i++){
        password[i] = 'a';
    }
    for (int i = 0; i < (int)strlen(user_salt); i++){
        user_salt[i] = 'a';
    } 

    // The following function calls have been added as a structure to a 
    // potential solution demonstrating the core functionality. Feel free to 
    // add, remove or otherwise edit. 

    // Register the given user and check if statuscode is good
    if (register_user(username, hash) > 2){
        exit(EXIT_SUCCESS);
    }
    //Retrieve the smaller file, that doesn't not require support for blocks
    get_file(username, hash, "tiny.txt");

    // // Retrieve the larger file, that requires support for blocked messages
    get_file(username, hash, "hamlet.txt");
    exit(EXIT_SUCCESS);
}