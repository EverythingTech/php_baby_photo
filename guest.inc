<h1>Gallery</h1>
	<div id = buttonwrapper>
	<button class = "greenAcross" type = "button" onclick = "goto('import.php');">Upload</button>
	</div>
	<div id = "filterwrapper">
		<h3>Tools</h3>
		<div id = "toolswrapper">
		<h5>Keyword Search: </h5>
		<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post">
			<input type="search" id="search" name = "search" value = "<?php if(isset($_POST['search']) && $_POST["search"]!= "") echo $_POST["search"];?>" placeholder=<?php if(isset($_POST['search']) && $_POST["search"]!= "") echo '"'.$_POST["search"].'"'; else echo "'Keywords Search...'";?> />

		<h5>Sort By:</h5>
			<select id = "sort" name = "sorted" onchange="this.form.submit()">
				<option value = "sortfirstname" <?php if(isset($_POST['sorted'])){ if($_POST['sorted'] == 'sortfirstname') echo 'selected="selected"';} ?>>First Name</option>
				<option value = "sortlastname" <?php if(isset($_POST['sorted'])){ if( $_POST['sorted'] == 'sortlastname') echo 'selected="selected"';}?>>Last Name</option>
				<option value = "sortdate" <?php if(isset($_POST['sorted'])){ if($_POST['sorted'] == 'sortdate') echo 'selected="selected"';} else echo 'selected = "selected"';?>>Date Uploaded</option>
			</select>
		</form>
		</div>
	</div>
	<div id="main">
	  <div id="mainwrapper">

    <?php
    	//show searched results
      if(isset($_POST["search"]) && $_POST["search"]!= "" && $_SERVER["REQUEST_METHOD"] == "POST"){
      	$searchString = $_POST["search"];
      	$searchArray = explode(',', $searchString);
      	$jsonfile = "galleryinfo.json";
      	//create json if doesn't exist
				if(!file_exists("galleryinfo.json")){
					touch("galleryinfo.json");
					$fileObj = fopen($jsonfile, "w");
					fwrite($fileObj, "[]");
					fclose($fileObj);
				}//if
				$current = file_get_contents($jsonfile);
				$contents = json_decode($current, true);
				$lastname = array();
				$firstname = array();
				$description = array();
				$filename = array();
				$tags = array();
				$found = false;
				if(isset($_POST['sorted'])){
					if($_POST['sorted'] == "sortfirstname"){
						uasort($contents, 'sort_by_first');
					}else if($_POST['sorted'] == "sortlastname"){
						uasort($contents, 'sort_by_last');
					}// else if
				}// if
				foreach ($contents as $content) {
					if($content["isApproved"]){
						if($content["access"] == "public"){
							$sourceArray = explode(',', $content["tags"]);
							$dir = "uploadedimages/";
							foreach($sourceArray as $eachSource){

								foreach ($searchArray as $eachSearch) {

									if($eachSearch == $eachSource){
										array_push($lastname , $content['last_name']);
										array_push($firstname , $content['first_name']);
										array_push($description, $content['description']);
										array_push($tags, $content['tags']);
										array_push($filename, 'uploadedimages/'.$content['filename']);
										echo '
										<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\')">
										<img class = "tile" src = "'.$dir.'thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
										</a>
										';
										$found = true;
										break;
									} // foreach
									if($found) break;
								} // foreach
							} // foreach
						} // if
					} // if
				}//foreach
				//send each arrays into js
				echo'<script>';
				echo'var firstname ='.json_encode($firstname).';';
				echo'var lastname ='.json_encode($lastname).';';
				echo'var description ='.json_encode($description).';';
				echo'var filename ='.json_encode($filename).';';
				echo'var tags ='.json_encode($tags).';';
				echo'</script>';

	    }else{
	      $lastname = array();
				$firstname = array();
				$description = array();
				$filename = array();
				$tags = array();
		    $dir = "uploadedimages/";

				# read galleryinfo.json
				#for each entry
					# get the image url from it
		        	# use it to get the image src for thumbnail
		        	# add new image tag with thumbnail src

	      $jsonfile = "galleryinfo.json";
				if(!file_exists("galleryinfo.json")){
					touch("galleryinfo.json");
					$fileObj = fopen($jsonfile, "w");
					fwrite($fileObj, "[]");
					fclose($fileObj);
				}// if
				$current = file_get_contents($jsonfile);
				$contents = json_decode($current, true);
				if(isset($_POST['sorted'])){
					if($_POST['sorted'] == "sortfirstname"){
						uasort($contents, 'sort_by_first');
					}else if($_POST['sorted'] == "sortlastname"){
						uasort($contents, 'sort_by_last');
					} // else if
				} // if
				//show all public images
				foreach ($contents as $content){
					if($content["isApproved"]){
						if($content["access"] == "public"){
							array_push($lastname , $content['last_name']);
							array_push($firstname , $content['first_name']);
							array_push($description, $content['description']);
							array_push($tags, $content['tags']);
							array_push($filename, 'uploadedimages/'.$content['filename']);
							echo '
							<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\')">
							<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
							</a>
							';
						} // if
					} // if
				} // for each
				//send each arrays into js
				echo'<script>';
				echo'var lastname ='.json_encode($lastname).';';
				echo'var firstname ='.json_encode($firstname).';';
				echo'var description ='.json_encode($description).';';
				echo'var filename ='.json_encode($filename).';';
				echo'var tags ='.json_encode($tags).';';
				echo'</script>';

			} // else
    ?>

	  </div>
	</div>

	<div id = "lightbox" class = "hidden">

	</div>


	<div id = "bigImage" class = "hidden">
	<a href = "javascript: unHideTwo('lightbox', 'bigImage', null)">
	  <img id = "x" src = "close.png" alt = "close" >
	</a>
	<div id = 'imagewrapper'>
	<img id = "imageFile" src = "http://example.org/" alt = "img">
	</div>
	<div id = 'lb_navi'>
	<a href = "javascript: goBack()">
		<img id = "left" src = "left_arrow.png" alt = "Back" >
	</a>
	<a href = "javascript: goNext()">
		<img id = "right" src = "right_arrow.png" alt = "Forward" >
	</a>
	</div>
	<div id = "infosection"></div>

	</div>
