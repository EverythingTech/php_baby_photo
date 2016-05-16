<?php
	$filename = $_POST["fileToDelete"];
	unlink('uploadedimages/'.$filename);
	unlink('uploadedimages/thumb/'.$filename);

	$jsonfile = "galleryinfo.json";	
	$current = file_get_contents($jsonfile);
	$contents = json_decode($current, true);	
	$found = false;
	foreach ($contents as $index => $content) {
		if($found){
			
			$contents[$index-1] = $contents[$index];
		}
		else if($content['filename'] == $filename){			
			unset($contents[$index]);
			$found = true;
		}
		if($index == count($contents)){
			unset($contents[$index]);
		}
	}
	
	$fileObj = fopen($jsonfile, "w");
	fwrite($fileObj, json_encode($contents));
	fclose($fileObj);

	header("Location: index.php"); /* Redirect browser */
?>