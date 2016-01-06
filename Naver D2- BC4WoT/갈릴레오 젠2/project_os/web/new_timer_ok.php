<?
/******************* Timer 값을 받아서 데이터베이스에 저장하기위한 페이지 ******************/


// POST 방식을 통해 데이터 값을 받아온다.
	$timerList			= $_POST['timerList'];
// timer 데이터베이스 경로
	$fp	= "/var/www/project_os/DB/Time_DB/timer";

// timer 데이터베이스에 값을 입력한다.
	$fp = fopen($fp, "r+");
	fputs($fp , $timerList);
	fclose($fp);


	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";
?>
