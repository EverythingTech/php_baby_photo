<?php
	session_start();
	if($_SESSION['isEditor']){

		$jsonfile = "galleryinfo.json";	
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);	
		foreach ($_POST as $filename) {
			unlink('uploadedimages/'.$filename);
			unlink('uploadedimages/thumb/'.$filename);
			foreach ($contents as $index => $content) {		
				if($content['filename'] == $filename){			
					unset($contents[$index]);	
					break;		
				}		
			}

		}
		$fileObj = fopen($jsonfile, "w");
		fwrite($fileObj, json_encode($contents));
		fclose($fileObj);
		//header("Location: index.php"); /* Redirect browser */
		header('Location: ' . $_SERVER['HTTP_REFERER']);
	}
?>