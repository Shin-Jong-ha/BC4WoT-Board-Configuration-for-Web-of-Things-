 #include "index.h"
 #include <stdio.h>
#include <fcntl.h>


/*
   7&#65533;&#65533; 1&#65533;&#65533; ë°•ê´‘&#65533;&#65533;
   ê°ˆë¦´&#65533;ˆì˜¤ ê¸°ì&#65533;&#65533;¼ë¡œ &#65533;°ëŠ” ì¤&#65533;  
*/


char* data_sprintf(int number)
{
		static char data[100];
		
		sprintf(data, "%d", number);

		return data;
}

void analogRead(int fp, int gpioNumber)
{
		char	fpData[100];
		char	analogInt[][2] = {"0", "1", "2", "3", "4", "5"};
		int		fp2, readResult;
		char	result[10];
        int     temp;

		if(gpioCompare(fp, gpioNumber) == 1)
		{
			write(0, "aawefpowjefpojwefopjwpfojpewfjpwofej", 5);
			return;
		}
		else
		{
			printf("wofeijwoeifjwioefj");
		}

		strcpy(fpData, "/sys/bus/iio/devices/iio:device0/in_voltage");
		strcat(fpData, analogInt[gpioNumber - 14]);
		strcat(fpData, "_raw");

		fp2 = open(fpData, O_RDONLY);

		if(fp2 == -1)
		{
			perror("readResult (Main) : ");
			//exit(0);
		}

		readResult = read(fp2, result, 255);

		result[readResult] = '\0';
//
//		temp = atoi(result) / 16;
//
//		sprintf(result, "%d", temp);


		
		printf("\n\n --------------------------------------------------------------%d ::::::: %s\n\n", gpioNumber, result);

		DBWrite(data_sprintf(gpioNumber), result);
		
		close(fp2);
}

int main(void)
{
		int status;
		// &#65533;Œì¼ &#65533;”ìŠ¤&#65533;¬ë¦½&#65533;&#65533;
		int gpio_file, gpio_config_file, gpio_unexport, gpio_pair;
		
		// GPIO &#65533;½ì–´&#65533;¤ê¸° &#65533;„í•œ &#65533;„ì‹œ ë³&#65533;&#65533;&#65533;
		int i = 0;
		int temp = 0;
		
// ÀÚ½Ä ÇÁ·Î¼¼½º
		int pid, childPid, childPidTemp;


		// GPIO ë²ˆí˜¸ 
		int gpio_number = -1, gpio_config_number = -1;

		// DBë¡&#65533; ë¶&#65533;&#65533;&#65533; &#65533;½ì–´&#65533;&#65533; ê°&#65533; &#65533;&#65533;&#65533;&#65533;
		
		char gpio_config_str[255] = {0};
		char gpio_result_str[2]; // DB&#65533;ì„œ &#65533;½ì–´&#65533;&#65533; ê°’ì„ &#65533;&#65533;&#65533;¥í•œ&#65533;&#65533;.
		char gpio_value_str[40];

		// DB ê²½ë¡œ
		char *pwd_temp			= "/var/www/project_os/DB/gpio";
		char *pwd_config_temp	= "/var/www/project_os/DB/gpio_config_DB/";
		char *pwd_value_temp	= "/sys/class/gpio/gpio";

		char* test[3] = {"nohup",  "/var/www/project_os/c_program/uart/uart", "&"};

		char pwd[50] = {0};

		/*
		   &#65533;&#65533;&#65533;˜ì&#65533; &#65533;Œì¼ &#65533;…ì¶œ&#65533;&#65533; êµ¬í˜„

		   &#65533;¹ì—&#65533;&#65533; GPIO ë¨¼ì&#65533; &#65533;¤ì •&#65533;˜ë©´

		   **************************************************
		   1. gpio_DB.txt : GPIO&#65533;ì„œ &#65533;½ì–´&#65533;¤ëŠ” ê°’ì„ &#65533;°ì´&#65533;°ë² &#65533;´ìŠ¤&#65533;&#65533; &#65533;&#65533;&#65533;¥í•¨.
		   2. gpio_config_DB.txt : GPIOë¥&#65533; &#65533;…ë ¥&#65533;¼ë¡œ &#65533; ì&#65533; ì¶œë ¥&#65533;¼ë¡œ &#65533; ì&#65533; &#65533;•í•œ&#65533;&#65533;. (&#65533;¹ì—&#65533;&#65533; &#65533;¤ì •&#65533;˜ê³  C&#65533;„ë¡œê·¸ë¨&#65533;ì„œ &#65533;½ëŠ”&#65533;&#65533;.)
		   **************************************************
	    */

		init(); // Galileo Level Shifter ì´ˆê¸°&#65533;&#65533;
		pid = fork(); // À¯¾ÆÆ® ÀÚ½Ä ÇÁ·Î¼¼½º »ı¼º
		while(gpio_config_number++ < 19)
		{
				// &#65533;¤ì • DB &#65533;Œì¼ &#65533;¤í”ˆ
				strcpy(gpio_config_str, pwd_config_temp);
				strcat(gpio_config_str, data_sprintf(gpio_config_number));

				gpio_config_file = open(gpio_config_str, O_RDONLY, S_IRUSR); // O_RDONLY, S_IRUSR

				if( gpio_config_file == -1 ) // DB &#65533;¬ëŠ”&#65533;&#65533; &#65533;¤ë¥˜ê°&#65533; &#65533;ˆì„ ê²½ìš° &#65533;„ë¡œê·¸ë¨ ì²˜ìŒ&#65533;¼ë¡œ &#65533;Œì•„ê°&#65533;
				{
						perror("config_file error (MAIN)");
						close(gpio_config_file);

						continue; // ì²˜ìŒ&#65533;¼ë¡œ
				}

				read(gpio_config_file, gpio_result_str, 2); // GPIO &#65533;¤ì • ê°’ì„ &#65533;½ì–´&#65533;¨ë‹¤.

				gpio_number++; // ëª‡ë²ˆ GPIO&#65533;¸ì&#65533;

				/*
				   ***************************
				   1. HTML &#65533;…ë ¥ (HTML&#65533;ìœ¼ë¡&#65533; ë²„íŠ¼) - ê°’ì„ &#65533;½ì–´&#65533;&#65533; GPIOë¡&#65533; ë³´ë‚´ì£¼ì–´&#65533;¼í•¨
				   2. &#65533;”ì&#65533;&#65533;&#65533; &#65533;…ë ¥ - &#65533;¸ë&#65533; ë²„íŠ¼ &#65533;…ë ¥ : DB&#65533;&#65533; &#65533;&#65533;&#65533;¥í•¨
				   3. &#65533;”ì&#65533;&#65533;&#65533; ì¶œë ¥ - DBê°’ì„ &#65533;½ì–´&#65533;&#65533; ì¶œë ¥&#65533;œë‹¤. (HIGH / LOW)
				   4. &#65533;„ë‚ ë¡œê·¸ &#65533;…ë ¥ - &#65533;„ë‚ ë¡œê·¸ ê°’ì„ &#65533;½ì–´&#65533;&#65533; DB&#65533;&#65533; &#65533;&#65533;&#65533;¥í•¨
				   5. &#65533;„ë‚ ë¡œê·¸ ì¶œë ¥ - DBê°’ì„ &#65533;½ì–´&#65533;&#65533; ì¶œë ¥&#65533;&#65533;
				   ***************************
				*/

				// GPIO &#65533;°ì´&#65533;°ë&#65533; &#65533;&#65533;&#65533;¥í•˜ê±°ë‚˜ &#65533;½ì–´&#65533;¤ê¸° &#65533;„í•œ ë¶&#65533;ë¶&#65533;
				strcpy(pwd, pwd_temp); // ê²½ë¡œ (/project_os/DB/gpio/) ë¥&#65533; ë³µì‚¬&#65533;&#65533;
				strcat(pwd, "/");
				strcat(pwd, data_sprintf(gpio_config_number)); // GPIOë²ˆí˜¸ë¥&#65533; ë¶™ì¸&#65533;&#65533;.
		
				if((gpio_file = open(pwd, O_RDWR, S_IRUSR)) == -1) // GPIO DB &#65533;Œì¼&#65533;&#65533; &#65533;°ë‹¤.
				{
						perror("open_gpio_file (MAIN)");
						continue;
				}

				/* 
					output_DB(int data) : DB&#65533;&#65533; &#65533;&#65533;&#65533;¥ëœ ê°’ì„ &#65533;½ì–´&#65533;¨ë‹¤.
					insert_DB(int data) : DB&#65533;&#65533; ê°’ì„ &#65533;½ì…&#65533;œë‹¤.
				*/

				printf("\n\n --------------------------------------------------------------%d %c\n\n", gpio_config_number, gpio_result_str[0]);

				switch( gpio_result_str[0] )
				{
						case '0' : // &#65533;¬ìš©&#65533;˜ì&#65533; &#65533;ŠëŠ” ê²½ìš°
								printf("&#65533;¬ìš©&#65533;˜ì&#65533; &#65533;ŠìŒ\n");
								break;
						case '1' : // &#65533;”ì&#65533;&#65533;&#65533; ì¶œë ¥
								output_DB(gpio_file, gpio_config_number);
								break;
						case '2' : // &#65533;”ì&#65533;&#65533;&#65533; &#65533;…ë ¥
								insert_DB(gpio_file, gpio_config_number); // 10000 &#65533;&#65533;&#65533; ì— GPIO&#65533;ì„œ &#65533;½ì–´&#65533;¤ëŠ” ê°’ìœ¼ë¡&#65533; ë³&#65533;ê²½í•˜ê¸&#65533;
								break;
						case '3' : // &#65533;„ë‚ ë¡œê·¸ &#65533;…ë ¥
								analogRead(gpio_file, gpio_config_number);
								break;
						case '4' : // PWM ì¶œë ¥
								analogOutput(gpio_file, gpio_config_number);
								break;
						case '5' : // Rx_insert. 

									if( pid == -1 )
									{
										perror("fork error");
									}
									else if( pid == 0 )
									{
										
	//									//Rx_rasb(gpio_file, gpio_config_number);
										childPid = getpid();
										status = 1;

	//										insertUart();
										if(execlp(test[1], test[1], (char *)NULL) == 0)
										{
											perror("execlp");
											exit(0);
										}
									}
									else
									{
										printf("wefoijweojfeoiw pid = %d, %d", childPid,pid);
									}

								
								break;
						case '6' :

									if( pid == -1 )
									{
										perror("fork error");
									}
									else if( pid == 0 )
									{
	//									//Rx_rasb(gpio_file, gpio_config_number);
	//										printf("pid = %d", pid);
											status = 1;
	//										insertUart();
										if(execlp(test[1], test[1], (char *)NULL) == 0)
										{
											perror("execlp");
											exit(0);
										}
	//									

									}
									else
									{
										printf("wefoijweojfeoiw pid = %d", pid);
	//										break;
									}

						default : // &#65533;ˆì™¸ ì²˜ë¦¬
								printf("&#65533;¤ë¥˜\n");
								break;
				}

				close(gpio_file);
				close(gpio_config_file);
		
				i = 0; // ì´ˆê¸°&#65533;&#65533;
				gpio_number = -1;

				if(gpio_config_number == 19)
				{
					gpio_config_number = -1;
				}
		}
}
