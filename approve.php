<?php
	//checks if session is private
	session_start();
	// if the user is editor
	if($_SESSION['isEditor']){
		// opens json file
		$jsonfile = "galleryinfo.json";	
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);
		if(isset($_POST["fileToApprove"])){
			// approves file that have been selected to approve
			$filename = $_POST["fileToApprove"];
			foreach ($contents as $i => $content) {	
				if($content['filename'] == $filename){			
					$contents[$i]["isApproved"] = true;
					break;	
				} // if	
				
			} // if
			
			$fileObj = fopen($jsonfile, "w");
			fwrite($fileObj, json_encode($contents));
			fclose($fileObj);
		}else{
			foreach ($contents as $i => $content) {				
				$contents[$i]["isApproved"] = true;
			} // foreach
			
			$fileObj = fopen($jsonfile, "w");
			fwrite($fileObj, json_encode($contents));
			fclose($fileObj);
		} // else
		// goes back to waiting for approval
		header("Location: waiting-for-approval.php"); /* Redirect browser */
	} // if
?>