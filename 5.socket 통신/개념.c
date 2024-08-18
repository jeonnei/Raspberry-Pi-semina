Soket 개념

## Network 네트워크

- 범국가적인 연결 >> 거미줄
  % 각 연결 : link, edge
  % 연결이 모이는 지점의 기기 : node, vertice
  % 한 node에서 다른 node까지의 경로 : path, context
  
- 호스트 : 통신을 주고받는 주체가 되는 네트워크에 연결되어 있는 모든 장치들 ex) 컴퓨터,서버장비,스마트폰..
- 포트 : 논리적인 접속장소, ip를 토대로 해당 서버가 있는 컴퓨터에 접근 한 후에 하나의 컴퓨터에 여러개의
       서버가 실행될 수 있다 이때 어느 서버에 접속해야 하는지 컴퓨터에 알려주어야 한다. 이때 사용하는 것이 포트번호이다
  포트 번호 : 컴퓨터에서 실행되고 있는 서버를 구분 짓기 위한 16비트의 논리적 할당 0~65536번이 존재 short int
           0~1023 정해져 있음=well-known port ex) http(웹서버) 80, ssh 22,   
		   ip뒤에 :포트번호 형식으로 붙음 ex) 172.0.0.1:1012
- 패킷들을 잠시 저장하고 방향을 정해 보내줄 중간 거점 : 스위치 브릿지, 라우터  
  허브 : 패킷 신호를 그대로 다른 포트에 나눠서 보내주는 장비(cpu,buffer없음)
        하나의 버스를 실시간으로 n대가 공유 >> 데이터 속도 1/n
  스위치 : cpu,buffer를 넣어 데이터 속도를 1/n보다 성능을 높임
         연결된 장비들의 MAC 주소를 이용해 프레임을 필터링, 특정 장비에만 전달
  브릿지 : 하드웨어가 아닌 소프트웨어 적으로 스위치의 역할 수행
  라우터 : 하나의 네트워크에서 다른 네트워크로 패킷을 전달하기 위해 사용하는 장비
         충동 도메인과 브로드캐스트 도메인을 분리해서 작동
  게이트웨이 : 네트워크 간 연결 통로의 역할을 하는 개념 ex) 스위치 라우터 브릿지 소프트 웨어 ...
  https://study-recording.tistory.com/13?category=488928


## OSI 7계층
   네트워크에서 통신이 일어나는 과정을 7단계로 나눈 것
	
- 1계층 Physical : 인터넷 선, 무선, 광통신, 리피터, 허브등의 물리적인 연결
  2계층 Datalink : 브릿지, 스위치기기 간 프레임 전달, 기기 주소(MAC) 부여 CRC 에러 검출, 재전송, 흐름 제어
  3계층 Network  : 게이트웨이(라우터 등),패킷 전달, 주소(IP) 부여, QoS 결정
                 경로 설정(Route), Segmentation, 오류 제어
  4계층 Transport : TCP, UDP 등, 패킷 생성 및 전송, End to End 제어
                   연결 기반의 상태 제어, 신뢰성 확보 중복 검사 및 연결, 오류, 흐름 제어
  5계층 Session : ADSP, SCP, PPTP, SOCKS, H.245 등 논리적 연결, 유효성 검사
                어플리케이션에서 실질적으로 사용하는 통신 종단 Duplex, Half-duplex, Full-duplex 결정
                OS가 세션 연결, 중단, 재연결 등 실질적 역할
  6계층 Presentation : JPEG, MPEG 등 표현 방식이 일치하도록 변환 Encoding/Decoding
                      Compression/Decompression
  7계층 Application : HTTP, DHCP, DNS, FTP, Telnet 등 사용자가 실제로 사용하는 프로토콜


## IP
   Internet Protocol : 각 네트워크의 Host를 구별하기 위한 고유 주소,
   네트워크의 여러 노드들이 구별되어지는 해당 노드의 고유한 주소값과 그 주소값을 구성하고 해석할수 있는 방식 
  
- 종류 
  IPv4: xxx.xxx.xxx.xxx, 8비트씩 4자리의 32비트
  IPv6: xxx.xxx.xxx.xxx.xxx.xxx  16비트씩 8자리의 128비트
   % xxx : 0(0x00)~255(0xff)까지 값을 갖는 1byte의 숫자
- 표기법
  10진수 IP,2진수 IP,도메인 IP(www.google.com
- 고정 IP : 컴퓨터에 고정적으로 부여된 IP
          한번 부여되면 IP 반납을 하기 전까지는 다른 장비에 부여할 수 없는 고유의 IP로 보안성 우수
- 유동 IP : 모든 인터넷 사용자에게 고정IP를 부여해 주기 힘들기 때문에 일정한 주기 또는 사용자들이
          인터넷에 접속하는 매 순간마다 사용하고 있지 않은 IP주소를 임시로 발급해 준다. 대부분 유동 IP를 사용
- 공인 IP : ICANN에서 국가별 IP대역 관리> 한국인터넷진흥원에서 국내IP 주소들 관리> KT,LG,SKT에서 관리
           공유기를 사용시 공유기까지는 공인IP를 할당 받고 공유기에 연결되어있는 장치들은 사설 IP를 할당받음
		   사설 IP는 한 네트워크 안에서 내부적으로 사용되는 고유한 주소로 네트워크안에서만 유일  
  % 도메인 : IP를 기억하기 어렵기 때문에 IP에 부여한 이름
  % DNS(Domain Name Server:네임서버) : 숫자로 이루어진 ip주소와 일정한 형식을 가진 도메인을 서로 매핑시키는 정보
                                    모든 도메인은 주인만이 제어할수 있는 권한을 가짐


## 서버&클라이언트 모델

- 서버 : 데이터를 관리하고,서비스를 브라우저에 어울리는 형태(HTML)로 제공하는 네트워크 프로그램
- 클라이언트 : 서버에 정보를 요청하는 프로그램=브라우저
- 중앙집중형 정보 제공 방식  


## Manager & Agent 모델
- 한개의 Manager 프로그램이 여러개의 Agent 프로그램으로 정보 요청
  1:n관계, 


## P2P 모델
- Peer To Peer 동등계층 모델
  모든 노드가 동등한 자격으로 네트워크 참여, 각 노드(네트워크 구성 프로그램)들이 데이터를 서로 교환,토렌트
  
  
## Soket

- 두개의 프로세스(프로그램)가 네트워크를 통해 데이터를 송수신할때 TCP/IP를 이용하여 양쪽에 생성되는 통로(인터페이스), 
  소프트웨어로 작성된 추상적인 개념의 통신 접속점,   1982년 BSD UNIX 4.1에서 처음 소개되었음
  두 소켓이 연결되면 서로 다른 프로세스끼리 데이터를 전달 가능
  UNIX에서의 입출력 메소드의 표준인 개방/읽기/쓰기/닫기 메커니즘을 따름
  클라이언트 프로그램과 서버 프로그램은 각각 자신의 포트를 통해 통신해야 하고 이 포트를 사용하기 위해서 소켓을 이용한다.
  
  구성 : 프로토콜 : 통신규약
       Ip 주소 : 전 세계 컴퓨터에 부여된 고유 식별 주소
	   Port number : 컴퓨터(호스트) 내에서 네트워크 통신을 하고 있는 프로세스를 식별하는 번호
  종류 : 클라이언트 소켓 서버 소켓
  
- 서버(Server) 소켓
  서버 프로그램에서만 사용하는 소켓. 클라이언트로부터 연결 요청이 오기를 기다렸다가 연결 요청이 들어오면 클아이언트와
  연결을 맺고 다른 소켓을 만드는 일을 한다.
  1. socket() : 소켓 생성
  2. bind() : ip,port 설정
  3. listen() : 클라이언트의 접근 요청에 수신 대기열을 만들어 몇 개의 클라이언트를 대기시킬지 결정
  4. accept() : 클라이언트와의 연결을 기다림
  5. close()
  
- 클라이언트(Client) 소켓
  기다릴 필요 없이 바로 클라이언트 소켓을 생성. 서버프로그램으로 연결요청과 데이터 전송을 한다.
  1. socket() : 소켓 생성
  2. connect() : 통신할 서버의 설정된 ip와 port번호에 통신을 시도
  3. 통신을 시도할때, accept() 함수를 이용하여 클라이언트의  soket descriptor를 반환
  4. 이를 통해 클라이언트와 서버가 서로 read(),write()를 하여 통신(과정 반복)
  5. close()

- 전송계층 프로토콜 : 데이터 전달시 사용하는 프로토콜
  * 스트림(TCP/IP):  인터넷상에서 데이터를 메세지의 형태로 보내기 위해 IP와 함께 사용하는 프로토콜
	OSI통합하여 4계층으로 만듬
	패킷을 추적 관리 : 패킷에 번호를 부여하여 손실 확인,재조립 
	연결형 서비스,가상 회선 방식 안정성,신뢰성 보장,패킷의 순서 정확히 유지,에러 교정, 
	데이터 흐름 제어 및 혼잡 제어 가능,양방향,일대일 Byte 스트림을 통신,UDP보다 속도느림
	3-Way Handshake 방식을 통해 연결을 맺고, 4-Way Handshake를 통해 해제
	서버가 응답을 주지 않으면 계속적으로 요청하게 된다
	연속적 데이터 송수신보다는 신뢰성 있는 연결을 중시(연속적 데이터 송수신시 손실된 경우 재전송 요청 때문에)
	IP : 데이터의 배달 처리
	   % 패킷 : 인터넷 내에서 데이터를 보내기 위한 경로배정(라우팅)을 효율적으로 하기 위해
        	   데이터를 여러 조각 나누는데 이 중 하나의 조각
       % 3-Way Handshake : 목적지와 수신지를 정확히 하여 정확한 전송을 보장하기 위함
	       수신자가 패킷을 받을 때마다 ACK라는 별도의 패킷을 만들어서 보냄, 
		   일정 시간ACK가 오지 않았을때 송신자가 패킷을 다시 보냄(재전송)
	   % 가상 회선 방식 : TCP에서 가상회선(논리적 경로)을 배정하여 패킷들이 순서대로 이동
	   % 데이터 흐름 제어 : 송신측과 수신측의 데이터 처리 속도를 조절하여 수신측의 버퍼 오버플로우 방지
	   % 혼잡 제어 : 네트워크 내의 패킷 수가 넘치지 않게 방지  	
			   
  * 데이터그램 (UDP) : 데이터를 데이터 그램단위로 처리하는 프로토콜
    소켓을 만들고 그냥 UDP서버 IP,Port와 UDP 클라이언트 IP,Port로 데이터그램단위로 송수신
    서버하나에 여러개의 클라이언트들이 붙어서 데이터를 송수신 가능,일대일 일대다 다대다
	비연결형소켓이므로 연결을 위해 할당되는 논리적 경로 없음, 순서가 뒤바뀔수도 있음
	UDP Headaer의 CheckSum을 토해 최소한의 에러만 검출
	상대의 집주소(IP,Port)만 알면 그냥 편지를 보냄>> 수신자가 확인전까지 편지 왔는지 모름
	,수신자가 편지를 받았는지 읽었는지 관심 없음
	TCP보다 속도가 빠름, 신뢰성이 낮음, 연결의 맺고 끊는 과정 없음
	실시간 영상 스트리밍 등에 사용		  
		% 데이터 그램 : 독립적인 관계를 지니는 패킷
		
  * HTTP통신과 비교
    HTTP : 클라이언트의 요청이 있을 때만 서버가 응답하여 해당 정보를 전송하고 곧바로 연결을 종료하는 방식
	특징 : 클라이언트가 요청을 보내는 경우에만 서버가 응답하는 단방향 통신이다
	      서버로부터 응답을 받은 후에는 연결이 바로 종료된다.
		  실시간 연결이 아니고, 필요한 경우에만 서버로 요청을 보내는 상황에 유용하다
		  요청을 보내 서버의 응답을 기다리는 어플리케이션의 개발에 주로 사용된다
		  
## Soket 통신
  
- 서버와 클라이언트가 특정 포트를 통해 실시간으로 양방향 통신하는 방식
  서버와 클라이언트가 계속 연결을 유지하는 양방향 통신
  실시간으로 데이터를 주고받는 상황이 필요한 경우에 사용
  실시간 동영상 스트리밍이나 온라인 게임등과 같은 경우에 자주 사용됨
https://wiserloner.tistory.com/695?category=831127

- 소켓 버퍼 : 소켓은 따로 읽기/쓰기를 위한 버퍼를 관리(read(),write())
  

## 네트워크 바이트 순서

- 바이트 오더(byte order)
  메모리>레지스트리>cpu로 데이터를 읽을 때 순서를 가짐
  빅 엔디언 : 비트를 높은 곳에서부터 채워 넣음
  리틀 엔디언 : 비트를 주소가 낮은 곳에서부터 채워넣음
  네트워크 통신시 서로 다른 노드에 있는 호스트 서로간에 호환이 가능하도록 바이트 오더를 통일 해야함
  네트워크 바이트 오더는 빅 엔디언 방식을 따름

## 코드
- #include <sys/types.h>
- #include <sys/socket.h>

- int socket(int domain, int type, int protocol)
  domain : 소켓의 사용 영역 정의(프로토콜 family)AF_INET(인터넷영역IPv4),AF_INET6(IPv6),AF_UNIX(컴퓨터내에서 프로세스간의 통신 영역)...
  type : 소켓이 사용할 프로토콜의 유형을 정의, 서로 같은 타입과 프로토콜 사용해야함 SOCK_STREAM(TCP), SOCK_DGRAM(UDP), SOCK_RAW(사용자 정의)
  protocol : 어떤 프로토콜의 값을 결정   SOCKET_STREAM=IPPROTO_TCP , SOCKET_DGRAM=IPPROTO_UDP
  소켓 fd 반환 오류시 -1

- int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  1. int server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  2. struct sockaddr_in serveraddr;
     serveraddr.sin_family = AF_INET;
     serveraddr.sin_addr.s_addr = inet_addr("218.234.19.87");
     serveraddr.sin_port = htons(8080);
  3. client_len = sizeof(serveraddr);
  4. connect(server_sockfd, (struct sockaddr*)&serveraddr, client_len);

- 파일 함수 : 파일 시스템에서 제공하는, 파일의 입출력 함수
  ssize_t write(int fd, const void *buf, size_t count); //출력
  ssize_t read(int fd, void* buf, size_t count); //입력

- 소켓 함수 : 소켓에서 제공하는 데이터 입출력 함수
  int send(int fd, const void* msg, size_t len, int flags); //출력
  int recev(int fd, void* buf, size_t len, int flags); //입력

- 연결 종료
  close(int sockfd); //파일을 닫는 함수입니다. 유닉스에서는 소켓도 파일로 보기에
  closesocket(SOCKET sockfd); //윈도우에서는 이것을 사용

- int bind(int sockfd, struct sockaddr* my_addr, socklen_t addrlen);
  소켓을 인터넷 주소에 묶어주기 위해 사용, 자신이 어떠한 요청을 기다리는지를 명시
  struct_sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(8080);
  state = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

- int listen(int queue_size);
  수신 대기열을 만듬
  처리할 요청을 저장하고 차례로 실행 시킬 완충역할을 하는 큐를 만들기
  여러개의 수신 요청이 들어왔을 때 대기열  순서대로 accept 해줌
  
- int accept(int s, struct sockaddr* addr, socklen_t* addrlen);
  수신 대기열에서 꺼내 오는 역할 connect를 통해 만들어냇 상대 주소에 대한 연결 소켓
  즉 서버의 경우 서버 소켓 하나, n번의 외부 요청에 따른 각각의 n개의 연결소켓이 생성됨
  
- #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>

  int open(const char* pathname, int flags);
  int open(const char* pathname, int flags, mode_t mode);
  프로그램적으로 파일을 다루기 위한 요청을 운영체제에 보내기위해 파일의 핸들을 가져옴
  fd = open("my.txt", O_WRONLY|O_CREATE, 0755);
  flags : 비트 연산자를 통해 여러개의 플래그 사용가능
  O_RDONLY	읽기 전용
  O_WRONLY	쓰기 전용
  O_RDWR	읽기 / 쓰기
  O_CREATE	파일을 생성
  O_EXCL	파일이 있는지 검사
  O_APPEND	추가 모드로 열기
  O_NONBLOCK	비 봉쇄 모드로 열기
  mode_t mode : 파일의  소유자,그룹,other단위로 읽기/쓰기/실행 권한 지정
  반환값: open한 파일의 fd, 이를 read(),whrite()에 사용
 
  close(int fd); fd의 파일 닫기
  
  디스크>커널 버퍼> read() > 유저버퍼
  open 함수 사용하여 커널에게 파일 준비를 요청 > 디스크에서 커널 버퍼로 데이터가 옮겨서 저장됨 > 
  read()함수로 프로세스가 커널에게 파일 열람을 요청 >커널은 커널 버퍼에 있는 데이터를 유저 버퍼로 복사

- in_addr_t inet_addr(const char *cp) 점표기 방식 >> 이진 인터넷 주소
  char* inet_ntoa(struct in_addr in) 이진 인터넷 주소 >> 점표기 방식
  
- 소켓을 생성하는 함수
	SOCKET socket(int af,int type,int protocol);
	실패 시: -1(SOCKET_ERROR) 반환
	af: 네트워크 주소 체계
    #define AF_INET       2         //IPv4
    #define AF_INET6      23        //IPv6
	type: 소켓 타입
    #define SOCK_STREAM   1         //스트림 , TCP 프롤토콜의 전송 방식
    #define SOCK_DGRAM    2         //데이터 그램, UDP 프로토콜의 전송 방식
    #define SOCK_RAW      3         //RAW 소켓, 가공하지 않은 소켓
	protocol: 프로토콜
    #define IPPROTO_TCP   6         //TCP 프로토콜
    #define IPPROTO_UDP   17        //UDP 프로토콜
    #define IPPROTO_RAW   255       //RAW
	소켓을 닫는 함수
	int closesocket(SOCKET sock);
    https://badayak.com/4472
	
	
## 구조체
  객체 지향 프로그래밍에서 말하는 클래스의 모체가 되는 것으로 여러개의 자료형을 만들수 있는 방법
  여러 개의 데이터를 하나로 묶어서 사용할 수 있도록 하기 위해 만들어진 c언어 문법
  배열은 여러 개의 같은 자료형들을 하나로 묶는 것이라면 구조체는 서로 다른 자료형들을 하나로 묶어서 한꺼번에 다룸
- struct 구조체이름{
	자료형 멤버이름;
  };
- struct 구조체이름 변수이름;