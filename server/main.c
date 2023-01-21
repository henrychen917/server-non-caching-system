#include <main.h>



//thread
void* clientHandler(void *_args){
	// int reqCount30 = 100073;
	// int reqCount60 = 100073;
	// int reqCount90 = 74876;
	// int reqCount120 = 74876;
	// int reqCount150 = 74876;
	// int reqCount180 = 74876;
	// int reqCount210 = 74876;
	int reqCount30 = 0;
	int reqCount60 = 0;
	int reqCount90 = 0;
	int reqCount120 = 0;
	int reqCount150 = 0;
	int reqCount180 = 0;
	int reqCount210 = 0;
	time_t start, stop;	
	start = time(NULL);
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

		if (strncasecmp(buf, "exit", 4) == 0){
			printf("Client exited\n");
			send(new_sockfd, "Client exited", 200, 0);
			break;
		}
		char *response = processRequest(buf, pool);
		printf("Response: %s\n", response);
		send(new_sockfd, response, 200, 0);
		stop = time(NULL);


		if (stop - start >= 210){
			break;
		}
		reqCount210++;
		if (stop - start <= 90){
			reqCount90++;
		}
		if (stop - start <= 60){
			reqCount60++;
		}
		if (stop - start <= 30){
			reqCount30++;
		}
		if (stop - start <= 150){
			reqCount150++;
		}
		if (stop - start <= 180){
			reqCount180++;
		}
		if (stop - start <= 120){
			reqCount120++;
		}
	}
	stop = time(NULL);
	printf("30 Request count: %d\n", reqCount30);
	printf("60 Request count: %d\n", reqCount60);
	printf("90 Request count: %d\n", reqCount90);
	printf("120 Request count: %d\n", reqCount120);
	printf("150 Request count: %d\n", reqCount150);
	printf("180 Request count: %d\n", reqCount180);
	printf("210 Request count: %d\n", reqCount210);
	printf("Time: %ld\n", stop - start);
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
