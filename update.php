<?php
	//$id = trim($_POST["id"]);
	//http://localhost/ultra/update.php?mode=0&distance=1&flow=2&volume=3&height=4
	$mode = $_GET["mode"];
	$distance =$_GET["distance"];
	$flow=$_GET["flow"];
	$volume=$_GET["volume"];
	$height=$_GET["height"];

	date_default_timezone_set("Asia/Bangkok");
	$f = fopen("data.txt", "w");
	fwrite($f, date("Y-m-d H:i:s",time()).",".$mode.",".$distance.",".$flow.",".$volume.",".$height);
	fclose($f);
?>		  