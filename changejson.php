<?php
	$filename = $_POST["filename"];
	$firstname = $_POST["firstname"];
	$lastname = $_POST["lastname"];
	$description = $_POST["description"];
	$tags = $_POST["tags"];

	$jsonfile = "galleryinfo.json";	
	$current = file_get_contents($jsonfile);
	$contents = json_decode($current, true);	

	foreach ($contents as $index => $content) {
		
		if($content['filename'] == $filename){			
			$contents[$index]["first_name"] = $firstname;
			$contents[$index]["last_name"] = $lastname;
			$contents[$index]["description"] = $description;
			$contents[$index]["tags"] = $tags;
		}
		
	}


	$fileObj = fopen($jsonfile, "w");
	fwrite($fileObj, json_encode($contents));
	fclose($fileObj);

	//header("Location: index.php"); /* Redirect browser */
	header('Location: ' . $_SERVER['HTTP_REFERER']);

?>			