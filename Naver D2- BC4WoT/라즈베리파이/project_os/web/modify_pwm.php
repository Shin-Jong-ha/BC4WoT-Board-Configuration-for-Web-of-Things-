 <?

/****************** PWM을 증가하고 감소하기 위한 페이지 ********************/

	$condition			= $_GET['condition'];
	$number				= $_GET['number'];

	$imageLocation		=	"/var/www/project_os/DB/homepage/image";

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
	$fpImageDown		=	fopen("/var/www/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult		=	fread($fpImageDown, 255);
	$imageResult		=	$imageLocation . "/" . $fpImageResult;

	$imageSearch		=		strpos($imageResult, ".jpg");
	$imageResult		=		substr($imageResult, 0, $imageSearch + 4);

	echo "<!-- <body background	=	'$imageResult'> -->";

// PWM 변화량 값
	$fp_pwm		= "/var/www/project_os/DB/gpio_pwm/";
	$fp_pwm	   .= $number;

// PWM 현재 값
	$fp_gpio	= "/var/www/project_os/DB/gpio/";
	$fp_gpio	.= $number;

// PWM DB에 저장되어있는 값을 읽어온다.
	$gpioData		= fopen($fp_gpio, "r+");
	$gpioData		= fread($gpioData , 255);

// 현재 PWM 값이 5V 이하 일 경우 ( 갈릴레오 Gen1에서는 1000000 (5V)이 최대이다.) 
	if($gpioData <= 1000000)
	{
		$config_open	= fopen($fp_pwm, "r+");
		$config_index	= fread($config_open , 255);
		
		if($condition == "sub")
		{
			$gpioData = $gpioData - $config_index;

// (PWM 값 - PWM 변화량 값) < 0 일 경우, 오류 메시지 출력
			if($gpioData < 0)
			{
				echo "오류!";
				echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";
				return;
			}
		}
		else
		{
			$gpioData = $gpioData + $config_index;

// (PWM 값 - PWM 변화량 값) > 5V 일 경우, 오류 메시지 출력	
			if($gpioData > 1000000)
			{
				echo "오류!";
				echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";
				return;
			}
		}

		$fp	= "/var/www/project_os/DB/gpio/";
		$fp	.= $number;

		$fp = fopen($fp, "w+");
		fputs($fp , $gpioData);

		fclose($fp);
	}
	else
	{
		echo "오류!";
	}

	echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";
?>