<?

/****************** GroupControl 수정하기 위한 페이지 실질적으로 사용하는 pinData가 저장된다. ********************/

	$name			= $_POST['name'];
	$gpioNumber		= $_POST['gpioNumber'];
	$gpioValue		= $_POST['gpioValue'];
	$name			= $_POST['name'];
	$variableName	= $_POST['variableName'];
	$variableIndex	= $_POST['variableIndex'];

	$size			= sizeof($variableIndex);

	$fpGpio			= "/usr/local/apache/htdocs/project_os/DB/gpio/";

// GroupControl 필드에는 띄워쓰기 단위로 저장이 되므로 띄워쓰기 포함해서 저장할 수 있도록한다.
	for($i = 0 ; $i < $size ; $i++)
	{
		$list .= $variableName[$i];
		$list .= " ";
		$list .= $variableIndex[$i];
		$list .= "\n";
		$fpGpio .= $variableName[$i];
	}

	$fp				= "/usr/local/apache/htdocs/project_os/DB/web_variable/";
	$fp			   .= $name;
	$fp				= fopen($fp, "w+");

	$test			= fwrite($fp , $list);

	fclose($fp);

	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";

?>
