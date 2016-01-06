<meta name = "viewport" content = "width=device-width, initial-scale=1"/>

<?

/******************* GroupControl 수정하기 위한 페이지 ******************/

	$name				= $_GET['name'];
	$listNumber			= $_GET['listNumber'];
	$counter			= $_GET['counter'];

	$variableName		= array();
	$variableIndex		= array();
	$variableTemp		= 0;
	$i					= 0;

	$imageLocation		=	"/project_os/DB/homepage/image";

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
	$fpImageDown		=	fopen("/var/www/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult		=	fread($fpImageDown, 255);
	$imageResult		=	$imageLocation . "/" . $fpImageResult;

	$imageSearch		=		strpos($imageResult, ".jpg");
	$imageResult		=		substr($imageResult, 0, $imageSearch + 4);

	echo "<body background	=	'$imageResult'>";

	$fp					= "/var/www/project_os/DB/web_variable/";
	$fp					.= $name;
	$fp					= fopen($fp, "r");

// DB에 저장되어있는 표 색깔을 읽어온다.
	$fpTableColor		=	fopen("/var/www/project_os/DB/homepage/tableColor", "r");
	$TableColorResult	=	fread($fpTableColor, 255);

	while(($test		= fread($fp , 1)) != NULL)
	{
		if($variableTemp == 0)
		{
			$variableName[$i] .= $test;

			if($test == " ")
			{
				$variableTemp = 1;
			}
		}
		else if($variableTemp == 1)
		{
			$variableIndex[$i] .= $test;

			if($test == "\n")
			{
				$i++;
				$variableTemp = 0;
			}
		}
	}
	
	if($counter == 0)
	{
		$test			= sizeof($variableName);
		$listNumber		= $test;
	}
	else
	{
		$listNumber		= $listNumber + 1;
	}

	fclose($fp);

	echo "<form action=modify_web_variable_ok.php method=post> ";

	echo "<br>";	
	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white'><tr align='center' bgcolor = $TableColorResult>";
	echo "<td align = 'center' colspan = 2><font size=4><b>GroupControl Modify</font></b><font size = 2><a href = modify_web_variable.php?name=$name&listNumber=$listNumber&counter=1><br>ADD</a>
	<a href = modify_web_variable_delete.php?name=$name>&nbspDELETE</a></td></tr>";
	echo "<tr><td align = 'center' colspan = 2>Name<input type=edit name = name value= $name><br></tr>";

	for($j = 0 ; $j < $listNumber ; $j++)
	{
		echo "<tr><td align = 'center' colspan = 2>Pin Number<input type=edit name = variableName[] value=$variableName[$j]><br>Pin Data<input type=edit name = variableIndex[] value=$variableIndex[$j]></tr>";
	}

	echo "</table>";
	echo "<p align = center><input type ='submit' onClick='checkSolution(sb.onoff)'></form>"; 
?> 