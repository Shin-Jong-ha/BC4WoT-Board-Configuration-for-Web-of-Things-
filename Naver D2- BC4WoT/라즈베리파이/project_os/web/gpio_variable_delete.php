<?
	$index = $_GET['index'];
	

	$fp				= "/var/www/project_os/DB/gpio_variable/";
	$fp			   .= $index;
	unlink($fp);

	echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";

?>