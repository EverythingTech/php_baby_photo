<?php

	$filename = $_POST["fileToDelete"];
	unlink('uploadedimages/'.$filename);
	unlink('uploadedimages/thumb/'.$filename);

	$jsonfile = "galleryinfo.json";	
	$current = file_get_contents($jsonfile);
	$contents = json_decode($current, true);		
	foreach ($contents as $index => $content) {		
		if($content['filename'] == $filename){			
			unset($contents[$index]);			
		}		
	}
	
	
	$fileObj = fopen($jsonfile, "w");
	fwrite($fileObj, json_encode($contents));
	fclose($fileObj);

	//header("Location: index.php"); /* Redirect browser */
	header('Location: ' . $_SERVER['HTTP_REFERER']);
?>