#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208 8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

int read_mcp3208_adc(unsigned char adcChannel)
{
      unsigned char buff[3];
      buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
      buff[1] = ((adcChannel & 0x07) << 6);
      buff[2] = 0x00;

     digitalWrite(CS_MCP3208, 0);            	// Low : CS Active
     wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
     buff[1] = 0x0f & buff[1];               	//12비트 중 상위 4비트
     adcValue = ( buff[1] << 8) | buff[2];  	 //12비트 중 상위 4비트 + 12비트 중 하위 8비트
     digitalWrite(CS_MCP3208, 1);            	// High : CS Inactive

     return adcValue;
}

int main(void)
{
	int adcValue = 0;
	if(wiringPiSetup() < 0)
	{
	  fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));//라즈벨파이에서 표준출력(모니터)
      return 1;

	}
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) return 1;
	
	pinMode(CS_MCP3208, OUTPUT);
	
	while(1)
	{
		adcValue = read_mcp3208_adc(0);
		printf("adcValue = %d\n", adcValue);
		delay(100);
	}
	
	return 0;
}