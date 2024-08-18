#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <pthread.h>

#define CS_MCP3208 8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

volatile int adcValue_1 = 0;
volatile int adcValue_2 = 0;
int read_mcp3208_adc(unsigned char adcChannel)
{
      unsigned char buff[3];

      buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
      buff[1] = ((adcChannel & 0x07) << 6);
      buff[2] = 0x00;

     digitalWrite(CS_MCP3208, 0);              // Low : CS Active

     wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

     buff[1] = 0x0f & buff[1];                 //12비트 중 상위 4비트
     adcValue_1 = ( buff[1] << 8) | buff[2];   //12비트 중 상위 4비트 + 12비트 중 하위 8비트

     digitalWrite(CS_MCP3208, 1);              // High : CS Inactive

     return adcValue_1;
}
void *adc_1()													//가변저항1 포인터함수
{
	while(1)
	{
		adcValue_1 = read_mcp3208_adc(0);		
		printf("adcValue_1 = %d\n", adcValue_1);
		delay(300);
	}
}
void *adc_2()													//가변저항2 포인터함수
{
	while(1)
	{
		delay(300);
		adcValue_2 = read_mcp3208_adc(1);
		printf("adcValue_2 = %d\n\n", adcValue_2);
	}
}
void *pwm()														//서보모터 포인터함수
{	
	while(1)
	{
		int duty = 43;
		//adcValue_1은 600~700, adcValue_2는 200~300 사이의 범위일 때 OPEN
		if(((600<adcValue_1)&&(adcValue_1 <700))&&((200<adcValue_2)&&(adcValue_2<300)))duty = 100;    
		else duty = 43;
		pwmWrite(1, duty);          								//HARDWARE PWM 출력
	}
}
int main(void)
{
	pthread_t p_thread[3];      									// 쓰레드를 위한 식별자
    int thread_id;
    int status;
	
	if(wiringPiSetup() < 0) return 1;                               //wiringPi 사용 준비 확인
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) return 1;      //spi 사용 준비 확인
	
	pinMode(CS_MCP3208, OUTPUT);                                    //cs 출력
	pinMode(1, PWM_OUTPUT);                  						//HARDWARE PWM 출력
	
	pwmSetMode(PWM_MODE_MS);                  						//서보모터 사용에 적합한 모드로 변경
	pwmSetClock(384);
	pwmSetRange(1000);                         						//19.2MHz / PWM클럭 / 분해능 = 주기, 19.2M / 384 / 1000 = 50Hz(20ms)
	
	thread_id = pthread_create(&p_thread[0], NULL, adc_1, NULL);
    if(thread_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

    thread_id = pthread_create(&p_thread[1], NULL, adc_2, NULL);
    if(thread_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
    
	thread_id = pthread_create(&p_thread[2], NULL, pwm, NULL);
    if(thread_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
	pthread_join(p_thread[2], (void **)&status);
	
	return 0;
}