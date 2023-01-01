<?php
	$f=fopen("data.txt","r");
	$d=fgets($f);
	fclose($f);
	echo $d;    		     			   		  
?>