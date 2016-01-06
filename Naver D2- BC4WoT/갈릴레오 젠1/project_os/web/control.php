<?

/****************** 디지털(0, 1)을 조작하기 위한 페이지 ********************/


	$power		=		$_GET['power'];						// 현재 켜짐, 꺼짐 상태 값을 읽어온다.
	$number		=		$_GET['number'];					// GPIO #
	$fp			=		"/usr/local/apache/htdocs/project_os/DB/gpio/";		// GPIO 경로
	$fp			.=		$number;							// GPIO 경로에 #을 더한다.

// 현재 상태가 켜짐 상태일 경우
	if($power == "off")
	{
			$fp = fopen($fp, "r+");
			fputs($fp , "0"); // 값에 0을 넣어서 LOW로 만든다.
	}
// 현재 상태가 꺼짐 상태일 경우
	else
	{
			$fp = fopen($fp, "w+");
			fputs($fp, "1"); // 값에 1을 넣어서 HIGH로 만든다.
	}

	echo "<meta http-equiv = 'Refresh' content='0.3; URL=test.php'>";
?>
