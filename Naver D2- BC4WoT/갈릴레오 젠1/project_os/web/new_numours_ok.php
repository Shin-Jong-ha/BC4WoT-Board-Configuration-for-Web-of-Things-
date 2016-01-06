<?

/****************** GroupControl 추가하기 위한 페이지 ********************/

	$name			= $_POST['name'];
	$initValue		= $_POST['initValue'];

	$fp				= "/usr/local/apache/htdocs/project_os/DB/web_variable/";
	$fp			   .= $name;
	$fp				= fopen($fp, "w+");

	$test			= fwrite($fp , $initValue);

	fclose($fp);

	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";

?>
