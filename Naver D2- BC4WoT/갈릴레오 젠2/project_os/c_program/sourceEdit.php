<html>

<head>
<meta http-equiv="content-type" content="text/html; charset=euc-kr">
<title>���� ����</title>
<meta name="generator" content="Namo WebEditor">


<body bgcolor="white" text="black" link="blue" vlink="purple" alink="red">

<script>
	function setAlert(result)
	{
		alert(result);
	}


</script>
<form action = sourceSave.php method = POST>
<?

	$test = $_GET['test'];

	$fpTest = fopen($test, "r+");
	$fpResultList;

	while(($fpResult = fread($fpTest, 1)) != NULL)
	{
		$fpResultList = $fpResultList . $fpResult;
	}
	$fpResultList = trim($fpResultList);


	echo "<textarea cols = 100 rows = 50 name = sourceCode> $fpResultList</textarea>";
	echo "<input type = 'hidden' name = sourceLocation value = $test></input>";
	echo "<input type ='submit' value = 'ok' onClick=setAlert(aa)></form>";

?>

</body>

</html>