#include<stdio.h>
#include<wiringPi.h>
#include <softPwm.h>							

#define swich1 0 			//physical 11
#define swich2 1 			//physical 12
#define swich3 2 			//physical 13
#define swich4 3 			//physical 15
#define DC_A 5				//physical 24
#define DC_B 4				//physical 23
#define servomoter 26		//physical 12

unsigned char swich[4] = {swich1,swich2,swich3,swich4};
int plag = 0;													//mode
int dc_speed =30;												//dc speed
int dc_way = 0;													//dc LOW
int servo_degree =43;											//서보모터 각도
int dc_plag=0;													//dc_mode

void servo_moter();												//서보모터 함수
void dc_moter();												//dc모터 함수

int main()
{
    if(wiringPiSetup()==-1) return -1;
	for(int j=0;j<4;j++) pinMode(swich[j],INPUT);				//SWITCH 입력
	pinMode(servomoter, PWM_OUTPUT);							//서보모터 출력
	pwmSetMode(PWM_MODE_MS); 									//PWM모드 markspace모드
	pwmSetClock(384);											//PWM주기 20ms  = 19.2*10^6Hz /384/1000 =50Hz
	pwmSetRange(1000);											//1000ms/50Hz = 20ms/Hz
	pinMode(DC_A, PWM_OUTPUT);
	pinMode(DC_B, PWM_OUTPUT);
	softPwmCreate(DC_A,0,200);									//200* 0.1ms 주기를 가지는 신호를 만듬
	softPwmCreate(DC_B,0,200);									//200* 0.1ms 주기를 가지는 신호를 만듬
	
	while(1)	
	{
		if(digitalRead(swich1)==0)								//스위치 1번 mode1
		{
			plag = 1;							
		}
		else if(digitalRead(swich2)==0)							//스위치 2번 mode2
		{
			plag = 2;
		}
		else if(digitalRead(swich3)==0)							//스위치 3번		
		{
			delay(20);											//채터링방지
			while(digitalRead(swich3)==0);
			delay(20);											//채터링방지
			dc_speed+=30;										//dc moter 속도 증가
			if(dc_speed==180)dc_speed=30;						//dc moter 속도가 지정된 최대치만큼 오르면 원상복구
		}
		else if(digitalRead(swich4)==0)							//스위치 4번
		{
			delay(20);											//채터링방지
			while(digitalRead(swich4)==0);					
			delay(20);											//채터링방지
			dc_plag+=1;											//스위치 4번을 누를 때 마다,
			if(dc_plag==2)dc_plag=0;							//dc plag가 1->2, 2->1
		}
		if(plag ==1)											//mode1일 때 servo moter 동작
		{
			servo_moter();
		}
		else if(plag ==2)										//mode2일 때 dc moter 동작
		{
			dc_moter();
		}
		
	}
	return 0;
}
void servo_moter()												//servo moter 동작
{
	pwmWrite(servomoter,servo_degree);
	delay(100);
	if(digitalRead(swich1)==0)
	{
		delay(20);												//채터링방지
		while(digitalRead(swich1)==0);
		delay(20);												//채터링방지
		servo_degree+=30;										//각도 증가
		if(servo_degree>103)servo_degree=43;					//0>180도 증가하면 0도로 복귀
	}
}

void dc_moter()													//dc moter 동작
{
	if(dc_plag==0)
	{
		softPwmWrite(DC_A,dc_speed);							//dc_speed만큼 pwm파형출력
		softPwmWrite(DC_B,dc_way);								//dc_way값은 0고정
	}
	else if(dc_plag==1)
	{
		softPwmWrite(DC_A,dc_way);								//dc_way값은 0고정
		softPwmWrite(DC_B,dc_speed);							//dc_speed만큼 pwm파형출력
	}
}