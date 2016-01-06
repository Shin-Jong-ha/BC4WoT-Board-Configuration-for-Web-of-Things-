<html>

<head>
<meta http-equiv="content-type" content="text/html; charset=euc-kr">
<title>제목 없음</title>
<meta name="generator" content="Namo WebEditor">
<base target="detail"></head>

<body bgcolor="white" text="black" link="blue" vlink="purple" alink="red">

<form action = test.php method = post>
<script>

	function newFile()
	{
		var newFileResult = prompt("안녕하시오");
		var newFileResultURL = 'newSourceFile.php?newFile=' + newFileResult;
		if (newFileResult != null)
		{
			location.assign(newFileResultURL);
		}
	}
</script>
<input type = button value = NewFile onClick = newFile()></input>


<?php 

		$fileArray			=		array();
		$fileLocation		=		"/var/www/project_os/c_program/";
		$fileFp				=		dir($fileLocation);

		$fileArraySize		=		sizeof($fileLocation);

		if($fileArraySize == 0)
		{
			$fileLocation	=		"/var/www/project_os/c_program/";
			$fileFp			=		dir($fileLocation);
		}
		
		while(($fileResult	= $fileFp -> read()) == true)
		{
			$fileArray[$i++] = $fileResult;	
		}
		$fileArraySize		=		sizeof($fileArray);
		
		echo "<br>";
		while($j < $fileArraySize)
		{
			$searchResult = stripos($fileArray[$j], "c");
			$fileStrlen	  = strlen($fileArray[$j]);
			if($searchResult == $fileStrlen - 1)
			{
				$fileLocationResult = $fileLocation . "$fileArray[$j]";
				echo "○ <a href = sourceEdit.php?test=$fileLocationResult>$fileArray[$j]</a>";

				echo "<br>-------------<br>";
			}
			$j++;
		}
		
?>

</body>

</html>