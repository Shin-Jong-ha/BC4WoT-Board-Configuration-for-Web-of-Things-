<?
/****************** GroupControl 삭제 ********************/

// GroupControl 이름을 받는다.
	$name						=	$_GET['name'];

// GroupControl 경로 추가
	$web_variable_location		=	"/usr/local/apache/htdocs/project_os/DB/web_variable/";
	$web_variable_location	   .=	$name;

// GroupControl 삭제
	unlink($web_variable_location);

	echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";
?>