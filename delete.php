<?php
	session_start();
	//checks if user is editor
	if($_SESSION['isEditor']){
		// gets the file to delete and unlinks values
		$filename = $_POST["fileToDelete"];
		unlink('uploadedimages/'.$filename);
		unlink('uploadedimages/thumb/'.$filename);

		// reads in the json file
		$jsonfile = "galleryinfo.json";	
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);
		//unsets the indicated file
		foreach ($contents as $index => $content) {		
			if($content['filename'] == $filename){			
				unset($contents[$index]);			
			} // if		
		} // foreach
		// writes to json
		$fileObj = fopen($jsonfile, "w");
		fwrite($fileObj, json_encode($contents));
		fclose($fileObj);

		//redirects to index.php
		header('Location: ' . $_SERVER['HTTP_REFERER']);
	}//if
?>