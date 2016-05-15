<?php
	unlink($_GET['filedir']);
	$jsonfile = "galleryinfo.json";	
	$current = file_get_contents($jsonfile);
	$contents = json_decode($current, true);	
	foreach ($contents as $content) {
		if($content['filename'] == $_GET['file']){
			unset($content);
			break;
		}
	}
	$fileObj = fopen($jsonfile, "w");
	fwrite($fileObj, json_encode($contents));
	fclose($fileObj);
?>