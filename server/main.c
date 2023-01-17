#include <main.h>



//thread
void* clientHandler(void *_args){
	time_t start, stop;	
	threadArgs_t *args = (threadArgs_t*)_args;
	char buf[BUFSIZ];
	int len;
	int new_sockfd = args->new_sockfd;

	pool_t *pool = args->pool;
	struct sockaddr_in clnt = args->clnt;


	printf("connect from %s: %d\n",
	inet_ntoa(clnt.sin_addr), ntohs(clnt.sin_port));
	memset(buf, 0, BUFSIZ);
	while (1) {
		len = recv (new_sockfd, buf, BUFSIZ, 0);
		buf[len] = '\0';
		buf[strcspn(buf, "\n")] = 0;
		printf("\nReceived: %s\n", buf);
		start = time(NULL);
		if (strncasecmp(buf, "exit", 4) == 0){
			printf("Client exited\n");
			send(new_sockfd, "Client exited", 200, 0);
			break;
		}
		char *response = processRequest(buf, pool);
		printf("Response: %s\n", response);
		send(new_sockfd, response, 200, 0);
		stop = time(NULL);
		printf("Time taken: %f\n", stop - start);
	}
	close(new_sockfd);


	return 0;
}







int main (int argc, char *argv[]){
	int sockfd, len, new_sockfd;
	pool_t *pool = pool_init(default_size);	
	char buf[BUFSIZ];
	char message[BUFSIZ];
	struct sockaddr_in serv, clnt;
	socklen_t sin_siz;
	int port;
	threadArgs_t *args = pool_alloc(sizeof(threadArgs_t), pool);
	pthread_t threads[100];
	int thread_count = 0;






	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	printf("socket() called\n");
	serv.sin_family = PF_INET;
	if (argc == 3) {
		port = strtol(argv[2], NULL, 10);
	} else {
		port = strtol(DEFAULT_PORT, NULL, 10);
	}

	serv.sin_port = htons(port);	
	if (argc >= 2){
		inet_aton(argv[1], &serv.sin_addr);
	}else{
		inet_aton(DEFAULT_ADDR, &serv.sin_addr);
	}

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

	sin_siz = sizeof(struct sockaddr_in);
	if (bind(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
		perror("bind");
		exit(1);
	}
	printf("bind() called\n");
	if(listen(sockfd, SOMAXCONN) < 0) {
		perror("listen");
		exit(1);
	}
	printf("listen() called\n");
	while(1) {
		if((new_sockfd = accept(sockfd, (struct sockaddr *) &clnt, &sin_siz)) < 0) {
			perror("accept");
		}
		args->new_sockfd = new_sockfd;
		args->clnt = clnt;
		args->pool = pool;
		pthread_create(&threads[thread_count], NULL, clientHandler, args);
		thread_count++;

	}
	close (sockfd);
	return 0;
}


/*

int main (int argc, char *argv[]){
	pool_t *pool = pool_init(default_size);
	node_t *root = diskInit(pool);
	int sockfd, len, new_sockfd;
	char buf[BUFSIZ];
	char message[BUFSIZ];
	struct sockaddr_in serv, clnt;
	socklen_t sin_siz;
	int port;
	


	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	printf("socket() called\n");
	serv.sin_family = PF_INET;
	if (argc == 3) {
		port = strtol(argv[2], NULL, 10);
	} else {
		port = strtol(DEFAULT_PORT, NULL, 10);
	}

	serv.sin_port = htons(port);	
	if (argc >= 2){
		inet_aton(argv[1], &serv.sin_addr);
	}else{
		inet_aton(DEFAULT_ADDR, &serv.sin_addr);
	}



	sin_siz = sizeof(struct sockaddr_in);
	if (bind(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
		perror("bind");
		exit(1);
	}
	printf("bind() called\n");
	if(listen(sockfd, SOMAXCONN) < 0) {
		perror("listen");
		exit(1);
	}
	printf("listen() called\n");
	while(1) {
		if((new_sockfd = accept(sockfd, (struct sockaddr *) &clnt, &sin_siz)) < 0) {
			perror("accept");
		}
		printf("connect from %s: %d\n",
		inet_ntoa(clnt.sin_addr), ntohs(clnt.sin_port));
		memset(buf, 0, BUFSIZ);
		while (strncasecmp(buf, "exit\n", 5) != 0) {
			len = recv (new_sockfd, buf, BUFSIZ, 0);
			buf[len] = '\0';
			buf[strcspn(buf, "\n")] = 0;
			printf("\nReceived: %s\n", buf);
			char *response = processRequest(buf, root, pool);
			printf("Response: %s\n", response);
			send(new_sockfd, response, 200, 0);
		}
		close(new_sockfd);
	}
	close (sockfd);
	diskSaveAll(root);
	return 0;
}

*/
