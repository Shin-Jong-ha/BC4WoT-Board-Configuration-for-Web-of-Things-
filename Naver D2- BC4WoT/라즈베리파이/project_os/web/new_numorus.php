<meta name = "viewport" content = "width=device-width, initial-scale=1"/>

<?

/******************* GroupControl을 새롭게 추가한다. ******************/

// DB에 저장되어있는 표 색깔을 읽어온다.
	$fpTableColor		=	fopen("/var/www/project_os/DB/homepage/tableColor", "r");
	$TableColorResult	=	fread($fpTableColor, 255);
	$imageLocation		=	"/project_os/DB/homepage/image";

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
	$fpImageDown		=	fopen("/var/www/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult		=	fread($fpImageDown, 255);
	$imageResult		=	$imageLocation . "/" . $fpImageResult;

	$imageSearch		=	strpos($imageResult, ".jpg");
	$imageResult		=	substr($imageResult, 0, $imageSearch + 4);

	echo "<body background	=	'$imageResult'>";

	echo "<form action=new_numours_ok.php method=post> ";

	echo "<br>";	
	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white' bgcolor = white><tr align='center' bgcolor = $TableColorResult>";
	echo "<td align = 'center' colspan = 4><font size=4 color = white><b>New GroupControl</font></b></td></tr>";
	echo "<tr><td align = 'center'>GroupControl Name</td><td><input type=edit name = name value=0 size = 30><br></tr>";

	echo "</table>";
	echo "<p align = center><input type ='submit' value = 'ok' onClick='checkSolution(sb.onoff)'></form>"; 
?> 