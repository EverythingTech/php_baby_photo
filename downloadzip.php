<?php
	session_start();
	//checks if user is editor
	if($_SESSION['isEditor']){
		//opens json file
		$dir = "uploadedimages/";
		$jsonfile = "galleryinfo.json";
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);
		$files_to_zip = array();
		//creates a zip file
		foreach($contents as $content){
			if($content["isApproved"])
				array_push($files_to_zip, "uploadedimages/".$content["filename"]);
		} // foreach

		//if true, good; if false, zip creation failed
		if(!create_zip($files_to_zip,'photos.zip')) echo "error";

		//downloads zip file
		$file = "photos.zip";
		$file_name = basename($file);
		header("Content-Type: application/zip");
		header("Content-Disposition: attachment; filename=$file_name");
		header("Content-Length: " . filesize($file));
		readfile($file);

		header("Location: index.php"); /* Redirect browser */
		exit();
	}//if
	
	/* creates a compressed zip file */
	function create_zip($files = array(),$destination = '') {
		//vars
		$valid_files = array();
		//if files were passed in...
		if(is_array($files)) {
			//cycle through each file
			foreach($files as $file) {
				//make sure the file exists
				if(file_exists($file)) {
					$valid_files[] = $file;
				} // if
			} // foreach
		} // if
		//if we have good files...
		if(count($valid_files)) {
			//create the archive
			$zip = new ZipArchive();
			if(file_exists("photos.zip")){
				$res = $zip->open($destination,ZIPARCHIVE::OVERWRITE);
			}else{$zip->open($destination,ZIPARCHIVE::CREATE);}

			//add the files
			foreach($valid_files as $file) {
				$zip->addFile($file,$file);
			} // foreach
			//debug
			//echo 'The zip archive contains ',$zip->numFiles,' files with a status of ',$zip->status;

			//close the zip -- done!
			$zip->close();

			//check to make sure the file exists
			return file_exists($destination);
		} else {
			return false;
		} // else
	} // create_zip

?>
