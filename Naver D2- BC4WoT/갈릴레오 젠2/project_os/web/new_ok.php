<?

/****************** 새롭게 추가할때 OK 하는 페이지 ********************/

	$number			= $_POST['number'];
	$setting		= $_POST['setting'];
	$number2		= $_GET['number2'];

// 추가할 때 범위를 벗어나는 경우 오류를 출력한다. 아니면 정상적으로 입력함.
	if((($number >= 0) && ($number <= 20)))
	{
		$fp	= "/var/www/project_os/DB/gpio_config_DB/";
		$fp	.= $number;

		$fp = fopen($fp, "r+");
		fputs($fp , $setting);
		fclose($fp);
	}
	else
	{
		echo "<p align = center>";
		echo "경고!!";
		echo "0번 부터 20번까지 GPIO를 추가해주세요.";
		echo "</p>";
	}

	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";
?>
