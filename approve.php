<?php
	//checks if session is private
	session_start();
	if($_SESSION['isEditor']){
		$jsonfile = "galleryinfo.json";	
		$current = file_get_contents($jsonfile);
		$contents = json_decode($current, true);
		if(isset($_POST["fileToApprove"])){
			$filename = $_POST["fileToApprove"];	
			foreach ($contents as $i => $content) {	
				if($content['filename'] == $filename){			
					$contents[$i]["isApproved"] = true;
					break;	
				}	
				
			}

			$fileObj = fopen($jsonfile, "w");
			fwrite($fileObj, json_encode($contents));
			fclose($fileObj);
		}else{
			foreach ($contents as $i => $content) {				
				$contents[$i]["isApproved"] = true;
			}
			
			$fileObj = fopen($jsonfile, "w");
			fwrite($fileObj, json_encode($contents));
			fclose($fileObj);
		}
		header("Location: waiting-for-approval.php"); /* Redirect browser */
	}
?>