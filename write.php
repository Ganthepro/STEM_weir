<?php
    $wmode = $_GET["wmode"];
	$f = fopen("send.txt", "w");
    if ($wmode == "plus") {
        fwrite($f,"+");
    } elseif ($wmode == "minus") {
        fwrite($f,"-");
    } elseif ($wmode == "reset") {
        fwrite($f,"r");
    }
    else {
        fwrite($f,"");
    }
	fclose($f);
?>