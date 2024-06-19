#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define TRUE 1

// HTTP 응답 웹페이지
char webpage[] = "HTTP/1.1 200 OK\r\n"
                 "Server: Linux Web Server\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                 "<!DOCTYPE html>\r\n"
                 "<html><head><title>My Web Page</title>\r\n"
                 "<link rel=\"icon\" href=\"data:,\">\r\n"
                 "<style>\r\n"
                 "body { background-image: url('sky.jpg'); background-size: cover; }\r\n"
                 "</style></head>\r\n"
                 "<body><center><h1>Welcome kyeong min Server!!</h1><br>\r\n"
                 "<img src=\"cat.jpg\"></center></body></html>\r\n";

int main(int argc, char *argv[]) {
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t sin_len = sizeof(clnt_addr);
    int serv_sock, clnt_sock;
    char buf[2048];
    int fdimg, img_size;
    int option = TRUE;
    char img_buf[700000];

    // 소켓 생성
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 주소 재사용 옵션 설정
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

    // 서버 주소 구조체 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 소켓을 주소와 포트에 바인딩
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind() error");
        exit(1);
    }

    // 클라이언트의 연결을 대기
    if (listen(serv_sock, 5) == -1) {
        perror("listen() error");
        exit(1);
    }

    while (TRUE) {
        // 새로운 클라이언트 연결 수락
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &sin_len);
        if (clnt_sock == -1) {
            perror("accept() error");
            continue;
        }
        puts("New client connection...");

        // 클라이언트로부터 요청 읽기
        read(clnt_sock, buf, 2047);
        printf("%s\n", buf);

        // 클라이언트가 cat.jpg 또는 sky.jpg 이미지를 요청했는지 확인
        if (strstr(buf, "GET /cat.jpg") != NULL) {
            fdimg = open("cat.jpg", O_RDONLY);
        } else if (strstr(buf, "GET /sky.jpg") != NULL) {
            fdimg = open("sky.jpg", O_RDONLY);
        } else {
            fdimg = -1;
        }

        if (fdimg != -1) {
            // 이미지 파일을 버퍼에 읽기
            img_size = read(fdimg, img_buf, sizeof(img_buf));
            if (img_size == -1) {
                puts("File read error!");
                close(fdimg);
                close(clnt_sock);
								continue;
						}
						close(fdimg);

						// 이미지에 대한 HTTP 헤더 전송
            sprintf(buf, "HTTP/1.1 200 OK\r\n"
                         "Server: Linux Web Server\r\n"
                         "Content-Type: image/jpeg\r\n"
                         "Content-Length: %d\r\n\r\n", img_size);
            if (write(clnt_sock, buf, strlen(buf)) < 0) {
                puts("Header write error!");
            }

            // 이미지 전송
            if (write(clnt_sock, img_buf, img_size) < 0) {
                puts("Image write error!");
            }

            close(clnt_sock);
        } else {
            // 웹페이지 전송
            if (write(clnt_sock, webpage, sizeof(webpage) - 1) == -1) {
                puts("Webpage write error!");
            }
            puts("Closing connection...");
            close(clnt_sock);
        }
    }

    // 서버 소켓 종료
    close(serv_sock);
    return 0;
}
