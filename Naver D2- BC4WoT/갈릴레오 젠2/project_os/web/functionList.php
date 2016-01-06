<?

/****************** 외부 함수가 저장이 된다. ********************/


// DB에 저장되어있는 표 색깔을 읽어온다.
	function fileList($list, $size)
	{
		$i				=		0;
		$j				=		-1;
		$fileList		=		array();
		$fileFp			=		dir($list);


// 디렉토리의 파일 리스트를 처음부터 읽어온다.
		while(($fileResult = $fileFp -> read()) == true)
		{
			$fileList[$i++] = $fileResult;
		}
		echo "<br>";
// 표 시작
		echo "<table width = $size border = 1 cellpadding='3' cellspacing='1' frame = 'void'>";

		$fileListSize = sizeof($fileList);

// 파일 포인터 종료
		$fileFp -> close();

// 표에 출력한다. (오류있음 수정할것)
		while($j++ <= $fileListSize)
		{
// 현재 폴더와 이전 폴더도 리눅스처럼 출력된다. 막기
			if($fileList[$j] == "." | $fileList[$j] == ".." | $fileList[$j] == "")
			{
				continue;
			}

			echo "<tr><td bgcolor = white><p align = center><b><a href = modify_web_variable.php?name=$fileList[$j]&counter=0>$fileList[$j]</a></b></p></td>";
			echo "<td bgcolor = white><p align = center><b><a href = web_variable_ok.php?name=$fileList[$j]>Run</a></b></p></td></tr>";
		}

// 표 종료
		echo "</table>";
	}
	function bgColor()
	{
		// DB에 저장되어있는 표 색깔을 읽어온다.
		$fpTableColor		=	fopen("/var/www/project_os/DB/homepage/tableColor", "r");
		$TableColorResult	=	fread($fpTableColor, 255);

		return $TableColorResult;
	}

	function tableList($size)
	{
// DB에 저장되어있는 표 색깔을 읽어온다.
		$fpTableColor		=	fopen("/var/www/project_os/DB/homepage/tableColor", "r");
		$TableColorResult	=	fread($fpTableColor, 255);

		$configLocation		=	"/var/www/project_os/DB/gpio_config_DB/";
		$pairLocation		=	"/var/www/project_os/DB/gpio_pair/";

// DB에 저장되어있는 표 색깔을 읽어온다.
		$fpTableColor		=	fopen("/var/www/project_os/DB/homepage/tableColor", "r");
		$TableColorResult	=	fread($fpTableColor, 255);

		echo "<br>";

// main 홈페이지 : width = 800, new 홈페이지 330
		echo "<table width = $size border = 1 cellpadding='3' cellspacing='1' frame = 'void' align = center><tr><td align = center bgcolor = $TableColorResult colspan = 2>
			<font color = white><b>Current PinMode</b></font></td></tr>";

		if($size == 800)
		{
			echo "<tr><td bgcolor = white><font size = 1><img src = off.png width = 10 height = 10> &nbsp 0 ~ 13 : Digital Port <br> 
			<img src = off.png width = 10 height = 10> &nbsp 14 ~ 19 : Analog Port <br> 
			<img src = off.png width = 10 height = 10> &nbsp 0 : UART0_RX <br> 
			<img src = off.png width = 10 height = 10> &nbsp 1 : UART0_TX <br> 
			<img src = off.png width = 10 height = 10> &nbsp 3, 5, 6, 9, 10, 11 : PWM</td>";
		}
		echo "<td width = 600 bgcolor = white>";

		for($j = 0 ; $j < 20 ; $j++)
		{
			$configLocationResult	=	$configLocation . $j;
			$fp						=	fopen($configLocationResult, "r");
			$fpConfig				=	fread($fp, 255);

			$pairLocationResult		= $pairLocation . $j;
			$fp						= fopen($pairLocationResult, "r");
			$fpRead					= fread($fp, 255);

			if($fpConfig != 0)
			{
				if($fpConfig == "1")
				{
					$config = "Output";
				}
				else if($fpConfig == "2")
				{
					$config = "Input";
				}
				else if($fpConfig == "3")
				{
					$config = "Output";
				}
				else if($fpConfig == "4")
				{
					$config = "Analog";
				}
				else if($fpConfig == "5")
				{
					$config = "PWM";
				}
				echo "<font size = 2>$j : <font size = 1><b>$config</b></font> <font size = 1><b>(PAIR $fpRead)</b></font><br></font>";
			}
		}

		echo "</td></tr></table>";
	}
?>