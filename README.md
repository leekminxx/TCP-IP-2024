# TCP-IP-2024
TCP/IP-2024


## 1일차 
- TCP/IP - cmd > ipconfig
    - 전송방식: TCP / UDP 
       - TCP (Transmission Control Protocol)
            - 연결 지향적: 데이터 전송 전에 송신자와 수신자 간에 연결을 확립
            - 신뢰성: 데이터가 손실되거나 손상되지 않도록 보장합니다. 손실된 데이터는 재전송
            - 데이터 순서 보장: 송신한 순서대로 데이터가 수신
            - 흐름 제어 및 혼잡 제어: 네트워크 혼잡을 방지하기 위해 데이터 전송 속도를 조절

       - UDP (User Datagram Protocol)

            - 비연결 지향적: 데이터 전송 전에 연결을 확립하지 않음
            - 신뢰성 부족: 데이터가 손실되거나 손상될 수 있으며, 재전송을 보장하지 않음
            - 데이터 순서 미보장: 데이터가 송신한 순서대로 수신되지 않을 수 있음
            - 저오버헤드: 추가적인 제어 정보가 적어 전송 속도가 빠름

            - 소->소켓(socket) : 소켓 생성은 통신의 출발점입니다. 소켓은 네트워크 통신의 끝점을 나타내며, IP 주소와 포트 번호의 조합을 통해 통신을 설정
            - 말->바인더(bind) : 바인드는 소켓에 IP 주소와 포트 번호를 할당하는 단계입니다. 이 단계는 서버에서만 필요하며, 클라이언트는 일반적으로 바인드를 수행하지 않음.
            - 리->리슨(listen) : 리슨은 서버 소켓이 들어오는 연결 요청을 대기하도록 설정하는 단계입니다. 이 단계에서는 연결 대기열의 크기도 지정.
            - 아->엑셉트(accept) : 엑셉트는 들어오는 연결 요청을 수락하고, 새로운 소켓 객체를 반환하는 단계입니다. 이 새로운 소켓은 클라이언트와의 통신을 처리하는 데 사용됨.
            

    - 네트워크 프로그래밍에서 연결요청을 허용하는 소켓의 생성과정을 정리

        - 1단계 : 소켓 생성 (soket 함수호출)
        - 2단계 : IP 주소와 PORT번호 할당 (bind 함수호출)
        - 3단계 : 연결요청 가능상태로 변경(listen 함수호출)
        - 4다계 : 연결요청에 대한 수락 (accept 함수호출)

    - 리눅스 기반 파일 조작하기 
        - 저 수준 파일 입출력(Low-level File Access) 과 파일 디스크립터(File Descriptor)
            - 파일 디스크립터 
                - 0 : 표준입력 
                - 1 : 표준출력
                - 2 : 표준에러 
            
            - 파일 열기
                - O_CREAT : 필요하면 파일을 생성
                - O_TRUNC : 기존 데이터 전부 삭제
                - O_APPEND : 기존 데이터 보존하고 , 뒤에 이어서 저장
                - O_RDONLY : 읽기 전용으로 파일 오픈
                - O_WRONLY : 쓰기 전용으로 파일 오픈
                - o_RDWR : 읽기 , 쓰기 겸용으로 파일 오픈 


- 소켓의 프로토콜과 그에 따른 데이터 전송 특성

    - 프로토콜이란?
        - 컴퓨터 상호간의 대화에 필요한 통신규약 
    
    - 프로토콜 체계
        - PF_INET : IPv4 인터넷 프로토콜 체계
        - PF_INET6 : IPv6 인터넷 프로토콜 체

    - 소켓의 타입 1 : 연결지향형 소켓 (SOCK_STREAM)  == TCP
        - 중간에 데이터가 소멸되지 않고 목적지로 전송된다.
        - 전송 순서대로 데이터가 수신된다.
        - 전송되는 데이터의 경계(Boundary)가 존재하지 않는다.
        - 즉 , 연결지향형 소켓 하나는 다른 연결지향형 소켓 하나와만 연결이 가능하다. (소켓 대 소켓의 연결은 반드시 1대1이어야 한다.!)
        - 신뢰성 있는 순차적인 바이트 기반의 연결지향 데이터 전송 방식의소켓!
    
    - 소켓의 타입 2 : 비연결지향형 소켓 (SOCK_DGRAM) == UDP
        - 전송된 순서에 상관없이 가장 빠른 전송을 지향한다.
        - 전송된 데이터는 손실의 우려가 있고, 파손의 우려가 있다 
        - 전송되는 데이터의 경계(Boundary) 가 존재한다.
        - 한번에 전송할 수 있는 데이터의 크기가 제한된다.
        - 신뢰성과 순차적 데이터 전송을 보장하지 않는 , **고속의 데이터 전송을** 목적으로 하는 소켓!


- 소켓에 할당되는 IP주소와 PORT 번호 
    - IP: 인터넷상에서 데이터를 송수신할 목적으로 컴퓨터에게 부여하는 값
    - PORT 번호 : 컴퓨터에게 부여하는 값이 아닌, 프로그램상에서 생성되는 소켓을 구분 하기 위해 소켓에 부여되는 번호 

    - 인터넷 주소 
        - IPv4 : 4바이트 주소체계
        - IPv6 : 16바이트 주소체계
        - IPv4 와 IPv6의 차이점은 IP주소의 표현에 사용되는 바이트 크기에 있음 
    
    - **클래스 별 네트워크 주소와 호스트 주소의 경계**
        - IP 주소의 첫 번째 바이트만 보면 몇 바이트인지 판단이 가능 함
            - 클래스 A의 첫 번째 바이트 범위 (0이상 127이하)   - **즉 클래스 A의 첫 번째 비트는 항상 0으로 시작**
            - 클래스 B.의 첫 번째 바이트 범위 (128이상 191이하) - **즉 클래스 B의 첫 두 비트는 항상 10으로 시작**
            - 클래스 C의 첫 번째 바이트 범위 (192이상 223이하)  - **즉 클래스 C의 첫 세 비트는 항상 110으로 시작**
        - 기준이 정해져있음으로 데이터를 송수신할때 별도로 신경쓸 필요 없이 네트워크로 데이터가 이동하고 최종 목적지인 호스트로 데이터가 전송 됨 

    - **네트워크로 데이터가 전송된다는것은 네트워크를 구성하는 라우터(Router) 또는 스위치 (Switch)로 데이터가 전송됨을 뜻함.**
        - IP는 컴퓨터를 구분하는 목적으로만 존재하기 때문에 IP만 가지고있다면 원하는 목적지로 데이터를 전송할수는 있어도 최종 응용프로그램까지는 전달할 수 없기때문에 **PORT번호가 필요로 함** 

    - PORT 
        - 번호는 하나의 운영체제 내에서 소켓을 구분하는 목적으로 사용되기 때문에 하나의 운영체제 내에서 동일한 번호를 사용할 수 없음!
        - 16비트로 표현 됨 , 범위는 (-dltkd 65535이하) 까지 , 하지만 0부터 1023번까지는 예약번호이기때문에 제외한 다른값을 할당 해주어야 함
        - 중복이 불가능하지만 TCP , UDP 소켓은 PORT번호를 공유하지는 않기때문에 상관없음
        - 정리하자면 TCP > 9190 PORT번호 할당 했다면 > 다른 TCP 소켓에는 9190 번호 X > 하지만 UDP 소켓에서는 할당가능!

- IPv4 기반의 주소표현을 위한 구조체 
    - posix 사진
        - 이렇게 자료형을 별도로 정의 해둔 이유는 확장성을 **고려한 결과** 즉 int32_t 라는 자료형을 사용한다면 , 어떠한 경우에도 4바이트 자료형임을 보장받을 수 있다.

    - 구조체 sockaddr_in의 멤버에 대한 분석 
        - 주소체계
            - AF_INET : IPv4 인터넷 프로토콜에 적용하는 주소체계
            - AF_INET6: IPv6 인터넷 프로토콜에 적용하는 주소체계
            - AF_LOCAL: 로컬 통신을 위한 유닉스 프로토콜의 주소체계 

    - 네트워크 바이트 순서와 인터넷 주소 변환
        - **CPU에 따라서 4바이트 정수 1을 메모리공간에 저장하는 방식이 달라질 수 있음**
            - 순서 그대로 메모리에 저장하는 CPU가 있는 반면 , 거꾸로 저장하는 CPU도 존재하기 때문
            - 데이터의 저장순서가 다른것은 전송되어온 해석순서가 다름을 뜻하기 때문

        - 바이트 순서(Order)와 네트워크 바이트 순서
            - 빅 엔디안 (Big Endian) : 상위 바이트의 값을 작은 번지수에 저장하는 방식
                - ex: 0x1234567은 가장 나은 번지부터 0x12 0x34 0x56 0x78순서로 담긴다. (상위 바이트는 12이다.)
            - 리틀 엔디안(Little Endian) : 상위 바이트의 값을 큰 번지수에 저장하는 방식
                - ex: 00x1234567은 0x78 0x56 0x34 0x12 순서로 담긴다.
            
            - 데이터 송수신 과정에서 데이터 저장방식의 차이 문제가 발생할 수 있기때문에 송수신을 할때에는 약속이 필요 함
            - 보내는 쪽 , 받는 쪽 모두 BigEndian/ LittleEndian이든 상관없이 보내는 바이트의 수서는 낮은 주소로부터 전송 (빅에디안) 한다는것을 알려야 함 
            - 네트워크 바이트 순서는 BigEndian 기준 ! (낮은 주소의 데이터 번지부터 전송!) 낮은 주소를 significantbyte로 취급하라고 알려줌

        - 바이트 순서의 변환(Endian Conversions)
            - unsigned short htons(unsigned short);
            - unsigned short ntohs(unsigned short);
            - unsigned long htonl(unsigned long);
            - unsigned long ntonl(unsigned long);

            - htons에서의 h는 호스트(host) 바이트 순서를 의미
            - htons에서의 n은 네트워크(network) 바이트 순서를 의미

            - s는 short 를 l은 long를 의미함 **(무엇보다 중요한것은 리눅스에서 long형은 4바이트라는 사실 short는 2바이트를 의미 PORT번호의 변환에 사용됨)**
            - htons : short 형 데이터를 호스트바이트순서에서 네트워크바이트 순서로 변환!
            - ntohs : short 형 데이터를 네트워크 바이트 순서에서 호스트 바이트 순서로 변환! 
        

## 2일차
   -  인터넷 주소의 초기화
    - memset : 구조체를 초기화 시킬때 사용되는 함수  
    - memset 함수를 사용 하는 이유 : sockaddr_in 구조체 변수의 마지막 8byte변수는 사용하지 않기 때문에 모두 0으로 채울 필요가 있다 . 
   
   - 문자열 정보를 네트워크 바이트 순서의 정수로 변환하기 
    - sockaddr_in 안에서 주소정보를 저장하기 위해 선언된 멤버는 32비트 정수형으로 정의 되어있음

   - 소켓에 인터넷주소 할당하기 
    - bind 함수가 필요로 함 

   - TCP 와 UDP 에 대한 이해
    - SOCK_STREAM : TCP 소켓임을 의미
      두번째 인자의 경우, 데이터의 전송 방식에 따라 TCP 와 UDP로 나눌 수 있다.
      TCP는 연결지향형 방식으로, 신뢰성이 높다는 특징을 가진다. 데이터가 소실없이, 순서대로 전달되어야만 하는 응용프로그램들에 주로 이용된다.
      UDP는 비 연결지향형 방식으로, 빠른 전송을 지향한다. 실시간 화상과 같은 속도가 중요한 응용 프로그램들에 주로 사용된다.
      UDP 소켓을 원할 경우 SOCK_DGRAM으로 대체해준다.

   - LINK 계층 
    - 물리적인 영역의 표준화에 대한 결과 가장 기본이 되는 영역 LAN , WAN , MAN 과 같은 네트워크 표준과 관련된 프로토콜을 정의하는 영역

   - IP 계층 
    - 목적지로 데이터를 전송하기 위해서 중간에 IP 프로토콜을 거친다 
    - 비연결지향적이며 신회 할 수 없는 프로토콜이다
    - 데이터를 전송할 때마다 경로를 선택해줌 > 경로상 문제가 발생하면 다른경로 추천 > 이 과정에서 데이터 손실 발생할 수 있음
    - 즉 , 오류발생에 대한 대비가 되어있지 않음 

   - TCP / UDP  계층 
    - IP 계층에서 경로의 검색을 해결해주기때문에 UDP 에서는 데이터 전송만 하면 됨 
    - 송수신을 담당하는 계층 (Tracnsport) 계층 이라고 함 
    - UDP 는 TCP 보다 상대적으로 간단 
    - TCP : 신뢰정있는 데이터 전송담당 ,, 하지만 IT기반

   - TCP 기반 서버 , 클라이언트 구현
    - TCP 서버에서의 기본적인 함수호출 순서
        - socket() 소켓생성 > bind() 소켓 주소할당 > listen() 연결요청 대기상태 > accept() 연결허용 > read()/write() 데이터 송수신 > close() 연결종료

        - bind 함수호출을 통해서 소켓에 주소까지 할당했으면 listen 함수호출을 통해서 '연결요청 대기  상태' 가 있음 listen 함수가 호출되어야 클라이언트가 연결요청을 할 수 있는 상태가 됨 연결요청을 위해서 connect 함수를 호출하면 오류 발생 > listen 함수호출 이후에 클라이언트의 연결요청이 들어왔다면 , **들어온 순서대로 연결요청을 수락해야 한다** 수락은 클라이언트와 데이터를 주고받을 수 있는 상태가 됨을 의미 > accept 함수는 호출성공 시 내부적으로 데이터 입출력에 사용할 소켓을 생성하고 그 소켓의 파일 디스크립터를 반환 **중요한점은 자동으로 생성되어 연결요청을 한 클라이언트와 연결까지 이루어짐** 

        - 함수호출 순서 (사진)

    - TCP기반 서버, 클라이언트의 함수호출 관계
        - 이 둘의 관계는 서로 독립된 과정이 아니기 때문에 하나의 과정으로 생각
            - 전체적인 정리를 하면 서버는 소켓 생성 이후에 bind, listen 함수의 연이은 호출을 통해 대기상태에 들어가고 > 클라이언트는 connect 함수호출을 통해서 연결요청 > 클라이언트는 서버 소켓의 listen 함수호출 이후에 connect 함수호출이 가능 > 클라이언트가 connect 함수를 호출하기에 앞서 서버가 accept함수를 먼저 호출할 수 있음 ..../ 클라이언트가 connect 함수를 호출할 때까지 서버는 accept 함수가 호출된 위치에서 블로킹 상태에 놓임

        - 함수호출  관계 (사진) 

    - lterative 서버의 구현 
        - 계속해서 들어오는 클라이언트의 연결요청을 수락하기 위해서는 반복문을 삽입해서 accept함수를 반복 호출 

    - lterative 서버의 함수호출 순서 (사진) 


        - accept 함수가 호출된 다음에 입출력 함수인 read , write 함수를 호출 > close 함수를 호출하지만 accept 함수의 호출과정에서 생성된 소켓을 대상으로 하는 close 함수까지 호출되었다면 한 클라이언트에 대한 서비스가 완료된것 또 다른 클라이언트에게 서비스를 제공하기 위해서는 또 accept 함수부터 호출해야하는 번거러움이 발생 

    - server client 연결 한 내용 적어놓기 

    - lterative 에코 서버 , 에코 클라이언트
        - 서버는 한 순간에 하나의 클라이언트와 연결되어 에코 서비스를 제공한다.
        - 서버는 총 다섯 개의 클라이언트에게 순차적으로 서비스를 제공하고 종료된다.
        - 클라이언트는 프로그램 사용자로부터 문자열 데이터를 입력 받아서 서버에 전송한다.
        - 서버는 전송 받은 문자열 데이터를 클라이언트에게 재전송한다. 즉 , 에코  시킨다
        - 서버와 클라이언트간의 문자열 에코는 클라이언트가 Q를 입력할 때까지 계속한다.

    ```c
    write(sock, message, strlen(message));
    str_len=read(sock, message, BUF_SIZE-1);
    message[str_len]=0;
    printf("Message from server: %s", message);
    ``` 
    - 지금 코드에는 read, write 함수가 호출될 때마다 문자열 단위로 실제 입출력이 이루어진다.

- 윈도우 기반 에코 서버
      - 사진 첨부
      -  TCP 서버에서 listen 함수호출을 통해 연결요청 대기상태에 들어가면 클라이언트가 connect() 함수호출을 통해서 연결요청을 할 수 있다.

      - listen 함수 호출이후 클라이언트의 연결요청이 들어왔다면, 들어온 순서대로 연결요청을 수락하고 클라이언트와 데이터를 주고받을 수 있는 상태가 되는데, 데이터를 주고받기 위해서는 소켓이 필요하다.
        서버소켓은 문지기 역할을 하는 소켓이니까 클라이언트와 데이터 송수신을 위해서는 연결요청 수락과 함께 소켓을 하나 더 만들어야 한다.

## 3일차 
- UDP 기반 서버 / 클라이언트
    - UDP 소켓의 특성 : 편지를 예로 들면 알기 쉽게 할 수 있음 편지를 보내기 위해서는 편지봉투에 , 보내는 사람 , 받는 사람의 주소정보를 써 넣어야 함 마지막으로 우체통에 넣는것까지 적용하면 되는데 
    편지 특성상 보내고 나서 상대방의 수신여부를 알 수 는 없음 , 편지가 이동되는 중에는 편지가 분실될 일은 적음 , 즉 편지는 신뢰할 수 없는 전송방법 (UDP)는 신뢰할 수 없는 전송방법을 제공

       - UDP 는 TCP 보다 훨씬 간결한 구조로 설계되어 있음 , ACK 와 같은 응답 메시지를 보내는 일도 없음
       - SUE와 같이 패킷에 번호를 부여하는 일도 없음 
       - TCP 보다 훨씬 좋은 성능을 보여준다
    
    - UDP 의 역할 
        - UDP 에서는 흐름제어가 존재하지 않음 (TCP와 UCP 의 가장 큰 차이)
        - **UDP의 역할 중 가장 중요한 것은 호스트로 수신된 패킷을 PORT 정보를 참조하여 최종 목적지인 UDP 소켓에 전달하는것**

    - TCP 와의 차이 
        - TCP 소켓을 생성하고 나서 데이터를 전송하는 경우에는 , 주소 정보를 따로 추가하는 과정이 필요 없음 (TCP 소켓은 목적지에 해당하는 소켓과 연결된 상태이기 때문에)
        - UDP 소켓은 연결상태를 유지하지 않으므로 (UDP 소켓은 단순 우체통의 역할만 함) 데이터를 전송할때마다 주소정보를 별도로 추가해야 한다. 

    - UDP 를 효율적으로 사용하는 방법
        - 데이터 송수신 이전, 이후에 거치는 연결설정 및 해제과정
        - 데이터 송수신 과정에서 거치는 신뢰정보장을 위한 흐름제어

- UDP기반 서버 / 클라이언트의 구현
    - UDP에서의 서버와 클라이언트는 연결되어 있지 않음
    - UDP에서는 서버 , 클라이언트 상관없이 하나의 소켓만 있으면 가능
    - UDP 기반의 데이터 입출력 함수 
       
    - UDP 클라이언트 소켓의 주소정보 할당
        - IP와 PORT를 소켓에 할당하는 부분이 없음
        - 자동으로 connect 함수호출시 연결되는 TCP 클라이언트와 다르게 작용
        - 데이터를 전송하는 sendto 함수호출 이전에 해당 소켓에 주소정보가 할당되어 있어야함 
        - 따라서 bind 함수를 호출해서 주소정보를 할당 . (TCP UDP를 가리지 않고 할당 됨으로)

    - connected UDP 소켓 , unconnected UDP 소켓 
        - TCP 소켓에는 데이터를 전송할 목적지의 IP와 PORT 번호를 등록하는 반면 , UDP 소켓에는 데이터를 전송할 목적지의 IP와 PORT 번호를 등록하지 않는다 . 때문에 sendto 함수호출을 통한 데이터 전송과정을 나눔
            - 1단계 : UDP 소켓에 목적지의 IP와 PORT번호 등록
            - 2단계 : 데이터 전송
            - 3단계 : UDP 소켓에 등록된 목적지 정보 삭제 
                - 즉 , sendto 함수가 호출될 때마다 이러한 과정을 반복 (목적지의 주소정보가 계속해서 변경되기 때문에 하나의 UDP 소켓을 이용해서 다양한 목적지로 데이터 전송이 가능한 것)
                - 이것처럼 등록되어 있찌 않은 소켓을'unconnected소켓'이라 하고 , 반대로 목적지 정보가 등록되어 있는 소켓을 'connected 소켓' 이라고 함 
        - connected UDP 소켓 생성
         - UDP 소켓을 대상으로 connect 함수만 호출해주면 됨
         ```c
         sock=socket(PF_INET, SOCK_DGRAM, 0);
         memset(&adr, 0, sizeof(adr));
         adr.sin_family=AF_INET;  // 주소 패밀리를 설정 AF_INET: IPv4 사용
         adr.sin_addr.s_addr=  // IP 주소를 설정 Ex) inet_addr("127.0.0.1")를 사용할 수 있음
         adr.sin_port= // 포트 번호를 설정 Ex) htons(12345)와 같이 사용할 수 있음
         connect(sock, (struct sockaddr*)&adr, sizeof(adr)); // 소켓을 지정한 주소와 포트 번호로 연결
         ```
         - q뿐만 아니라 송수신의 대상이 정재졌기 때문에 sendto, recvfrom 함수가 아닌 write, read함수의 호출로도 데이터를 송수신할 수 있음 

- 소켓의 연결종료
    - 일방적인 연결종료의 문제점 
        - 완전 종료 함수 (데이터 송수신 전송 더 이상 불가능한 상황을 의미)
            - 리눅스 : close , 윈도우 : closesocket 함수

    - 소켓과 스트림(Stream)
        - 스트림이 형성된 상태 : 소켓을 통해 두 호스트가 연결되면 , 그 다음부터 상호작용 송수신이 가능한 상태가 됨
        - 물의 흐름과 같다고 보면 됨 , 물의 흐름처럼 한쪽 방향으로만 설정됨 
        - **양방향 통신을 위해서는 두 개의 스트림이 필요**

    - 우아한 종료를 위한 shutdown 함수
        - 앞에서 말한 내용의 두 개의 스트림을 한번에 끊어내는 것이 아닌 이 중 하나만의 스트림만 끊어내는것을 설명 **(일방적인 종료)는 한번에 모두가 끊어지기 때문에 거리가 멀다**
        - Half-close 함수 사용
        ```c
        #include <sys/socket.h>

        int shutdown(int sock, int howto);
        ```
        - sock : 종료할 소켓의 파일 디스크립터 전달.
        - howto : 종료방법에 대한 정보 전달.
        - 위의 함수를 호출할 때 두 번째 매개변수에 전달되는 인자에 따라서 종료의 방법이 결정됨 
            - 두 번째 매개변수에 전달 될 수 있는 인자의 종류
                - SHUT_RD : 입력 스트림 종료 / 더 이상 데이터를 수신할 수 없는 상태가 됨 (혹시나 전달되어도 허용되지 않거나 지워짐)
                - SHUT_WR : 출력 스트림 종료 / 
                - SHUT_RDWR : 입출력 스트림 종료

- 도메인
    - DNS : IP주소와 이름 사이에서 변환을 수행하는 시스템을 가리켜 'DNS(Domain Name System)' 이라고 하며 DNS 중심에는 DNS 서버가 있음
    - 도메인 이름을 이용해서 IP주소 얻어오기 
        - hostent 라는 구조체의 변수정의
            ```c
            struct hostent
            {
                char * h_name;  // official name
                char ** h_aliases; // alias list
                int h_addrtype; //gist address type
                int h_length  // address length
                char ** h_addr_list  // address list
            }
            // 도메인 이름을 IP로 변환하는 경우에는 h_addr_list만 신경쓰면 됨
            ```
            - h_name : 공식 도메인 이름 저장 해당 홈페이지를 대표하는 도메인 이름이라는 의미를 담고 있지만 실제 우리에게 잘 알려진 유명 회사의 도메인 이름이 공식 도메인 이름으로 등록되지 않은 경우도 많음
            - h_aliases : 같은 메인 페이지여도 다른 도메인 이름으로 접속할 수 있는 경우 다른 도메인 이름의 지정이 가능 정보는 h_alsiases 를 통해 얻을 수 있다
            - h_addrtype : IPv4 , IPv6 둘다 지원 h_addr_list 로 변환된 IP주소의 주소체계정보를 반환
            - h_length : 함수호출의 결과 IP주소가 담긴다 IPv4의 경우는 4바이트 IPv6 의 경우에는 16바이트
            - h_addr_list : IP주소가 **정수의 형태로 변환된다 . 접속자 수가 많은 서버는 하나의 도메인 이름에 대응하는 IP를 여러개 둬서 둘 이상의 서버로 부하를 분산** , 이 경우에도 이 멤버를 통해 모든 IP의 주소정보를 얻을 수 있다 

- 소켓의 다양한 옵션
    - getsockopt & setsockopt
        ```c
        #include <sys/socket.h>
        int getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
        // sock : 옵션확인을 위한 소켓의 파일 디스크립터 전달.
        // level : 확인할 옵션의 프로토콜 레벨 전달.
        // optname : 확인할 옵션의 이름 전달. 
        // optval : 확인결과의 저장을 위한 버퍼의 주소 값 전달.
        // optlen : 네 번째 매개변수 optval로 전달된 주소 값의 버퍼크기를 담고 있는 변수의 주소 값 전달, 함수호출이 완료되면 이 변수에는 네 번째 인자를 통해 반환된 옵션정보의 크기가 바이트 단위로 계산되어 저장된다.
        ```
        
        ```c
        #include <sys/socket.h>
        int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen);
        // sock : 옵션변경을 위한 소켓의 파일 디스크립터 전달.
        // level : 변경할 옵션의 프로토콜 레벨 전달.
        // optname : 변경할 옵션의 이름 전달.
        // optval : 변경할 옵션정보를 저장한 버퍼의 주소 값 전달 
        // optlen : 네 번째 매개변수 optval로 전달된 옵션정보의 바이트 단위 크기 전달.
        ```

- SO_SNDBUF & SO_RCVBUF 
    - SO_RCVBUF 는 입력버퍼의 크기와 관련된 옵션 , SO_SNDBUF 는 출력버퍼의 크기와 관련된 옵션 
    - 이 두 옵션을 이용해서 **버퍼의 크기를 참조 뿐 아니라 변경도 가능**
    - 소켓이 생성되면 기본적으로 입력버퍼와 출력버퍼가 생성
    - 소켓의 타입은 소켓 생성시 한번 결정되면 변경이 불가능하다!


- SO_REUSEADDR 
    - Time-wait상태는 상대적으로 중요함 
        - 클라이언트를 먼저 종료시키고 서버를 종료하면 재실행이 바로 진행되지만 , 서버를 먼저 종료하고 클라이언트를 종료시키면 재 실행 시 bind() error발생 -> 3분뒤 다시 실행 해야 함  / 빠르게 다시 시작하고 싶으면 PORT 번호를 바꿔주면 가능! **(서버는 종료되지만 Time-wait때문에 ex(10010번 PORT 가 살아있어서 기다려줘야하는것 , 기존에 사용하던 PORT를 바로 사용못하는 이유))** 

    - 주소의 재할당 
        - 네트워크나 오류가 발생하여 Time-wait상태가 발생하고 길어질 수 밖에 없는 문제의 상황이 올 수 도있음 
        - 해결방안으로 SO_REUSEADDR 의 상태를 변경하면 되는데 Time-wait 상태에 PORT 번호를 새로 시작 하는 소켓에 할당 되게 할 수 있음 
        - SO_REUSEADDR의 디폴트 값 0 은 : Time-wait 상태에 있는 소켓의 PORT 번호할당이 불가 를 나타냄
        - 이 값을 1로 변경해주면 해결이 됨

        ```c
        optlen = sizeof(option);
        option = TRUE;
        setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
        // reuseadr_eserver.c 언제든 사용가능한 상태로 만들어주는 코드
        ```

- 프로세스(실행중인 프로그램) 이해
    - 두 가지 유형의 서버
        - 대표적인 다중접속 서버의 구현 모델
            - 멀티프로세스 기반 서버 : 다수의 프로세스를 생성하는 방식으로 서비스 제공 (Linux에 적합)
            - 멀티플렉싱 기반 서버 : 입출력 대상을 묶어서 관리하는 방식으로 서비스 제공
            - 멀티쓰레딩 기반 서버 : 클라이언트의 수만큼 쓰레드를 생성하는 방식으로 서비스 제공
    - 싱글코어도 5개의 프로세스가 진행되는것 처럼 보이는 이유는 CPU가 빠르기 때문에 빠르게 돌아가면서 
        보여지는것이 동시에 보이는것 처럼 보일정도로 빠르기 때문에 (코어수가 많을수록 더 많이 느낌)

    - 프로세스 ID
        - 모든 프로세스는 생성되는 형태에 상관없이 운영체제가 ID를 지정해줌
        - 2이상의 정수 형태를 가지고있음
        - **숫자1은 운영체제가 시작되자마자 실행되는(운영체제를 돕는)프로세스에게 할당되기때문**
    
    - fork 함수호출을 통한 프로세스 생성(멀티프로세스 기반 서버의 구현에 사용)
        - 이미 실행중인 fork 함수를 호출한 (호출한 부모프로세스의 복사본을 생성)
        - 그 다음 두 프로세스는 모두 fork 함수의 호출 이후 문장을 실행함
        - **완전 동일 메모리 영역까지 동일하게 복사되기 때문에 fork 함수의 변환 값을 기준으로 나뉘도록 프로그래밍을 해야함**
        - 부모 프로세스 : fork 함수의 반환 값은 자식 프로세스의 ID를 가지게 됨
        - 자식 프로세스 : fork 함수의 반환 값은 0
        - 반환값은 부모 프로세스로 다시 감 > 호출을 부모 프로세스에서 하기 때문에 
        - fork 함수호출 (그림)
        - ```c
            #include <unistd.h>
            pid_t fork(void);
          ```
- 프로세스 & zombie 프로세스 
    - 프로세스를 완벽히 종료시키지 않고 대충만 소멸시켜둔다면 좀비프로세스가 될 가능성이 있음(중요한 리소스를 차지할 수 있음)
    - exit 함수로 전달되는 인자 값과 main 함수의 return 문에 의해 반환되는 값 모두 운영체제로 전달 > 이 값이 자식 프로세스를 생성한 부모 프로세스에게 전달될 때까지 자식 프로세스를 소멸 시키지 않는데 이 상황을 좀비 프로세스라고 한다. 
    - 해당 자식 프로세스를 생성한 부모 프로세스에게 exit 함수의 인자 값이나 return 문의 반환 값이 전달 되어야 함.
    - 전달 해주는 방식 : 부모 프로세스의 적극적인 요청이 있어야 (함수 호출) 함 
        
        - (좀비 프로세스의 생성이유)fork 함수의 호출로 생성된 자식 프로세스가 종료되는 상황 두 가지
            - 인자를 전달하면서 exit를 호출하는경우
            - main 함수에서 reutrn문을 실행하면서 값을 반환하는 경우 

## 4일차
- ZOMBIE PROCESS : wait 함수의 사용
    - 자식 프로세스의 소멸을 위해서는 부모프로세스가 자식 프로세스의 전달 값을 요청해야 함 요청방법은 2가지 있음
    - 그 중 하나는 다음 함수를 호출
    - ```c
        #include <sys/wait.h>
        pid_t wait(int * statloc);
        // 호출 되었을 때 이미 종료된 자식 프로세스가 있다면, 자식 프로세스가 종료되면서 전달한 값
        // (exit 함수의 인자 값, main 함수의 return에 의한 반환 값) 매개변수로 전달          
        ```
        - WIFEXITEM : 자식 프로세스가 정상 종료한 경우 '참(true)'을 반환
        - WEXITSTATUS : 자식 프로세스의 전달 값을 반환
    - wait 함수의 인자로 변수 status의 주소 값이 전달되었다면 , wait 함수의 호출 이후에는 
    -  ```c
        if(WIFEXITED(status))  //정상 종료하였는가?
        {
        puts("Normal termination!");
        printf("Child pass num: %d", WEXITSTATUS(status)); // 
        }
       ```
- 시그널 핸들링
    - 함수이름 : signal
    - 매개변수 선언 : int signo , void(*func)(int)
    - 반환형 : 매개변수형이 int 이고 반환형이 void 인 함수포인터
        - 자식 프로세스가 언제 종료될지 모르고 wiatpid함수를 계속 호출하고 있을 수 없기때문에 사용
        - 운영쳊는 자식프로세스의 전달값을 전달 받고 자식프로세스가 종료되었는지 인식할 수 있기 때문에 
        - 부모프로세스가 자식프로세스의 종료여부를 계속해서 확인할 수 없어서
    
    - signal 함수를 통해서 등록 가능한 특정 상황과 그 상황에 할당된 상수
        - signal(SIGCHLD,mychild);  = 자식 프로세스가 종료되면 mychild 함수를 호출해 달라
        - signal(SIGALRM, timeout); = alarm 함수 호출을 통해서 등록된 시간이 지나면 timeout 함수를 호출하라
        - signal(SIGINT, keycontrol); = CTRL+C 가 입력되면 keycontrol 함수를 호출해 달라
    
    - sigaction 함수를 이용한 시그널 핸들링 
        - signal 함수와 유사 , signal 함수를 대체할 수 있고 , 보다 더 안정적으로 작동함 
        - signal 함수는 유닉스 계열의 운영체제 별로 동작방식에 있어서 약간의 차이를 보일 수 있지만,
         sigaction 함수는 차이를 보이지 않음.
        - 실제로 요즘은 signal 함수를 사용해서 프로그램을 작성하지 않음 , 과거 프로그램과의 호환성을 위해서 유지되고 있을뿐
    - ```c
      #include <signal.h>
      int sigaction(int signo, const struct sigaction * act, struct sigaction *oldact);
      // signo : signal 함수와 마찬가지로 시그널의 정보를 인자로 전달
      // act : 첫 번째 인자로 전달된 상수에 해당하는 시그널 발생시 호출될 함수 (시그널 핸들러) 의 정보전달.
      // oldact : 이전에 등록되었던 시그널 핸들러의 함수 포인터를 얻는데 사용되는 인자, 필요없다면 0전달
      ```
    - 위 함수의 호출을 위해서는 sigaction 이라는 이름의 구조체 변수를 선언 및 초기화 해야함
    ```c
    struct sigaction
    {
        void(*sa_handler)(int);
        sigset_t sa_mask;
        int sa_flags;
    }
    // sa_handler 에 시그널 핸들러의 함수 포인터 값(주소 값) 을 저장하면 됨
    // 그리고 sa_mask는 모든 비트를 0으로 초기화 함. 이 두 멤버는 시그널 관련 옵션 및 특성의 지정에 사용
    ``` 
- 시그널 핸들링을 통한 좀비 프로세스의 소멸
    - 좀비 프로세스가 생성되지 않도록 함
    - 자식 프로세스가 종료된 상황에서 시그널 이름이 SIGCHLD 라는 사실만을 알면 됨

- 멀티태스킹 기반의 다중접속 기반
    - 프로세스 기반의 다중접속 서버의 구현 모델
        - 연결이 하나 생성될 때마다 프로세스를 생성해서 해당 클라이언트에 대해 서비스를 제공하는 것
            - 1단계: 에코 서버(부모 프로세스)는 accept 함수 호출을 통해서 연결요청을 수락한다.
            - 2단계: 이때 얻게 되는 소켓의 파일 디스크립터를 자식 프로세스를 생성해서 넘겨준다.
            - 3단계: 자식 프로세스는 전달받은 파일 디스크립터를 바탕으로 서비스를 제공한다.

    - fork 함수호출을 통한 파일 디스크립터의 복사 
        - 소켓이 복사되면 동일한 PORT에 할당된 소켓이 둘 이상이 됨
        - 두개의 파일디스크립터가 존재하는 경우 , 파일 디스크립터가 모두 종료(소멸) 되어야 소켓은 소멸됨
        - 서로에게 상관이 없는 소켓의 파일 디스크립터를 닫아줘야함

- TCP의 입출력 루틴(Routine) 분할
    - 입출력 루틴 분할의 의미와 이점
        - 클라이언트의 부모 프로세스는 데이터의 수신을 담당
        - 별도로 생성된 자식 프로세스는 데이터의 송신을 담당
        **이렇게 구현해놓으면 입력과 출력을 담당하는 프로세스가 각각 다르기 때문에 서버로부터의 데이터 수신여부에 상관없이 데이터를 전송할 수 있음**
        - 가장 중요한 이유는 프로그램의 구현이 수월해짐
        - 프로세스 생성 이후에 부모 프로세스가 실행하는 영역은 데이터의 수신과 관련해서만 코드를 작성하면 되고 , 
        - 자식 프로세스가 실행하는 영역은 데이터의 수신과 관련해서만 코드를 작성하면 됨

    - 에코 클라이언트의 입출력 루틴 분할
        - 지금까지 구현한 에코 서버와 에코 클라이언트 방식은
            - 서버로 데이터를 전송 > 그리고 데이터가 돌아올때까지 기다린다 (무조건) > 그리고 에코되어 돌아온 데이터를 수신하고 나서야 비로소 데이터를 추가로 전송할 수 있음
                - 즉 한번 데이터를 전송하면 에코되어 돌아오는 데이터를 수신할때까지 무조건 기다려야하는 단점이 있음(프로그램 코드의 흐름이 read와 write함수를 반복하는구조였기 떄문)
                - 위에서 정리한 내용인
                    - 클라이언트의 부모 프로세스는 데이터의 수신을 담당
                    - 별도로 생성된 자식 프로세스는 데이터의 송신을 담당
                        - 서버로부터 데이터 수신여부에 상관없이 데이터를 전송할 수 있음

- 프로세스간 통신의 기본 
    - 파이프 
        - 파이프는 프로세스에 속하는 자원이 아님 x ,
        - 소켓과 마찬가지로 운영체제에 속하는 자원 (때문에 fork 함수의 호출에 의한 복사 대상이 아님)
        - 운영체제가 마련해 주는 메모리 공간을 통해서 두 프로세는 통신을 하게 됨 
        - ```c
          #include <unistd.h>
          int pipe(int filedes[2]);
          // filedes[0] : 파이프로부터 데이터를 수신하는데 사용되는 파일 디스크립터가 저장된다 . 즉 , filedes[0]는 파이프의 출구가 된다.
          // ifledes[1] : 파이프로 데이터를 전송하는데 사용되는 파일 디스크립터가 저장된다 . 즉 , filedes[1] 은 파이프의 입구가 된다
          ```
        - 길이가 2인 int형 배열의 주소 값을 인자로 전달하면서 위의 함수를 호출하면 배열에는 두 개의 파일 디스크립터가 담긴다. 
        - 각각은 파이프의 출구와 입구로 사용됨 
            - 결론
                - 부모 프로세스가 위의 함수를 호출하면 파이프가 생성되고 , 파이프의 입구 및 출구에 해당 하는 파일 디스크립터를 동시에 얻게됨

        - 파이프의 기본원리 
            - 부모, 자식 프로세스 모두 파이프의 입출력 경로에 접근이 가능하지만 , 자식은 입력 경로에만 , 부모는 출력 경로에만 접근해서 통신을 함
        
    - 파이프 기반의 프로세스간 양방향 통신
        - 하나의 파이프만 가지고 양방향으로 데이터를 송신수하는 것은 쉬운일이 아니기 때문에 (두 개의 파이프를 사용)

    - 메시지를 저장하는 형태의 에코 서버 
        - 서버는 클라이언트가 전송하는 문자열을 전달되는 순서대로 파일에 저장

- IO 멀티플렉싱기반 서버
    - 멀티프로세스 서버
        - 하나의 통신채널을 통해서 둘 이상의 데이터(시그널)를 전송하는데 사용되는 기술 
        - 물리적 장치의 효율성을 높이기 위해서 최소한의 물리적인 요소만 사용해서 최대한의 데이터를 전달하기 위해 사용되는 기술 
        - 간단하게 두 개의 클라이언트를 위해서 두 개의 프로세스, 두 개의 스레드를 두는 것이 아니라 하나의 서버에서 두 클라이언트를 모두 처리하는 것 
    - 시그널 
        - 서버는 항상 대기를 하고 있고, 클라이언트로부터 뭔가 신호가 오면 해당 파일 디스크립터를 받아 처리해주고 다시 대기상태로 들어가는 시그널 방식을 통해 가능하게 함

- select 함수의 이해와 서버의 구현
    - select 함수의 기능과 호출순서 
        - select 함수를 사용하면 한곳에 여러 개의 파일 디스크립터를 모아놓고 동시에 관찰 할 수 있음 
            - 관찰 할 수 있는 목록
                - 수신한 데이터를 지니고 있는 소켓이 존재하는가?
                - 블로킹되지 않고 데이터의 전송이 가능한 소켓은 무엇인가?
                - 예외상황이 발생한 소켓은 무엇인가?

    - 파일 디스크립터의 설정 
        - select 함수를 사용하여 관찰하기 전에 파일 디스크립터를 모아야 한다 
        - 모을 때도 관찰항목 (수신 , 전송 , 예외) 에 따라서 구분해서 모아야 함 
        - 사용되는 변수 fd_set형 ( 매번 지정하는것이 아닌 매크로 함수를 통해서 ) 
            - FD_ZERO(fd_set * fdset)  : 인잘 전달된 주소의 fd_set형 변수의 모든 비트를 0으로 초기화
            - FD_SET(int fd_set *fdset) : 매개변수 fdset으로 전달된 주소의 주소의 변수에 매개변수 fd로 전달된 파일 디스크립터 정보를 등록
            - FD_CLR(int fd, fd_ser *fdset) : 매개변수 fdset으로 전달된 주소의 변수에서 매개변수 fd로 전달된 파일 디스크립터 정보를 삭제 
            - FD_ISSET(int fd, fd_set *fdset) : 매개변수 fdset으로 전달된 주소의 변수에 매개변수 fd로 전달된 파일 디스크립터 정보가 있으면 양수를 반환한다. **(select 함수의 호출결과를 확인하는 용도로 사용됨)**

        - 검사(관찰)의 범위지정 및 타임아웃 설정
            ```c
            #include <sys/select.h>  
            #include <sys/time.h>

            int select(int maxfd, fdset *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);
            //maxfd : 검사 대상이 되는 파일 디스크립터의 수 
            //readset : fd_set형 변수에 '수신된 데이터의 존재여부' 에 관심 있는 파일 디스크립터 정보를 모두 등록해서 그 변수의 주소 값을 전달
            //writeset : fd_set형 변수에 '블로킹 없는 데이터 전송의 가능여부' 에 관심 있는 파일 디스크립터 정보를 모두 등록해서 그 변수의 주소 값을 전달
            //exceptest : fd_set형 변수에 '예외상황의 발생여부' 에 관심이 있는 파일 디스크립터 정보를 모두 등록해서 그 변수의 주소 값을 전달
            //timeout : 오류발생시에는 -1이 반환 , 타임 아웃에 의한 반환 시에는 0이 반환 , 관심대상으로 등록된 파일 디스크립터에 해당 관심에 관련된 변화가 발생하면 0보다 큰 값이 반환, 이값은 변화가 발생한 파일 디스크립터의 수를 의미 
            ```
            - 파일디스크립터의 범위는 매개변수와 관련이있음
                - 파일 디스크립터의 값은 생성될때마다 1씩 증가 
                - 가장 큰 파일 디스크립터의 값에 1을 더해서 인자로 전달(1을 더하는 이유는 파일 디스크립터의 값이 0부터 시작하기 때문)
                - select 함수의 마지막 매개변수와 관련이 있음 timeval은 구조체 기반의 자료형
                    - 정의내용
                        - ```c
                          struct timeval
                          {
                            long tv_sec; // seconds
                            long tv_usec; // microseconds
                          }
                            // 변화가 생기지 않으면 무한정 블로킹 상태에 머물게 된다. (방지하기 위해서 타임아웃을 지정)
                            // tv_sec : 초단위 정보 , tv_usec : 마이크로 초 단위 정보 이 변수의 주소값에 select함수의 마지막 인자를 전달 
                            // 파일디스크립터에 변화가 발생하지 않아도 지정된 시간이 지나면 함수가 반환을 함 
                            // 이렇게 해서 반환이 되는 경우 , select 함수는 0을 반환!! 
                            // 타임아웃을 설정하고 싶지않을 경우에는 NULL을 인자로 전달.
                          ```

        

     - select 함수호출 이후의 결과확인  // 보류
            
        
## 5일차
- send & recv 입출력 함수
    ```c
    ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
        // 성공 시 전송된 바이트 수, 실패 시 -1 반환
        // sockfd : 데이터 전송 대상과의 연결을 의미하는 소켓의 파일 디스크립터 전달
        // buf : 전송할 데이터를 저장하고 있는 버퍼의 주소 값 전달
        // nbytes : 전송할 바이트 수 전달
        // flags : 데이터 전송 시 적용할 다양한 옵션 정보 전달
    ```

    ```c
    ssize_t recv(int sockfd, const void *buf, size_t nbytes, int flags);
        // 성공 시 수신한 바이트 수(단, EOF 전송 시 0), 실패 시 -1 반환
        // sockfd : 데이터 수신 대상과의 연결을 의미하는 소켓의 파일 디스크립터 전달
        // buf : 수신된 데이터를 저장할 버퍼의 주소 값 전달
        // nbytes : 수신할 수 있는 최대 바이트 수 전달
        // flags : 데이터 수신 시 적용할 다양한 옵션 정보 전달
    ```

    - send & recv 함수 옵션 
        1. MSG_OOB(Out-of-band) :긴급 메시지 전송
        - 긴급으로 전송해야 할 메시지가 있어 메시지의 전송방법 및 경로를 달리하고자 할 때 사용!
        - Out-of-band data : 전혀 다른 통신 경로로 전송되는 데이터
        - 진정한 의미의 Out-of-band 형태로 데이터가 전송되려면 별도의 통신경로가 확보되어 고속으로 전송되어야 하지만
        - TCP는 별도의 통신 경로를 제공하지 않는다.
        - 다만 TCP에 존재하는 Urgent mode를 이용해 데이터를 전송해줄 뿐!

        - Urgent mode
            - MSG_OOB 옵션 => 데이터 수신하는 대상에게 *데이터의 처리를 독촉! 전송순서가 그대로 유지되는 TCP의 전송특성은 그대로 유지됨*
            ```c
            send(sock, "890", strlen("890"), MSG_OOB);
            // 버퍼의 가장 왼쪽 위치를 offset 0이고 8저장, 문자 0은 offset 2의 위치에 저장됨
            // 문자 0의 오른편인 offset 3가 Urgent Pointer로 지정!
            ```
            - Urgent Pointer는 긴급 메시지의 다음 번 위치를 가리키면서 상대 호스트에게 Urgent Pointer가 가리키는 오프셋 바로 앞에 존재하는 것이 긴급 메시지임을 알림
            - 즉, 긴급 메시지 정보는 실제로 하나의 바이트에만 표시됨!
            - **MSG_OSB 옵션이 지정되면, 패킷 자체가 긴급 패킷이 되고, Urgent Pointer를 통해 긴급 메시지 위치도 표시됨**
        
        2. MSG_PEEK : 입력버퍼에 수신된 데이터가 존재하는 지 확인
            - MSG_PEEK 옵션을 주고 recv 함수 호출 시 **입력버퍼에 존재하는 데이터가 읽혀지더라도 입력버퍼에서 데이터가 지워지지 않음**
            - 따라서 MSG_DONWAIT 옵션과 묶여, 블로킹 되지 않는 데이터의 존재유무를 확인하기 위한 함수의 호출 구성에 사용

- readv & writev 입출력 함수
    - 데이터 송수신의 효율성 향상에 도움
    - 데이터를 모아서 전송하고, 모아서 수신하는 기능의 함수
    - writev : 여러 버퍼에 나뉘어 저장되어 있는 데이터를 한 번에 전송 가능
        ```c
        ssize_t writev(int filedes, const struct iovec* iov, int iovcnt);
            // 성공 시 전송된 바이트 수, 실패 시 -1 리턴
            // filedes : 데이터 전송의 목적지를 나타내는 소켓의 파일 디스크립터 전달.
            //         : 단, 소켓에만 제한된 함수가 아니므로 read 함수처럼 파일이나 콘솔 대상의 파일 디스크립터도 전달 가능
            // iov : 구조체 iovec 배열의 주소 값 전달, 구조체 iovec 변수에는 전송할 데이터의 위치 및 크기 정보 담음
            // iovcnt : 두 번째 인자로 전달된 주소 값이 가리키는 배열의 길이 정보 전달

        struct iovec
        {
            void* iov_base;     // 버퍼의 주소 정보
            size_t iov_len;     // 버퍼의 크기 정보
        }
        ```
    - readv : 데이터를 여러 버퍼에 나눠서 수신 가능
        ```c
        ssize_t readv(int filedes, const struct iovec* iov, int iovcnt);
            // 성공 시 수신된 바이트 수, 실패 시 -1 리턴
            // filedes : 데이터를 수신할 파일(혹은 소켓)의 파일 디스크립터 전달.
            // iov : 데이터를 저장할 위치 및 크기 정보 담고 있는 iovec 구조체 배열의 주소 값 전달
            // iovcnt : 두 번째 인자로 전달된 주소 값이 가리키는 배열의 길이 정보 전달
        ```
    - 전송해야 할 데이터가 여러 개의 버퍼(배열)에 나뉘어 있는 경우 여러 번의 write 함수 호출 대신 딱 한번의 writev 함수 호출
    - 입력버퍼에 수신된 데이터를 여러 저장소에 나눠서 읽어 들이고 싶은 경우 여러 번의 read 함수 호출 대신 딱 한번의 readv 함수 호출
    - 호출횟수가 적으면 성능이 향상되고, 전송되는 패킷의 수 또한 줄일 수 있다!

- 표준 입출력 함수 장점
    - 이식성(Portability) 좋음
        - 모든 표준 함수들은 이식성이 좋음 - 모든 OS(컴파일러)가 지원하도록 ANSI C에서 표준으로 정의했기 때문
    - **버퍼링**을 통한 성능 향상에 도움됨

- 소켓 생성 시 OS는 입출력을 위한 버퍼 생성, 해당 버퍼는 TCP 프로토콜을 진행하는 데 매우 중요한 역할!
- 이와는 별도로 표준 입출력 함수 사용 시 추가로 하나의 버퍼를 제공 받음!!
- 표준 입출력 함수를 사용한 데이터 전송의 경우, 거쳐야 하는 버퍼의 수는 2개가 되는 것
    - fputs 함수를 통해 "Hello" 문자열 전송할 경우,
    1. 표준 입출력 함수의 버퍼에 데이터 전달
    2. 소켓의 출력버퍼로 이동
    3. 상대방에게 문자열 전송됨

- 소켓 관련 버퍼
    - 버퍼는 기본적으로 성능 향상을 목적으로 함
    - **소켓과 관련**하여 제공되는 버퍼는 **TCP 구현을 위한 목적**이 더 강함
        - TCP의 경우 데이터 분실 시 재전송 진행!
        - 재전송을 위한 데이터 저장을 소켓의 출력버퍼에 저장
    
- 표준 입출력 함수 관련 버퍼    
    - **표준 입출력 함수 사용 시 제공되는 버퍼**는 **오로지 성능 향상만을 목적**으로 제공됨
    - 버퍼링
        - *전송하는 데이터의 양, 출력버퍼로의 데이터 이동 횟수의 관점에서의 성능이 우월함*
        - 1바이트 데이터를 총 10번에 걸쳐(10개의 패킷에) 보내는 경우 vs 버퍼링해서 10바이트로 묶어 한번에 전송하는 경우
            - 데이터 전송을 위해 구성된 패킷에는 헤더정보가 추가됨, 이는 데이터의 크기에 상관없이 일정한 크기 구조를 가지므로
            - 헤더 크기를 약 40바이트로 잡았을 때, 전송해야 할 데이터의 양의 차이를 보자!
            - 1바이트 10회 -> 40 X 10 = 400 바이트
            - 10바이트 1회 -> 40 X 1 = 40 바이트
            - 또한 데이터의 전송을 위해 소켓의 출력버퍼로 데이터를 이동시키는 데에도 시간 소모가 제법 된다
            - 1바이트 10회 이동시키는 시간 >= 10바이트 1회 이동시키는 시간 X 10

- 표준 입출력 함수 단점
    - 양방향 통신 어렵
    - 상황에 따라 fflush 함수의 호출이 빈번히 등장할 수 있음
        - fflush 함수는 출력 버퍼를 비우는 함수!
        - 버퍼링 문제로 인해 읽기 -> 쓰기, 쓰기 -> 읽기로 작업의 형태를 바꿀 때마다 fflush 함수를 호출해야함 => 표준 입출력 함수의 장점인 버퍼링 기반의 성능향상에도 영향을 미침
    - 파일 디스크립터를 FILE 구조체의 포인터로 변환해야 함
         - 소켓 생성시에는 파일 디스크립터가 반환되는데, 표준 입출력 함수의 사용을 위해선 파일 디스크립터를 FILE 구조체의 포인터로 변환하는 과정을 거쳐야 함

- fdopen 함수를 이용한 FILE 구조체 포인터로의 변환
    ```c
    FILE *fdopen(int fildes, const char* mode);
        // 성공 시 변환된 FILE 구조체 포인터, 실패 시 NULL 반환
        // fildes : 변환될 파일 디스크립터
        // mode : 생성할 FILE 구조체 포인터의 모드 정보 전달
    ```

    - 두 번의 fdopen 함수 호출로 읽기모드의 FILE 포인터, 쓰기모드의 FILE 포인터 생성 => 입력버퍼와 출력버퍼를 구분함(=스트림의 분리)으로 인한 버퍼링 기능의 향상!

- fileno 함수를 이용한 파일 디스크립터로의 변환
    ```c
    int fileno(FILE *stream);
        // 성공 시 변환된 파일 디스크립터, 실패 시 -1 반환
        // 인자로 FILE 포인터 전달하면 해당 파일의 파일 디스크립터 반환!
    ```

- 파일 디스크립터의 복사와 Half-close
    - 읽기모드 FILE 포인터와 쓰기모드 FILE 포인터는 **하나의 파일 디스크립터를 기반으로 생성**
    - 따라서, 어떠한 FILE 포인터를 대상으로 fclose 함수를 호출하더라도
    - **파일 디스크립터가 종료**되고, 이는 **소켓의 완전종료(데이터 송수신 불가능)**로 이어짐
    - 해결방법 > 파일 디스크립터 복사 후 각각의 파일 디스크립터를 통해 FILE 포인터 생성! => Half-close 위한 환경 마련됨
    - 단, **모든 파일 디스크립터가 소멸되어야 소켓도 소멸된다는 사실**을 잊지말기!
        - 쓰기모드 FILE 포인터를 대상으로 fclose 함수를 호출해도 읽기모드 fILE 포인터를 생성하는데 사용한 파일 디스크립터가 남아있으므로 소켓은 소멸하지 않음
        - 그리고 **파일 디스크립터는 입력 및 출력 모두 가능...!**
        - 따라서 상대 호스트로 EOF가 전송되지 않고, 파일 디스크립터를 이용하면 여전히 출력도 가능한 상태..

    - 파일 디스크립터의 복사에 사용되는 dup & dup2 함수
        ```c
        int dup(int fildes);
        int dup2(int fildes, int fildes2);
            // 성공 시 복사된 파일 디스크립터, 실패 시 -1 반환
            // fildes : 복사할 파일 디스크립터 전달
            // fildes2 : 명시적으로 지정할 파일 디스크립터의 정수 값 전달
        ```
        - dup2 함수는 복사된 파일 디스크립터의 정수 값을 명시적으로 지정할 때 사용!

    - 복사된 파일 디스크립터의 수에 상관없이 **EOF의 전송을 동반하는 Half-close를 진행**하기 위해서는 **shutdown 함수를 호출**해야 한다.
    - shutdown 함수가 호출되면 복사된 파일 디스크립터의 수에 상관없이 Half-close 진행되고, 이 과정에서 EOF도 전달됨!!

        ```c
            // day05/sep_serv2.c
            ...
            // fileno 함수호출 시 반환되는 파일 디스크립터를 대상으로 shutdown 함수 호출
            // Half-close 진행되어 클라이언트로 EOF 전달됨
            shutdown(fileno(writefp), SHUT_WR);
            ...

            // day05/sep_clnt.c
            ...
            // 서버로부터 EOF수신 후, 서버로 문자열 FROM CLIENT : Thank you! 전송
            fputs("FROM CLIENT : Thank you! \n", writefp);
            ...
        ```

## Day06
<details>
<summary>내용</summary>
- 멀티프로세스 : fork()
- 멀티플렉싱 : select()
- 멀티스레드

- select 기반의 IO 멀티플렉싱이 느린 이유
    - select 함수 호출 후, 모든 파일 디스크립터를 대상으로 하는 반복문
    - select 함수 호출할 때마다 관찰대상에 대한 정보를 매번 운영체제에게 전달

- select() 는 파일 디스크립터, 정확히 말하면 소켓의 변화를 관찰하는 함수
- 소켓은 OS에 의해 관리되므로 select()는 절대적으로 운영체제에 의해 기능의 완성되는 함수!

- epoll : select() 단점 극복!
    - 상태 변화의 확인을 위한 전체 파일 디스크립터 대상으로 하는 반복문 필요X
    - select 함수에 대응하는 epoll_wait 함수 호출 시, 관찰 대상의 정보를 매번 전달할 필요X
    1. epoll_create : epoll 파일 디스크립터 저장소 생성
    2. epoll_ctl : 저장소에 파일 디스크립터 등록 및 삭제
    3. epoll_wait : select 함수와 마찬가지로 파일 디스크립터의 변화를 대기

    - select 방식 - 관찰대상인 파일 디스크립터의 저장을 위해 fd_set형 변수 선언
    - epoll 방식 - 관찰대상인 파일 디스크립터의 저장을 운영체제가 담당, 저장소의 생성을 OS에게 요청할 때 epoll_create 사용

    - 리눅스 커널 버전 (epoll 적용을 위해서는 2.5.44 이상)
        ```shell
        > uname -r
        > cat /proc/sys/kernel/osrelease
        ```
    
    - epoll_create() 호출 시 생성되는 파일 디스크립터의 저장소는 *epoll 인스턴스*
        ```c
        int epoll_create(int size);
            // 성공 시 epoll 파일 디스크립터, 실패 시 -1 반환
            // 반환되는 파일 디스크립터는 epoll 인스턴스 구분 목적으로 사용됨
            // 소멸 시에는 다른 파일 디스크립터들과 마찬가지로 close 함수 호출을 통한 종료의 과정 거쳐야함
            // size : epoll 인스턴스의 크기 정보(그냥 epoll 인스턴스의 크기를 결정하는 데 있어 참고용)
        ```

    - epoll_ctl() : epoll 인스턴스 생성 후 epoll 인스턴스(파일 디스크립터 저장소)에 관찰대상이 되는 파일 디스크립터 등록 시 사용
        ```c
        int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
            // 성공 시 0, 실패 시 -1 반환
            // epfd : 관찰대상을 등록할 epoll 인스턴스의 파일 디스크립터
            // op : 관찰대상의 추가, 삭제, 변경여부 지정
            // fd : 등록할 관찰 대상의 파일 디스크립터
            // event : 관찰대상의 관찰 이벤트 유형
            //       : 구조체 epoll_event의 포인터 => 이벤트가 발생한 파일 디스크립터를 묶는 용도, 이벤트 유형 등록 용도

        // 구조체 epoll_event 기반으로 상태변화가 발생(이벤트 발생)한 파일 디스크립터가 별도로 묶인다!
        struct epoll_event
        {
            __uint32_t events;
            epoll_data_t data;
        }

        typedef union epoll_data
        {
            void *ptr;
            int fd;
            __uint32_t u32;
            __uint64_t u64;
        } epoll_data_t;
        ```
        
        - epoll_ctl(A, EPOLL_CTL_ADD, B, C); - epoll 인스턴스 A에 파일 디스크립터 B를 등록하되, C를 통해 전달된 이벤트의 관찰을 목적으로 등록을 
        - epoll_ctl(A, EPOLL_CTL_DEL, B, NULL); - epoll 인스턴스 A에서 파일 디스크립터 B 삭제(삭제할 땐 관찰유형 불필요하니까 NULL 전달)

        - 구조체 epoll_event
            - 이벤트가 발생한 파일 디스크립터를 묶는 용도로 사용!
            - 파일 디스크립터를 epoll 인스턴스에 등록할 때, 이벤트의 유형을 등록하는 용도로도 사용

            ```c
            struct epoll_event event;
            ...
            // epoll 인스턴스인 epfd에 sockfd를 등록하되, 수신할 데이터가 존재하는 상황에서 이벤트가 발생하도록 등록!
            event.events = EPOLLIN;     // 수신된 데이터가 존재하는 상황(이벤트) 발생 시
            event.data.fd = sockkd;
            epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
            ```

    - epoll_wait() : select 함수와 마찬가지로 파일 디스크립터의 변화를 대기
        ```c
        int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
            // 성공 시 이벤트가 발생한 파일 디스크립터의 수, 실패 시 -1 반환
            // epfd : 이벤트 발생의 관찰영역인 epoll 인스턴스의 파일 디스크립터
            // events : 이벤트가 발생한 파일 디스크립터가 채워질 버퍼의 주소 값
            //         => 동적으로 할당 후 인자로 전달!
            // maxevents : 두 번째 인자로 전달된 주소 값의 버퍼에 등록 가능한 최대 이벤트 수
            // timeout : 1/1000초 단위의 대기시간, -1 전달 시 이벤트가 발생할 때까지 무한대기
        ```

- 레벨 트리거(Level Trigger)
    - 입력버퍼에 데이터가 남아있는 동안 계속해서 이벤트 발생

- 엣지 트리거(Edge Trigger)
    - 입력버퍼로 데이터가 수신된 상황에서 딱! 한번만 이벤트 등록 -> 입력 관련 이벤트 발생 시 입력버퍼에 저장된 데이터 전부를 읽어들여야 함!
    - 데이터의 수신과 데이터가 처리되는 시점 분리 가능!
        - 입력버퍼에 데이터가 수신된 상황(이벤트가 등록된 상황)임에도 불구하고,
        - 이를 읽어들이고 처리하는 시점을 서버가 결정할 수 있도록 하는 것은 서버 구현에 엄청난 유연성을 제공함

- 엣지 트리거 기반 서버 구현 시
    1. 변수 errno를 이용한 오류 원인 확인
        - 변수 접근 위해 <errno.h> 포함
        - **read 함수**는 입력 버퍼가 비어 더 이상 읽어들일 데이터가 없을 때 **-1 리턴**, 이 때 errno에 상수 **EAGAIN** 저장
    2. Non-blocking IO 를 위한 소켓 특성 변경
        - 엣지 트리거 방식에서 blocking 방식으로 read&write 함수 호출 시 서버를 오랜 시간 멈추는 상황이 발생할 수 있기 때문에 
        - Non-blocking 소켓을 기반으로 read&write 함수를 호출해야 함
        ```c
        int fcntl(int fildes, int cmd, ...);
            // 성공 시 매개변수 cmd에 따른 값, 실패 시 -1 리턴
            // fildes : 특성 변경의 대상이 되는 파일의 파일 디스크립터 전달
            // cmd : 함수호출의 목적에 해당하는 정보 전달
        ```
        - 두 번째 인자로 F_GETFL 전달하면 첫 번째 인자로 전달된 파일 디스크립터에 설정되어 있는 특성정보 int형으로 얻을 수 있음
        - 파일(소켓) Non-blocking 모드로 변경하기
            ```c
            int flag = fcntl(fd, F_GETFL, 0);
            fcntl(fd, F_SETFL, flag|O_NONBLOCK);
            ``` 

- 쓰레드
    - 하나의 프로세스 안에 여러 개의 쓰레드 생성
    - 멀티 프로세스의 단점(컨텍스트 스위칭 등)을 최소화하기 위해 설계된 경량화된 프로세스
    - 프로세스 : 운영체제 관점에서 별도의 실행흐름을 구성하는 단위
    - 쓰레드 : 프로세스 관점에서 별도의 실행흐름을 구성하는 단위
 
 - 쓰레드 vs 프로세스
    - 프로세스의 메모리 구조
        1. 데이터 영역 : 전역변수 할당
        2. 힙 영역 : malloc 함수 등에 의한 동적 할당
        3. 스택 영역 : 함수의 실행에 사용
    - 쓰레드는 스택 영역만 분리시키고 데이터 영역과 힙 영역을 공유하도록 설계
    - 프로세스 : 하나의 OS 안에서 둘 이상의 실행흐름을 형성하기 위한 도구
    - 쓰레드 : 프로세스 내에서 생성 및 실행되는 구조
    
    - pthread_create 함수
        - 쓰레드는 별도의 실행흐름을 가짐!
        - 따라서 쓰레드만의 main 함수를 별도로 정의해야 함!!
        - 이 함수를 시작으로 별도의 실행흐름을 형성해 줄 것을 OS에게 요청해야 하는데, 이를 목적으로 해당 함수를 호출
        ```c
        int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void*(*start_routine)(void*), void *restrict arg)
            // 성공 시 0, 실패 시 0 이외의 값 반환
            // thread : 생성할 쓰레드의 ID 저장을 위한 변수의 주소 값 전달
            // 참고로 쓰레드는 프로세스와 마찬가지로 쓰레드의 구분을 위한 ID 부여됨!
            // attr : 쓰레드에 부여할 특성 정보의 전달을 위한 매개변수, NULL 전달 시 기본적인 특성의 쓰레드 생성됨
            // start_routine : 쓰레드의 main 함수 역할을 하는, 별도 실행흐름의 시작이 되는 함수의 주소값(함수 포인터) 전달
            // arg : 세 번째 인자를 통해 등록된 함수가 호출될 때 전달할 인자의 정보를 담고있는 변수의 주소 값 전달
        ```

    - pthread_join 함수
        - 첫 번째 인자로 전달되는 ID의 쓰레드가 종료될 때까지 이 함수를 호출한 프로세스(혹은 쓰레드)를 대기상태에 둠
        - 쓰레드의 main 함수가 반환하는 값 얻을 수 있음
        ```c
        int pthread_join(pthread_t thread, void **status);
            // 성공 시 0, 실패 시 0 이외의 값 밙환
            // thread : 이 매개변수에 전달되는 ID의 쓰레드가 종료될 때까지 함수는 반환하지 않음
            // status : 쓰레드의 main 함수가 반환하는 값이 저장될 포인터 변수의 주소 값 전달
        ```

- 임계영역(Critical Section) 
    - 함수 내에 둘 이상의 쓰레드가 동시에 실행하면 문제를 일으키는 하나 이상의 문장으로 묶여있는 코드 블록

- 워커(Worker) 쓰레드 모델 - 둘 이상의 쓰레드를 생성, 각 쓰레드는 일꾼(Worker)의 형태

- 동기화(Synchronization)
    - 한 쓰레드가 전역변수에 접근하여 연산을 완료할 때까지, 다른 쓰레드가 해당 전역변수에 접근하지 못하도록 막는 것
    1. 동일한 메모리 영역으로의 동시 접근이 발생하는 상황
    2. 동일한 메모리 영역에 접근하는 쓰레드의 실행순서를 지정해야 하는 상황

    - Mutex(Mutual Exclusion) : 쓰레드의 동시 접근을 허용하지 않음
        - 임계영역(화장실)에 들어갈 때 문을 잠그고, 임계영역에서 나갈 때 문을 여는 자물쇠 시스템 
        ```c
        // 뮤텍스라는 자물쇠 시스템 생성 및 소멸
        int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
        int pthread_mutex_destroy(pthread_mutex_t *mutex);

        // 임계영역에 설치된 자물쇠 잠그고 풀 때
        int pthread_mutex_lock(pthread_mutex_t *mutex);
        // 임계영역의 시작
        // ...
        // 임계영역의 끝
        int pthread_mutex_unlock(pthread_mutex_t *mutex);
        ```
        - Dead-lock(데드락)
            - 임계영역을 빠져나가려는 쓰레드가 pthread_mutex_unlock() 를 호출하지 않아 
            - pthread_mutex_lock 함수가 블로킹 상태에서 빠져나가지 못하는 상황

    - Semaphore : 뮤텍스와 유사, 0과 1만을 사용하는 바이너리 세마포어를 대상으로 *쓰레드의 실행순서 컨트롤* 중심의 동기화
        ```c
        // sem : 세마포어의 참조 값 저장하고 있는 변수의 주소 값 전달
        int sem_init(sem_t *sem, int pshared, int value);   // 세마포어 생성
        int sem_destroy(sem_t *sem);                        // 세마포어 소멸
        // sem_post에 전달되면 세마포어의 값은 하나 증가
        // sem_wait에 전달되면 세마포어의 값은 하나 감소
        int sem_post(sem_t *sem);
        int sem_wait(sem_t *sem);

        // 세마포어의 값은 0보다 작아질 수 없다!!!!!
        // 현재 0인 상태에서 sem_wait 호출하면 호출한 쓰레드는 함수가 반환되지 않아 블로킹 상태 ㅠ
        // 다른 쓰레드가 sem_post 호출하면 세마포어 값이 1이 되어 이 1을 0으로 감소시키면서 블로킹 상태 탈출!
        // 이런 특징을 이용해서 임계영역 동기화 시킴! => 세마포어의 값이 0과 1 오가기 때문에 바이너리 세마포어라고 함
        sem_wait(&sem);     // 세마포어 값을 0으로
        // 임계영역의 시작
        // ...
        // 임계영역의 끝
        sem_post(&sem);     // 세마포어 값을 1로
        ```

- 쓰레드의 소멸
    1. pthread_join 함수 호출
        - 쓰레드의 종료 대기 및 쓰레드의 소멸까지 유도
        - 쓰레드가 종료될 때까지 블로킹 상태에 놓이는 문제점
    2. pthread_detach 함수 호출
        - 일반적으로 이 함수로 쓰레드의 소멸 유도
        ```c
        int pthread_detach(pthread_t thread);
            // 성공 시 0, 실패 시 0 이외의 값 반환
        ```
        - 해당 함수 호출로 종료되지 않은 쓰레드가 종료되거나 블로킹 상태에 놓이지는 않음!
        - 쓰레드에게 할당된 메모리의 소멸을 유도
        - 해당 함수 호출 이후에는 해당 쓰레드를 대상으로 pthread_join 함수 호출 불가!
        
</details>

## 