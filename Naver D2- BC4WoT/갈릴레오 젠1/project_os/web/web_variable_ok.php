<?



	$name			=		$_GET['name'];
	$variableName	=		array();
	$variableIndex	=		array();
	$variableTemp	=		0;
	$i				=		0;
	$fpGpio			=		"/usr/local/apache/htdocs/project_os/DB/gpio/";

	$fp				=		"/usr/local/apache/htdocs/project_os/DB/web_variable/";
	
	$fp			   .=		$name;
	$fp				=		fopen($fp, "r");

// 처음부터 끝까지 데이터를 읽어온다. variableTemp값을 0과 1을 넣어서 번갈아가면서 저장하도록함.
	while(($test	= fread($fp , 1)) != NULL)
	{
		if($variableTemp == 0)
		{
			$variableName[$i] .= $test;
// 띄워쓰기가 될 경우
			if($test == ' ')
			{
				$fpGpioResult = $fpGpio;
				$fpGpioResult .= $variableName[$i];
				$fpGpioResult = trim($fpGpioResult);
				$fpGpioResult = fopen($fpGpioResult, "r+");

				$variableTemp = 1;
			}
		}
		else if($variableTemp == 1)
		{
// 파일의 끝이거나 개행문자 일 경우
			if($test == "\n" | $test == "\0")
			{
				$t = fwrite($fpGpioResult, $variableIndex[$i]);

				$variableTemp = 0;
				$i++;
			}
			else
			{
				$variableIndex[$i] .= $test;
			}
		}
	}
	fclose($fp);

	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";

?>
