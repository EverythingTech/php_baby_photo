<?php
	session_start();
	// checks if user is an editor
	if($_SESSION['isEditor']){
		// reads in json file
		$jsonfile = "galleryinfo.json";	
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);
		//deletes indicated file
		foreach ($_POST as $filename) {
			unlink('uploadedimages/'.$filename);
			unlink('uploadedimages/thumb/'.$filename);
			foreach ($contents as $index => $content) {		
				if($content['filename'] == $filename){			
					unset($contents[$index]);	
					break;		
				} // if		
			} // foreach

		} // foreach
		
		//writes to json
		$fileObj = fopen($jsonfile, "w");
		fwrite($fileObj, json_encode($contents));
		fclose($fileObj);
		//redirects to index.php
		header('Location: ' . $_SERVER['HTTP_REFERER']);
		
	}//if
?>