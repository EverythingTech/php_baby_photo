<?php
	$errorInForm = false;
	include("formheader.inc");
	$first_name = $last_name = $access = $desciption = $tags = $user_agreement = "";
	$firstNameErr = $lastNameErr = $accessErr = $user_agreementError = $fileUploadErr = $successMsg= "";

	if(isset($_POST["first_name"])){
		$first_name = $_POST["first_name"];
	}
	if(isset($_POST["last_name"])){
		$last_name = $_POST["last_name"];
	}
	if(isset($_POST["access"])){
		$access = $_POST["access"];
	}
	if(isset($_POST["desciption"])){
		$desciption = $_POST["desciption"];
	}
	if(isset($_POST["tags"])){
		$tags = $_POST["tags"];
	}
	if(isset($_POST["user_agreement"])){
		$user_agreement = $_POST["user_agreement"];
	}
	
	if(isset($_GET["viewAlbum"])){
		$viewAlbum = $_GET["viewAlbum"];
	}else{
		$viewAlbum = false;
	}


	if($_SERVER["REQUEST_METHOD"] == "POST"){
		//validation
		if (empty($first_name)){
			$firstNameErr = "First name is required";
			$errorInForm = true;
		} else if(!preg_match("/^[a-zA-Z ]*$/",$first_name)) {
	  		$firstNameErr = "Only letters and white space allowed in first name"; 
	  		$errorInForm = true;
		}
		if (empty($last_name)){
			$lastNameErr = "Last name is required";
			$errorInForm = true;
		} else if(!preg_match("/^[a-zA-Z ]*$/",$last_name)) {
	  		$lastNameErr = "Only letters and white space allowed in last name"; 
	  		$errorInForm = true;
		}
		
		if(empty($access)){
			$accessErr = "Option of access is required";
			$errorInForm = true;
		}

		if($user_agreement != 'agree'){
			$user_agreementError = "You have to agree to continue";
			$errorInForm = true;
		}

		if(empty($_FILES["fileToUpload"]["name"])){
			$fileUploadErr = "You have to choose a file to continue";
			$errorInForm = true;
		}else{
			
			$target_dir = "uploadedimages/";
			$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
			$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
			$check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
			// Check if image file is a actual image or fake image
    		if(!$check){
		        $fileUploadErr = "File is not an image.";
		        $errorInForm = true;
    		}
    		// Check if file already exists
			if (file_exists($target_file)) {
			    $fileUploadErr =  "Sorry, file already exists.";
			    $errorInForm = true;
			}
			// Check file size
			if ($_FILES["fileToUpload"]["size"] > 2097152) {
			    $fileUploadErr = "Sorry, your file is larger than 2MB";
			    $errorInForm = true;
			}
			
			// Allow certain file formats
			if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType != "JPG" && $imageFileType != "PNG"){
			    $fileUploadErr = "Sorry, only JPG, JPEG, PNG files are allowed.";
			    $errorInForm = true;
			}
			
		}
		if($errorInForm){
			include("form.inc");
			
		}else if ($_SERVER["REQUEST_METHOD"] == "POST"){			

			//put image into folder
			if(move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)){

				$successMsg = "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
				$currentCounterPath = "uploadedimages/imageCount.txt";
					
				$currentCounter = file_get_contents($currentCounterPath);
				$counterNum = (int)$currentCounter + 1;
				
				$fileObj = fopen($currentCounterPath, "w");
				fwrite($fileObj, $counterNum);
				fclose($fileObj);
				$imgExt = pathinfo($target_file, PATHINFO_EXTENSION);
				rename($target_file, $target_dir.($counterNum-1).'.'.$imgExt);


				//write to json
				$jsonfile = "galleryinfo.json";
				if(!file_exists("galleryinfo.json")){
					touch("galleryinfo.json");
					$fileObj = fopen($jsonfile, "w");
					fwrite($fileObj, "[]");
					fclose($fileObj);
				}		
				$current = file_get_contents($jsonfile);
				$contents = json_decode($current);	
				$newArr = array("filename" => (($counterNum-1).'.'.$imgExt), "isApproved" => 0);
				$_POST["filename"]= $newArr["filename"];
				$_POST["isApproved"] = $newArr["isApproved"];
				$_POST["tags"] = preg_replace('/\s+/', '', $_POST["tags"]);
				array_push($contents, $_POST);
				
				$fileObj = fopen($jsonfile, "w");
				fwrite($fileObj, json_encode($contents));
				fclose($fileObj);
				



				//create thumbnail for the uploaded file

				//new image
				$imgSrc = $target_dir.($counterNum-1).'.'.$imgExt;
				//getting the image dimensions
				list($width, $height) = getimagesize($imgSrc); 
				//saving the image into memory (for manipulation with GD Library)
				if($imgExt == "jpg" || $imgExt == "JPG" || $imgExt == "jpeg")
					$myImage = imagecreatefromjpeg($imgSrc);
				else if($imgExt == "png" || $imgExt == "PNG")
					$myImage = imagecreatefrompng($imgSrc);
				///--------------------------------------------------------
				//setting the crop size
				//--------------------------------------------------------
				if($width > $height) $biggestSide = $width;
				else $biggestSide = $height;
				 
				//The crop size will be half that of the largest side
				$cropPercent = .5;
				$cropWidth   = $biggestSide*$cropPercent;
				$cropHeight  = $biggestSide*$cropPercent;
				
				//getting the top left coordinate
				$c1 = array("x"=>($width-$cropWidth)/2, "y"=>($height-$cropHeight)/2);
				//--------------------------------------------------------
				// Creating the thumbnail
				//--------------------------------------------------------
				$thumbSize = 250;
				$thumb = imagecreatetruecolor($thumbSize, $thumbSize);
				imagecopyresampled($thumb, $myImage, 0, 0, $c1['x'], $c1['y'], $thumbSize, $thumbSize, $cropWidth, $cropHeight);
				if($imgExt == "jpg" || $imgExt == "JPG" || $imgExt == "jpeg")
					imagejpeg($thumb, $target_dir.'thumb/'.($counterNum-1).'.'.$imgExt);
				else if ($imgExt == "png" || $imgExt == "PNG")
					imagepng($thumb, $target_dir.'thumb/'.($counterNum-1).'.'.$imgExt);
				imagedestroy($thumb);

				
				echo '<script type="text/javascript">
           			window.location = "index.php"
      				</script>';

      			die();



			}else{
				$fileUploadErr = "Sorry, there was an error uploading your file.";
			}
			
			include("form.inc");
			
		}
	}else if($viewAlbum){
		$file = "galleryinfo.json";
		$current = file_get_contents($file);
		$contents = json_decode($current);
		echo "<pre>";
		var_dump($contents);
    	echo "</pre>";
    	$dirname = "uploadedimages/";
		$images = glob($dirname."*.*");
		foreach($images as $image) {
			echo '<img src="/'.$image.' " width = "400" height = "300" alt = "'.$image.'"><br/>'."\n";
		}

		

	}else{
		include("form.inc");		
	}
	
	include("footer.inc");

	
?>