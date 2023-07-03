int inicializa_socket();
int fecha_socket(int sockfd);

int envia_push(int sockfd, Branch *branch, char *resp, Hash_No *commits);
int envia_pull(int sockfd, char *resp, Branch **HEAD, Hash_Branch *branches, Hash_No *commits);