<?
	$index = $_GET['index'];
	
	$fp				= "/var/www/project_os/DB/gpio_variable/";
	$fp			   .= $index;
	unlink($fp);

	$indexTemp		= strpos($index, "_");
	$indexResult	= substr($index, $indexTemp, strlen($index));
	$indexResult	= "/var/www/project_os/DB/gpio_variable/" . $indexResult;
	$variableFp		= fopen($indexResult, "w");



	echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";

?>