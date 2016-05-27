<h1>Photo Management System</h1>
	<div id = buttonwrapper>
	<button class = "greenAcross" type = "button" onclick = "goto('import.php');">Upload</button>
	<button class = "greenAcross" type = "button" onclick = "goto('waiting-for-approval.php');">Waiting For Approval</button>
	</div>
	<div id = "filterwrapper">
		<h3>Tools</h3>
		<div id = "toolswrapper">
		<h5>Keyword Search: </h5>
		<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post">
			<input type="search" id="search" name = "search" placeholder=<?php if(isset($_POST['search']) && $_POST["search"]!= "") echo '"'.$_POST["search"].'"'; else echo "'Keywords Search...'";?> />    
		</form>
		<h5>Sort By:</h5>
		<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post">
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
	  <a id = "download-all-button" href="downloadzip.php">Download All Images</a>
	  <?php   	
        if(isset($_POST["search"]) && $_POST["search"]!= "" && $_SERVER["REQUEST_METHOD"] == "POST"){
        	$searchString = $_POST["search"];
        	$searchArray = explode(',', $searchString);

        	$jsonfile = "galleryinfo.json";
        	if(!file_exists("galleryinfo.json")){
        		touch("galleryinfo.json");
        		$fileObj = fopen($jsonfile, "w");
        		fwrite($fileObj, "[]");
        		fclose($fileObj);
        	}		
        	$current = file_get_contents($jsonfile);
        	$contents = json_decode($current, true);
        	$found = false;
        	//sorting for search
        	//turns all letters in the array to lower case
			//code
			// Obtain a list of columns
			if(isset($_POST['sorted'])){				
				if($_POST['sorted'] == "sortdate"){
					foreach ($contents as $key => $row) {
						$sortedDate[$key] = $row['time'];
					}
					array_multisort($sortedDate, SORT_ASC, $contents);
				}else if($_POST['sorted'] == "sortfirstname"){
					
					foreach ($contents as $key => $row) {
						$sortedFirstName[$key] = $row['first_name'];
					}
					array_multisort($sortedFirstName, SORT_ASC, $contents);
				}else if($_POST['sorted'] == "sortlastname"){
					foreach ($contents as $key => $row) {
						$sortedLastName[$key] = $row['last_name'];
					}
					array_multisort($sortedLastName, SORT_ASC, $contents);
				}
			}
        	$lastname = array();
        	$description = array();
        	$filename = array();
        	foreach ($contents as $content) {
        		if($content["isApproved"]){
	        		$sourceArray = explode(',', $content["tags"]);
	        		$dir = "uploadedimages/";
	        		foreach($sourceArray as $eachSource){
	        			
	        			foreach ($searchArray as $eachSearch) {

	        				if($eachSearch == $eachSource){

	        					array_push($lastname , $content['last_name']);
	        					array_push($description, $content['description']);
	        					array_push($filename, 'uploadedimages/'.$content['filename']);	
	        					echo '
	        					<div class = "tilewrapper">
					        		<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
					        		<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
					        		</a>
					        		<form action="delete.php" method="post">
					        			<input type = "hidden" name = "fileToDelete" value = "'.$content["filename"].'">
					        			<button class = "individual-delete-button" type="submit">Delete</button>
					        		</form>
					        		<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'">Download</a>

					        		<form method = "post" action = "changejson.php">
					        			<input type = "hidden" name = "filename" value = "'.$content["filename"].'">
					        			<input type = "text" name = "firstname" value = "'.$content["first_name"].'">
					        			<input type = "text" name = "lastname" value = "'.$content["last_name"].'">
					        			<input type = "text" name = "description" value = "'.$content["description"].'">
					        			<input type = "text" name = "tags" value = "'.$content["tags"].'">
					        			<input type = "submit" value = "Save">
					        		</form>
					        		<p id = "timep"> Time: '.$content['time'].'</p>
	        						</div>
	        					';
	        					$found = true;
	        					break;
	        					
	        				}
	        				if($found) break;
	        			}
	        		}	
	        	}
        	}
        	//send each arrays into js
        	echo'<script>';
        	echo'var lastname ='.json_encode($lastname).';';
        	echo'var description ='.json_encode($description).';';
        	echo'var filename ='.json_encode($filename).';';
        	echo'</script>';

        }else{

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
        	}		
        	$current = file_get_contents($jsonfile);
        	$contents = json_decode($current, true);

        	//sorting
        	//turns all letters in the array to lower case
			//code
			// Obtain a list of columns
			if(isset($_POST['sorted'])){				
				if($_POST['sorted'] == "sortdate"){
					foreach ($contents as $key => $row) {
						$sortedDate[$key] = $row['time'];
					}
					array_multisort($sortedDate, SORT_ASC, $contents);
				}else if($_POST['sorted'] == "sortfirstname"){
					
					foreach ($contents as $key => $row) {
						$sortedFirstName[$key] = $row['first_name'];
					}
					array_multisort($sortedFirstName, SORT_ASC, $contents);
				}else if($_POST['sorted'] == "sortlastname"){
					foreach ($contents as $key => $row) {
						$sortedLastName[$key] = $row['last_name'];
					}
					array_multisort($sortedLastName, SORT_ASC, $contents);
				}
			}



        	$lastname = array();
        	$description = array();
        	$filename = array();
        	//show all photos
        	foreach ($contents as $content){	
        		if($content["isApproved"]){
	        		array_push($lastname , $content['last_name']);
	        		array_push($description, $content['description']);
	        		array_push($filename, 'uploadedimages/'.$content['filename']);	
	        		echo '
	        		<div class = "tilewrapper">
	        		<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
	        		<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
	        		</a>
	        		<form action="delete.php" method="post">
	        			<input type = "hidden" name = "fileToDelete" value = "'.$content["filename"].'">
	        			<button class = "individual-delete-button" type="submit">Delete</button>
	        		</form>
	        		<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'">Download</a>

	        		<form method = "post" action = "changejson.php">
	        			<input type = "hidden" name = "filename" value = "'.$content["filename"].'">
	        			<input type = "text" name = "firstname" value = "'.$content["first_name"].'">
	        			<input type = "text" name = "lastname" value = "'.$content["last_name"].'">
	        			<input type = "text" name = "description" value = "'.$content["description"].'">
	        			<input type = "text" name = "tags" value = "'.$content["tags"].'">
	        			<input type = "submit" value = "Save">
	        		</form>
	        		<p id = "timep"> Time: '.$content['time'].'</p>
	        		</div>
	        		';
	        	}
        	}

        	//send each arrays into js
        	echo'<script>';
        	echo'var lastname ='.json_encode($lastname).';';
        	echo'var description ='.json_encode($description).';';
        	echo'var filename ='.json_encode($filename).';';
        	echo'</script>';
        }	
      ?>
	  </div>      
	</div>
	
	<div id = "lightbox" class = "hidden">
	
	</div>
	
	<div id = "centerBigImages">
	  <div id = "bigImage" class = "hidden">
		<a href = "javascript: unHideTwo('lightbox', 'bigImage', null, null, null, null)">
		  <img id = "x" src = "close.png" alt = "close" >
		</a>
		<a href = "javascript: goBack()">Back</a>
		<a href = "javascript: goNext()">Next</a>


		<img id = "imageFile">
		<div id = "infosection"></div>

	  </div>

      
	</div>