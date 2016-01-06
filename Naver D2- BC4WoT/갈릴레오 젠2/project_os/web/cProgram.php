<?

/****************** 웹 페이지에서 Control Program을 실행하고 종료하기 위한 페이지이다. ********************/

	$power					=	$_GET['power'];

// 파일 경로, 명령어 
	$fileLocation			=	"/var/www/project_os/c_program/add  > /dev/null &";
	$gpioLocation			=	"/var/www/project_os/DB/gpio/";
	$turnOff				=	"ps -ef | grep /var/www/project_os/c_program/add";
	$killProcess			=	"kill ";

// on으로 입력이 될 경우
	if($power == "on")
	{
// PHP 함수를 이용해 파일을 실행한다.
		$t					=	exec($turnOff, $output);
		$turnOffLocation	=	$output[0];
		$turnOffLocation	=	explode(" ", $turnOffLocation);
	
// 웹에서 파일을 실행할 경우 유저 명이 "www-data"로 되는데 이를 찾아서 확인을 한다.
		if($turnOffLocation[0] == "www-data") // "www-data"가 있을 경우 실행 되었다는 의미
		{			
			$t					=	exec($fileLocation, $output);
			echo "<script>alert('프로그램이 실행되었습니다!!')</script>";
		}
		else
		{
			echo "<script>alert('프로그램이 실행중입니다!!')</script>";
		}
	}
	else if($power == "off")
	{
		$t					=	exec($turnOff, $output);
		$turnOffLocation	=	$output[0];
		$turnOffLocation	=	explode(" ", $turnOffLocation);

		if($turnOffLocation[0] == "www-data")
		{			
			echo "<script>alert('프로그램이 실행중이지 않습니다')</script>";
		}
		else
		{
// 프로그램을 종료할 경우 데이터 베이스를 초기화 한다.
			for($j = 0 ; $j <= 20 ; $j++)
			{
				$gpioLocationResult = $gpioLocation . $j;
				$result				= fopen($gpioLocationResult, "w+");
				fputs($result, "0");
			}

// 프로세스를 KILL 한다.
			$turnOffLocation	=	$output[0];
			$turnOffLocation	=	explode(" ", $turnOffLocation);
			$killProcess		.=	$turnOffLocation[6];
			$t					=	exec($killProcess, $output);

			echo "<script>alert('프로그램이 종료되었습니다.')</script>";
		}
	}
	echo "<meta http-equiv = 'Refresh' content='0; URL=setting.php'>";
?>
