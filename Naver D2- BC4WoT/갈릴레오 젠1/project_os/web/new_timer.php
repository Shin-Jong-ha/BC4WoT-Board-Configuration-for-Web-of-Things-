<body>
	<?
/******************* 타이머 수정하고 추가하기 위한 페이지 ******************/

// DB에 저장되어있는 표 색깔을 읽어온다.
		$fpTableColor		=	fopen("/usr/local/apache/htdocs/project_os/DB/homepage/tableColor", "r");
		$TableColorResult	=	fread($fpTableColor, 255);
		$imageLocation		=	"/project_os/DB/homepage/image";

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
		$fpImageDown		=	fopen("/usr/local/apache/htdocs/project_os/DB/homepage/image/imageWhere/down", "r");
		$fpImageResult		=	fread($fpImageDown, 255);

		$imageResult		=	$imageLocation . "/" . $fpImageResult;
		$imageSearch		=	strpos($imageResult, ".jpg");
		$imageResult		=	substr($imageResult, 0, $imageSearch + 4);

// Timer DB를 읽어 온다.
		$fpTimer			=	fopen("/usr/local/apache/htdocs/project_os/DB/Time_DB/timer", "r+");
		$fpTimerResult		=	fread($fpTimer, 255);

		echo "<form action=new_timer_ok.php method=post> ";
		
// Timer 표 시작하는 부분
		echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white'><tr align='center'>";
		echo "<td align = 'center' colspan = 2  bgcolor = $TableColorResult><font size=4 color = white><b>Timer Setting</font></b></td></tr>";
		echo "<tr><td align = 'center' colspan = 2><textarea cols = 40 rows = 30  name = timerList >$fpTimerResult</textarea></td></tr>";
		echo "</table>";

// 배경 그림
		echo "<body background	=	'$imageResult'>";

		echo "<p align = center><input type ='submit' onClick='checkSolution(sb.onoff)'></form>"; 
	?> 
</body>