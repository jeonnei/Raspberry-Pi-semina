#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringSerial.h>
#include <errno.h>

#define swich1 0 	//physical 11
#define swich2 1 	//physical 12
#define swich3 2 	//physical 13
#define swich4 3 	//physical 15

#define LED1 22		//physical 31
#define LED2 23		//physical 33
#define LED3 24		//physical 35
#define LED4 25		//physical 37

unsigned char led[4] = {LED1, LED2, LED3, LED4};
unsigned char swich[4] = {swich1,swich2,swich3,swich4};
int shift=0,flag=0;
int fd = 0;
char data = 0;


void reset_led(void)
{
	for(int i=0; i<4; i++)          										 //풀업 방식 HIGH(OFF)로 초기화
		digitalWrite(led[i],1);
}

void sw1()																	 //led SHIFT
{
	flag = 0;
	if(shift==4)shift=0;
	while(digitalRead(swich1)==0);
	delay(20);
	reset_led();
	digitalWrite(led[shift],0);
	shift++;
}
void sw2()							 										 //led 패턴점등
{
	shift+=2;
	delay(300);
	reset_led();
	if(shift==4)shift=1;
	else if(shift>=5)shift=0;
	digitalWrite(led[shift],0);
}
void sw3()							  										//키보드 숫자에 따라 LED출력
{
	for(int count=0; count<4; count++) digitalWrite(led[count], 1);  		//초기화
	if((data-'0') < 4) digitalWrite(led[data-'0'],0);                    	//led출력
}
void sw4()							  										//라즈베리 -> PC 문자열출력
{
	printf("\n");
	char Temp[100] = {0};
	fgets(Temp, sizeof(Temp), stdin);						    			//배열에 문자열 저장
	serialPuts(fd, Temp);													//저장한 문자열 전송
	serialPuts(fd, "\n");
	fflush(stdout);                                                         //출력 버퍼 지우기
	flag=0;
}
int main()
{
	if(wiringPiSetup()< 0)										     		//wiringPi 준비 완료 확인
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1;
	}
	if((fd = serialOpen("/dev/ttyAMA0", 9600)) < 0)                       	//포트 열기
	{
		fprintf(stdout, "unable to open serial device: %s\n", strerror(errno));
		return 1;
	}
	for(int i=0;i<4;i++) pinMode(led[i],OUTPUT);							//LED 출력
	for(int j=0;j<4;j++) pinMode(swich[j],INPUT);							//SWITCH 입력
	reset_led();															//풀업방식 LED설계이므로 다꺼주기
	while(1)	
	{
		if(serialDataAvail(fd)>0) 
		{
			data = serialGetchar(fd); 										//데이터 받기
			printf("%c", (char)data);										//pc ->라즈베리
			serialPutchar(fd, data);										//단일 바이트 전송
			fflush(stdout);													//오류방지
		}
		if(digitalRead(swich1)==0)sw1();
		else if(digitalRead(swich2)==0)flag=2;
		else if(digitalRead(swich3)==0)flag=3;
		else if(digitalRead(swich4)==0)flag=4;
		if(flag==2)sw2();
		else if(flag==3)sw3();
		else if(flag==4)sw4();
	}
	return 0;
}




