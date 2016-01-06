<?
/****************** pinCompare 삭제한다. ********************/

	$number =	$_GET['number'];
	$index	=	$_GET['index'];

// pinCompare 파일 포인터
	$fp						=		"/var/www/project_os/DB/gpio_compare/";
	$fp						.=		$number;
	$fp						=		fopen($fp, "r");

	$variableIndex = 0;
	$k = 0;
	$i = 0;

// 폴더에 있는 파일을 열어서 조건에 의해 구별 한 뒤 저장함.
	while(($test	= fread($fp , 8)) != NULL)
	{
		if($variableTemp == 0)
		{
			if($i == $index)
			{
				$i++;
				continue;
			}
			$variableIndex .= $test;
		}
		$i++;
	}

// pinCompare 파일 포인터
	$fp						=		"/var/www/project_os/DB/gpio_compare/";
	$fp						.=		$number;
	$fp						=		fopen($fp, "w");

	fputs($fp, $variableIndex);

	fclose($fp);

	echo "<meta http-equiv = 'Refresh' content='1; URL=modify.php?number=$number'>";

?>