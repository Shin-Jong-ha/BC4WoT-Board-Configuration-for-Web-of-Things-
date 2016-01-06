<meta name = "viewport" content = "width=device-width, initial-scale=1"/>

<?

/******************* Pin을 새롭게 추가함 ******************/

// DB에 저장되어있는 표 색깔을 읽어온다.
	$fpTableColor		=	fopen("/usr/local/apache/htdocs/project_os/DB/homepage/tableColor", "r");
	$TableColorResult	=	fread($fpTableColor, 255);

	$imageLocation		=	"/project_os/DB/homepage/image";

	require("./functionList.php");

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
	$fpImageDown		=	fopen("/usr/local/apache/htdocs/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult		=	fread($fpImageDown, 255);
	$imageResult		=	$imageLocation . "/" . $fpImageResult;

	$imageSearch		=	strpos($imageResult, ".jpg");
	$imageResult		=	substr($imageResult, 0, $imageSearch + 4);

	echo "<body background	=	'$imageResult'>";
	echo "<form action=new_ok.php method=post> ";
	echo "<br>";

// 표 시작	
	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3'	cellspacing='0' bordercolor='silver' bordercolorlight='white' bgcolor = white>";
	
	echo "<tr align= 'center' bgcolor = $TableColorResult>";
	echo "<td align = 'center' colspan = 4><font size=3 color = white><b>New Pin</font></b></td></tr>";

	echo "<tr><td align = 'center'>Pin #</td><td><input type=edit name = number value=0></td></tr>
	<tr><td align = 'center'>PinMode</td><td><input type=edit name = setting value=0></td></tr>";

	echo "</table>";

	tableList(330);

	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3'	cellspacing='0' bordercolor='silver' bordercolorlight='white' bgcolor = white>";
	echo "<tr align = center bgcolor = $TableColorResult>";
	echo "<td align = center colspan = 4><font size = 3 color = white><b>Pin Mode</font></b></td></tr>";
	echo "<tr align = center><td><font size = 1>0</font></td><td><font size = 1>None</font></td></tr>";
	echo "<tr align = center><td><font size = 1>1</font></td><td><font size = 1>Digital Output</font></td></tr>";
	echo "<tr align = center><td><font size = 1>2</font></td><td><font size = 1>Digital Input</font></td></tr>";
	echo "<tr align = center><td><font size = 1>3</font></td><td><font size = 1>Analog Input</font></td></tr>";
	echo "<tr align = center><td><font size = 1>4</font></td><td><font size = 1>PWM Output</font></td></tr>";
	echo "<tr align = center><td><font size = 1>5</font></td><td><font size = 1>UART RX</font></td></tr>";
	echo "<tr align = center><td><font size = 1>6</font></td><td><font size = 1>UART TX</font></td></tr>";
	echo "</table>";

	echo "<p align = center><input type ='submit' value = 'ok' onClick='checkSolution(sb.onoff)'></form>"; 
?> 