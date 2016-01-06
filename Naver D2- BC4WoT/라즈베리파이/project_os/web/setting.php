
<head>
<meta name = "viewport" content = "width=device-width, initial-scale=1"/>
<style>
	A:link 
	{
		COLOR: black; TEXT-DECORATION: none
	}
	A:visited 
	{
		COLOR: blue; TEXT-DECORATION: none
	}
	A:hover
	{	
		COLOR: orange; TEXT-DECORATION: underline 
	}
</style>

<script>
	var setting = 0;
	var settingColor = 0;
	var settingBackground = 0;

	function settingOn(){
		setting = 1;
	}

	function settingColorOn(){
		settingColor = 1;
	}

	function settingBackgroundOn(){
		settingBackground = 1;
	}
</script>

</head>

<?

/******************* 셋팅하는 페이지 ******************/

	$menuSelect			=		$_GET['menuSelect'];

	$i					=		0;
	$j					=		0;
	$color				=		array("#F44336", "#E91E63", "#9c27b0", "#673ab7", "#3f51b5", "#2196f3", "#03a9f4", "#00bcd4", "#009688", "#4caf50", "#8bc34a",
									   "#cddc39", "#ffeb3b", "#ffc107", "#ff9800", "#ff5722", "#795548", "#9e9e9e", "#607d8b", "#000000", "#FFFFFF");
	$colorName			=		array("Red", "Pink", "Purple", "Deep Purple", "Indigo", "Blue", "Light Blue", "Cyan", "Teal", "Green", "Light Green", "Lime", 
									   "Yellow", "Amber", "Orange", "Deep Orange", "Brown", "Grey", "Blue Grey", "Black", "White");
// 제목 경로
	$titleLocation		=		"/var/www/project_os/DB/homepage/title";
	$fpTitle			=		fopen($titleLocation, "r");
	$title				=		fread($fpTitle, 255);

// 이미지 경로
	$imageLocation		=		"/var/www/project_os/DB/homepage/image";
	$imageLocationResult=		"/var/www/project_os/DB/homepage/image";
// 폴더에 있는 파일을 전부 읽어온다.
	$fpImage			=		dir($imageLocation);

	$imageLocation		=		"/var/www/project_os/DB/homepage/image";

// 외부 라이브러리
	$outsideLocation	=		"/var/www/project_os/DB/outside_library";

// 외부 라이브러리 값을 읽어온다.
	$fpOutside			=		dir("/var/www/project_os/DB/outside_library");

// 표 배경 색깔
	require('./functionList.php');
	$backgroundColor	=		bgColor();

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
	$fpImageDown		=		fopen("/var/www/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult		=		fread($fpImageDown, 255);
	$imageResult		=		$imageLocation . "/" . $fpImageResult;

	$imageSearch		=		strpos($imageResult, ".jpg");
	$imageResult		=		substr($imageResult, 0, $imageSearch + 4);

	echo "<body background	=	'$imageResult'>";
	echo "<form action=setting_ok.php method=post>";

	while(NULL != ($fileResult = $fpImage -> read()))
	{
		$fileList[$i++] = $fileResult;
	}

	echo "$TableColorResult";
	
	echo "<br>";
	echo "<table border = '1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white'><tr align='center'>";
	echo "<tr><td align = 'center' colspan = 3 bgcolor = $backgroundColor><b><a href = setting.php?menuSelect=1><font color = 'white' size= '2'>Setting</font></a></b>";

	if($menuSelect == 1)
	{
		echo "<tr><td align = 'center' colspan = 2 bgcolor = white>Control Program</td><td align = center bgcolor = white><a href = cProgram.php?power=on><font color = black>Execute</font></a>&nbsp&nbsp&nbsp<a href = cProgram.php?power=off><font color = 'black'>Exit</font></a><br></td></tr>";
		echo "<tr><td align = 'center' colspan = 2 bgcolor = white>Title</td><td bgcolor = white><input type=edit name = title></td></tr>";
		echo "<tr><td align = 'center' colspan = 2 bgcolor = white>Refresh Time</td><td bgcolor = white><input type=edit name = refreshTime></td></tr>";
	}

	echo "</table><br>";

	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white' bgcolor = white><tr align='center'>";
	echo "<tr><td align = 'center' colspan = 5 bgcolor = $backgroundColor><font size=4><b><a href = setting.php?menuSelect=2><font color = white size = 2>Table Color</font></a></font></b></td></tr>";
	
	if($menuSelect == 2)
	{
		for($i = 0 ; $i < sizeof($color) ; $i++)
		{
			echo "<tr><td align = 'center' colspan = 2 bgcolor = $color[$i] width = 30  bgcolor = white></td>
					  <td bgcolor = white>	<font size = 1>$color[$i] </font></td>
					  <td bgcolor = white>	<b><font size = 2>$colorName[$i]</b></font></td>
					  <td bgcolor = white>	<input type=radio name = tableColor value=$color[$i]></td>";
		}

		echo "</tr>";
		echo "</table>";
	}

	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white' bgcolor = white><tr align='center'>";
	echo "<tr><td align = 'center' colspan = 5 bgcolor = $backgroundColor><font size=4><b><a href = setting.php?menuSelect=3><font color = white size = 2>Background Image</font></a></font></b></td></tr>";
	
	echo "<br>";

	if($menuSelect == 3)
	{
		echo " <tr><td colspan = 2 align = center  bgcolor = white>	<font size = 1>위 초기화<input type = radio name = initUpBackground value = 1>아래 초기화<input type = radio name = initDownBackground value = 1> </font></td></tr>";
		for($i = 0 ; $i < sizeof($fileList) ; $i++)
		{
			if($fileList[$i] != "." && $fileList[$i] != ".." && $fileList[$i] != "imageWhere")
			{
				$imageResult		=		$imageLocationResult . "/" . $fileList[$i];
				echo "<tr><td align = 'center' colspan = 2 width = 30  bgcolor = white><img src = $imageResult width = 330 height = 330></td>
					  <tr><td colspan = 2  bgcolor = white>	<font size = 1>$fileList[$i] </font></td></tr>
					  <tr><td width = 10  bgcolor = white>	선택 </td> <td align = center><input type = radio name = backgroundImage value = $fileList[$i]</td></tr>
					  <tr><td  bgcolor = white>	배경 위치</td><td align = center> <input type = radio name = whereImage value = 'up'> 위로 <input type = radio name = whereImage value = 'down'> 아래로";
			}
		}
	}
	echo "</tr>";
	echo "</table>";
	
	echo "<p align = center><input type ='submit' onClick='checkSolution(sb.onoff)'></form>"; 

?> 