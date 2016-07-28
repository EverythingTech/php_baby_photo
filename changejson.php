<?php
	//checks if session is private
	session_start();
	// if the user is editor
	if($_SESSION['isEditor']){
		// gets value for the edits
		$filename = $_POST["filename"];
		$firstname = $_POST["firstname"];
		$lastname = $_POST["lastname"];
		$description = $_POST["description"];
		$tags = $_POST["tags"];

		
		//sanitize the edits
		$tags = preg_replace('/\s+/', '', $tags);
		$firstname = strip_tags($firstname);
		$lastname = strip_tags($lastname);
		$description = strip_tags($description);
		$tags = strip_tags($tags);
		$firstname = trim($firstname);
		$lastname = trim($lastname);
		$description = trim($description);
		$tags = trim($tags);
		$firstname = stripslashes($firstname);
		$lastname = stripslashes($lastname);
		$description =  stripslashes($description);
		$tags = stripslashes($tags);

		// opens json file
		$jsonfile = "galleryinfo.json";	
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);	

		// changes the indicated file
		foreach ($contents as $index => $content) {
			if($content['filename'] == $filename){			
				$contents[$index]["first_name"] = $firstname;
				$contents[$index]["last_name"] = $lastname;
				$contents[$index]["description"] = $description;
				$contents[$index]["tags"] = $tags;
			} // if
			
		} // foreach
		//writes changes to the json
		$fileObj = fopen($jsonfile, "w");
		fwrite($fileObj, json_encode($contents));
		fclose($fileObj);

		//goes back to index.php
		header('Location: ' . $_SERVER['HTTP_REFERER']);
	}//if
?>			