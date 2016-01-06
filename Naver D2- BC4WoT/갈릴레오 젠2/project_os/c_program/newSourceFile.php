<?
	$newFile = $_GET['newFile'];
	$newFileResult = "/var/www/project_os/c_program/" . $newFile;
	$fpNewFile = fopen($newFileResult, "w");
	
	echo "$fpNewFile";
	echo "Aa";

?>