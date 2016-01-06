<?

/****************** Setting 페이지에서 데이터를 입력하기 위한 페이지이다. ********************/

	$title				=		$_POST['title'];
	$tableColor			=		$_POST['tableColor'];
	$refreshTime		=		$_POST['refreshTime'];
	$initUpBackground	=		$_POST['initUpBackground'];
	$initDownBackground	=		$_POST['initDownBackground'];
	$outside			=		$_POST['outside'];

// 배경
	$whereImage			=		$_POST['whereImage'];
	$backgroundImage	=		$_POST['backgroundImage'];
	
	$titleLocation		=		"/usr/local/apache/htdocs/project_os/DB/homepage/title";
	$colorLocation		=		"/usr/local/apache/htdocs/project_os/DB/homepage/tableColor";
	$refreshLocation	=		"/usr/local/apache/htdocs/project_os/DB/homepage/refreshTime";
	$imageLocation		=		"/usr/local/apache/htdocs/project_os/DB/homepage/image/imageWhere";
	$outsideLocation	=		"/usr/local/apache/htdocs/project_os/DB/outside_library/";

	
	if($outside		!= NULL)
	{
		$outsideLocation	=		$outsideLocation . $outside;
		echo "$outsideLocation";
		$outsideFp			=		dir($fp_config);

// 폴더에 있는 파일을 전부 읽어온다.
		while(NULL != ($fileResult = $outsideFp -> read()))
		{
			echo "$fileResult";
		}

// 파일 포인터 종료
		$outsideFp -> close();
	}

	if($initUpBackground == 1)
	{
		$imageLocationUp	=		$imageLocation . "/up";		
		$fp					=		fopen($imageLocationUp, "w");
		fputs($fp, $refreshTime);
	}
	
	if($initDownBackground == 1)
	{
		$imageLocationDown	=		$imageLocation . "/down";
		$fp					=		fopen($imageLocationDown, "w");
		fputs($fp, $refreshTime);
	}

	if($refreshTime != NULL)
	{
		$fp					=		fopen($refreshLocation, "w");
		fputs($fp, $refreshTime);
	}

	if($title != NULL)
	{

		$fp					=		fopen($titleLocation, "w");
		fputs($fp, $title);
	}

	if($tableColor != NULL)
	{
		$fp					=		fopen($colorLocation, "w");
		fputs($fp, $tableColor);
	}

	if($whereImage != NULL && $backgroundImage != NULL)
	{
		if($whereImage == "up")
		{
			$imageLocationResult	=		$imageLocation . "/" . "up";			
			$fp						=		fopen($imageLocationResult, "w");
			fputs($fp, $backgroundImage);
		}
		else if($whereImage == "down")
		{
			$imageLocationResult	=		$imageLocation . "/" . "down";
			$fp						=		fopen($imageLocationResult, "w");
			fputs($fp, $backgroundImage);
		}
	}

	echo "<meta http-equiv = 'Refresh' content='0; URL=setting.php'>";
?> 
