<?
	$number					=	$_GET['number'];
	$config					=	$_POST['config'];
	$pair					=	$_POST['pair'];
	$pwm					=	$_POST['pwm'];
	$pwm_condition			=	$_POST['pwm_condition'];

// GPIO VARIABLE 값 변수
	$gpio_variable			=	$_POST['gpio_variable'];
	$variable_area			=	$_POST['variable_area'];
	$gpio_variable_index	=	$_POST['gpio_variable_index'];

// analog 설정값
	$analogUnit				=	$_POST['analogUnit'];

// 조건 값 변수
	$gpio_compare			=	$_POST['area'];
	$gpioCompareNumber		=	$_POST['gpioCompareNumber'];
	$gpioCompareSize		=	$_POST['gpioCompareSize'];
	$insertData				=	$_POST['insertData'];
	$compareNumberSize		=	sizeof($gpioCompareNumber);

	$deleteIndex			=	$_POST['deleteIndex'];


	$fp	= "/var/www/project_os/DB/gpio_config_DB/";
	$fp	.= $number;

	$fp = fopen($fp, "r+");
	fputs($fp , $config);

	if($analogUnit != NULL)
	{
		echo "abcdefg";
		$fp = "/var/www/project_os/DB/gpio_analog/";
		$fp .= $number;
		
		$fp = fopen($fp, "w+");
		fputs($fp, $analogUnit);
	}

	if($pair != 0)
	{
		$fp	= "/var/www/project_os/DB/gpio_pair/";
		$fp	.= $number;

		$fp = fopen($fp, "w+");
		fputs($fp , $pair);
	}

	echo "$pwm";
	if($pwm != 0)
	{
		$fp = "/var/www/project_os/DB/gpio/";
		$fp .= $number;

		$pwm_temp = $pwm * 200000;

		$fp = fopen($fp, "w+");
		fputs($fp, $pwm_temp);
	}

	if($pwm_condition != 0)
	{
		$fp = "/var/www/project_os/DB/gpio_pwm/";
		$fp .= $number;

		$fp = fopen($fp, "r+");
		$pwm_condition_temp = $pwm_condition * 200000;

		fputs($fp, $pwm_condition_temp);
	}

	for($j = 0 ; $j < $compareNumberSize ; $j++)
	{
		$fp				= "/var/www/project_os/DB/gpio_compare/";
		$fp				.= $number;

		$fp				= fopen($fp, "r+");
		
		$compareResult	.= $deleteIndex[$j];

		fputs($fp, $compareResult);
	}

	for($j = 0 ; $j < $compareNumberSize ; $j++)
	{
		$fp				= "/var/www/project_os/DB/gpio_compare/";
		$fp				.= $number;

		$fp				= fopen($fp, "r+");
		
		$compareResult	.= $gpioCompareNumber[$j];
		$compareResult	.= " ";
		$compareResult	.= $gpio_compare[$j];
		$compareResult	.= " ";
		$compareResult	.= $insertData[$j];
		$compareResult	.= " ";
		$compareResult	.= $gpioCompareSize[$j];

		if($j != $compareNumberSize - 1)
		{
			$compareResult	.= "\n";
		}

		fputs($fp, $compareResult);
	}

	if($gpio_variable != NULL && $variable_area != NULL && $gpio_variable_index != 0)
	{

		$gpioResult = strpos($gpio_variable, "_");
	
		$fp			= "/var/www/project_os/DB/gpio_variable/";
		$fp			.= $gpio_variable;
		unlink($fp);

		if($gpioResult != NULL)
		{
			$gpioTemp	= substr($gpio_variable, $gpioResult + 1, strlen($gpio_variable));
			$gpioResult	= $number . "_". $gpioTemp;
		}
		else
		{
			$gpioResult = $number . "_" . $gpio_variable;
		}

		$fp				= "/var/www/project_os/DB/gpio_variable/";
		$fp			   .= $gpioResult;
		$fp				= fopen($fp, "w+");

		$variable_insert= $variable_area . " " . $gpio_variable_index . " " . "0";

		$test			= fwrite($fp, $variable_insert);
	}

	fclose($fp);
	
	
	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";
?>
