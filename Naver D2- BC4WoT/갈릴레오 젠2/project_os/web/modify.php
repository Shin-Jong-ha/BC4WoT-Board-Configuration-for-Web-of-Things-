<meta name = "viewport" content = "width=device-width, initial-scale=1"/>

<?

/******************* pinData 수정하기 위한 페이지 ******************/

	$number					=		$_GET['number'];
	$listNumber				=		$_GET['listNumber'];
	$counter				=		$_GET['counter'];
	$fp_config				=		"/var/www/project_os/DB/gpio_variable/";

	if($number == 14 || $number == 15 || $number == 16){
// 아날로그 설정
		$analogLocation			=		"/var/www/project_os/DB/gpio_analog/";

		$analogLocationResult	=		$analogLocation . $number;

		$analogSetting			=		fopen($analogLocationResult, "r");
		$analogResult			=		fread($analogSetting, 255);
	}

	$j						=		0;
	$i						=		0;

// gpioCompare 값 (배열)
	$gpioCompareSize		=		array();
	$insertData				=		array();
	$gpioCompareNumber		=		array();
	$area					=		array();
	$dataResultIndex		=		array();
	$deleteIndex			=		array();


// 경로에 있는 파일 리스트를 읽어오기 위한 배열
	$fileList				=		array();
	$gpioList				=		array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

// 파일 포인터

	$imageLocation			=		"/project_os/DB/homepage/image";

// DB에 저장되어 있는 바탕화면 그림을 불러온다.
	$fpImageDown			=		fopen("/var/www/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult			=		fread($fpImageDown, 255);
	$imageResult			=		$imageLocation . "/" . $fpImageResult;

	$imageSearch			=		strpos($imageResult, ".jpg");
	$imageResult			=		substr($imageResult, 0, $imageSearch + 4);
	
	echo "<body background	=	'$imageResult'>";

// gpioCompare 파일 포인터
	$fp						=		"/var/www/project_os/DB/gpio_compare/";
	$fp						.=		$number;
	$fp						=		fopen($fp, "r");

// DB에 저장되어있는 표 색깔을 읽어온다.
	$fpTableColor			=		fopen("/var/www/project_os/DB/homepage/tableColor", "r");
	$TableColorResult		=		fread($fpTableColor, 255);



	$i					= 0;
	$k					= 0;
	$counter_test		= 0;
	$counter_condition	= 0;
	
// 폴더에 있는 파일을 열어서 조건에 의해 구별 한 뒤 저장함.
	while(($test	= fread($fp , 1)) != NULL)
	{
		$deleteIndex[$k] .= $test;

		if($variableTemp == 0)
		{
			if($test == " ")
			{
				$counter_test++;
				$counter_condition = 1;
			}

			if($counter_test == 2 && $counter_condition == 0)
			{
				$variableName[$i] .= $test;
				$variableTemp = 1;
			}
			else if($counter_test == 1 && $counter_condition == 0)
			{
				switch($test)
				{
					case 0 :
						$test = "같을 때";
						break;
					case 1 :
						$test = "보다 클 때";
						break;
					case 2 :
						$test = "크거나 같을 때";
						break;
					case 3 : 
						$test = "보다 작을 때";
						break;
					case 4 :
						$test = "작거나 같을 때";
						break;
					default :
						break;
				}
				
				$dataResultIndex[$i] .= "비교 조건 = " . $test;
			}
			else if($counter_test == 0 && $counter_condition == 0)
			{
				$dataResultIndex[$i] = "GPIO # = " . $test . "&nbsp&nbsp";

			}
			$counter_condition = 0;
		}
		else if($variableTemp == 1)
		{
			$variableIndex[$i] .= $test;

			if($test == "\n")
			{
				$k++;
				$i++;
				$variableTemp = 0;
			}
		}
	}

// 처음인 경우
	if($counter == 0)
	{
		$test = sizeof($variableName);
		$listNumber = $test;
	}
// 갯수를 추가 했을 시에
	else
	{
		$listNumber = $listNumber + 1;
	}

	echo "<form action=modify_ok.php?number=$number method=post> ";
	echo "<br>";	

// GPIO 설정 표 시작
	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white'><tr align='center'>";
	echo "<td align = 'center' colspan = 2  bgcolor = $TableColorResult><font size=4 color = white><b>'$number' GPIO 설정</font></b></td></tr>";

// GPIO #가 14보다 작을 경우 (디지털)
	if($number < 14)
	{

// UART
		if($number == 0)
		{
			echo "<tr><td align = 'center' colspan = 2>
						<input type=radio name = config value=0>사용하지않음
						<input type=radio name = config value=2>입력
						<input type=radio name = config value=1>출력
						<input type=radio name = config value=5>유아트</tr>";
		}
		else if($number == 1)
		{
			echo "<tr><td align = 'center' colspan = 2>
						<input type=radio name = config value=0>사용하지않음
						<input type=radio name = config value=2>입력
						<input type=radio name = config value=1>출력
						<input type=radio name = config value=6>유아트</tr>";
		}
// PWM
		else if($number == 3 || $number == 5 || $number == 6 || $number == 9 || $number == 10 || $number == 11)
		{
			echo "<tr><td align = 'center' colspan = 2>
						<input type=radio name = config value=0>사용하지않음
						<input type=radio name = config value=2>입력
						<input type=radio name = config value=1>출력
						<input type=radio name = config value=4>PWM</tr>";

			echo "<tr><td align = 'center'><font size = 2><b>PWM 초기화</b></font></td><td align = 'center' colspan = 2><input type=edit name = pwm value=0></tr>";
			echo "<tr><td align = 'center'><font size = 2><b>PWM 변화량</b></font></td><td align = 'center' colspan = 2><input type=edit name = pwm_condition value=0></tr>";
		}
// PWM이 아닌 경우
		else
		{
			echo "<tr><td align = 'center' colspan = 2 bgcolor = 'white'>
						<input type=radio name = config value=0>사용하지않음
						<input type=radio name = config value=2>입력
						<input type=radio name = config value=1>출력</tr>";
		}
	}
// GPIO가 아날로그인 경우
	else
	{
		echo "<tr><td align = 'center' colspan = 2 bgcolor = 'white'>
					<input type=radio name = config value=0>사용하지않음<br>
					<input type=radio name = config value=4>아날로그 입력<br>
					<input type=radio name = config value=5>아날로그 출력</tr>";

		echo "<tr><td align = 'center' colspan = 2 bgcolor = 'white'>단위<input type = edit name = analogUnit value = $analogResult></td></tr>";	
	}

	echo "<tr><td align = 'center'><font size = 2><b>Pin Pair</b></font></td><td align = 'center' colspan = 2 bgcolor = 'white'><input type=edit name = pair value=0  size = 35></tr>";
	echo "</table>";
	echo "<br>";

// GPIO 비교 표 시작
	echo "<table border ='1' frame = hsides align = center width = '330' cellpadding='3' cellspacing='0' bordercolor='silver' bordercolorlight='white'><tr align='center'  bgcolor = $TableColorResult>";
	echo "<td align = 'center' colspan = 2><b><font  color = white>GPIO 비교</font></b> <a href = modify.php?number=$number&listNumber=$listNumber&counter=1>갯수 추가</a></tr>";

	for($j = 0 ; $j < $listNumber ; $j++)
	{
		echo "<tr><td align = 'center' colspan = 2 bgcolor = 'white'><SELECT class = box name = area[] itemname = '지역'>
				  <option value = '' select> 비교 조건</option>
				  <option value = '0' select> ==</option>
				  <option value = '1' select> ></option>
				  <option value = '2' select> >=</option>
				  <option value = '3' select> <</option>
				  <option value = '4' select> <=</option></SELECT>";

		echo "<SELECT class = box name = gpioCompareNumber[] itemname = '번호'> &nbsp&nbsp <option value = '' select> 타겟 GPIO #</option>";

		for($k = 0 ; $k < 20 ; $k++)
		{
			echo "<option value = $gpioList[$k] select> $gpioList[$k] </option>";
		}

		echo "</SELECT>&nbsp&nbsp<a href = 'gpio_compare_delete.php?number=$number&index=$j'><font size = 1>삭제</font></a><br><font size = 1 color = gray>$dataResultIndex[$j]</font></td></tr><tr><td align = center bgcolor = 'white'><font size = 2><b>비교 값</b></font></td><td> <input type = edit name = gpioCompareSize[] value = $variableName[$j] size = 32></tr><tr><td align = center><font size = 2><b>입력 값</b></font></td><td><input type = edit name = insertData[] value = $variableIndex[$j] size = 32></td></tr>";			  
		echo "</tr>";
	}

	echo "</table>";

	echo "<p align = center><input type ='submit' value = '수정하기' onClick='checkSolution(sb.onoff)'></form>"; 
?>
