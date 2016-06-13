<h1>Photo Management System</h1>
	<div id = buttonwrapper>
	<!-- Navigation Bar--> 
	<button class = "greenAcross" type = "button" onclick = "goto('import.php');">Upload</button>
	<button class = "greenAcross" type = "button" onclick = "goto('waiting-for-approval.php');">Waiting For Approval</button>
	</div>
	<!-- Search Bar --> 
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

	<!-- Download and Delete all buttons--> 
	</div>
	<div id="main">
		<div id="mainwrapper">
			<form action = 'delete-selected.php' method = "post" id = "delete-selected-form">
				<input id = "delete-selected-button" type = 'submit' value = "Delete Selected" disabled>
			</form>
			<a id = "download-all-button" href="downloadzip.php">Download All Images</a>
			
			<?php   
				// if users searches something
				if(isset($_POST["search"]) && $_POST["search"]!= "" && $_SERVER["REQUEST_METHOD"] == "POST"){
					$searchString = $_POST["search"];
					$searchArray = explode(',', $searchString);

					//opens or creates json file
					$jsonfile = "galleryinfo.json";
					if(!file_exists("galleryinfo.json")){
						touch("galleryinfo.json");
						$fileObj = fopen($jsonfile, "w");
						fwrite($fileObj, "[]");
						fclose($fileObj);
					} // if		
					$current = file_get_contents($jsonfile);
					$contents = json_decode($current, true);
					$found = false;
					//sorting for search
					//turns all letters in the array to lower case
					//code
					// Obtain a list of columns
					if(isset($_POST['sorted'])){	
						if($_POST['sorted'] == "sortfirstname"){
							uasort($contents, 'sort_by_first');
						}else if($_POST['sorted'] == "sortlastname"){					
							uasort($contents, 'sort_by_last');
						} // else if
					} // if
					//creates arrays of info to send to javascript
					$firstname = array();
					$tags = array();
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
										// adds information to the arrays
										array_push($firstname , $content['first_name']);
										array_push($tags , $content['tags']);
										array_push($lastname , $content['last_name']);
										array_push($description, $content['description']);
										array_push($filename, 'uploadedimages/'.$content['filename']);	
										//prints out gallery module
										echo '
										<div class = "tilewrapper">
										<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\')">
										<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'" id = "'.$content["filename"].'">
										</a>
										
										<form action="delete.php" method="post" class = "deleteform">
											<input type = "hidden" name = "fileToDelete" value = "'.$content["filename"].'">
											<button class = "individual-delete-button" type="submit" >Delete</button>
											<input class = "individual-delete-checkbox" type="checkbox" name="deleteCheck" onchange = "addToDelete(\''.$content['filename'].'\')">
										</form>

										<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'" class = "individual-download-button">Download</a>
										<div class = "individual-textbox-wrapper">
										<div class = "individual-textbox-header">
										<ul class = "individual-textbox-header-ul">
										<li>First Name</li>
										<li>Last Name</li>
										<li>Description</li>
										<li>Tags</li>
										</ul>
										</div>
										<form method = "post" action = "changejson.php" class = "individual-textbox-form">
											<input type = "hidden" name = "filename" value = "'.$content["filename"].'">
											<input class = "individual-textbox" type = "text" name = "firstname" value = "'.htmlspecialchars($content["first_name"]).'">
											<input class = "individual-textbox" type = "text" name = "lastname" value = "'.htmlspecialchars($content["last_name"]).'">
											<input class = "individual-textbox" type = "text" name = "description" value = "'.htmlspecialchars($content["description"]).'">
											<input class = "individual-textbox" type = "text" name = "tags" value = "'.htmlspecialchars($content["tags"]).'">
											<input type = "submit" value = "Save">
										</form>
										</div>
										<p class = "timep"> Uploaded: '.date("F j, Y, g:i a", $content['time']).'</p>
										</div>
										';
										$found = true;
										break;
										
									} // if
									if($found) break;
								} // foreach
							} // for each	
						} // if
					} // foreach
					//send each arrays into javascript
					echo'<script>';
					echo'var firstname ='.json_encode($firstname).';';
					echo'var tags ='.json_encode($tags).';';
					echo'var lastname ='.json_encode($lastname).';';
					echo'var description ='.json_encode($description).';';
					echo'var filename ='.json_encode($filename).';';
					echo'</script>';

				}else{
					// if users doesn't search
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
					} // if		
					$current = file_get_contents($jsonfile);
					$contents = json_decode($current, true);

					//sorting
					// Obtain a list of columns
					if(isset($_POST['sorted'])){	

						if($_POST['sorted'] == "sortfirstname"){
							uasort($contents, 'sort_by_first');
						}else if($_POST['sorted'] == "sortlastname"){					
							uasort($contents, 'sort_by_last');
						} // else if
					} // if

					// creates array of information to send to javascript
					$firstname = array();
					$tags = array();
					$lastname = array();
					$description = array();
					$filename = array();
					//show all photos
					foreach ($contents as $content){	
						if($content["isApproved"]){
							array_push($firstname , $content['first_name']);
							array_push($tags , $content['tags']);
							array_push($lastname , $content['last_name']);
							array_push($description, $content['description']);
							array_push($filename, 'uploadedimages/'.$content['filename']);	
							echo '
							<div class = "tilewrapper">
							<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\')">
							<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'" id = "'.$content["filename"].'">
							</a>
							
							<form action="delete.php" method="post" class = "deleteform">
								<input type = "hidden" name = "fileToDelete" value = "'.$content["filename"].'">
								<button class = "individual-delete-button" type="submit" >Delete</button>
								<input class = "individual-delete-checkbox" type="checkbox" name="deleteCheck" onchange = "addToDelete(\''.$content['filename'].'\')">
							</form>

							<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'" class = "individual-download-button">Download</a>
							<div class = "individual-textbox-wrapper">
							<div class = "individual-textbox-header">
							<ul class = "individual-textbox-header-ul">
							<li>First Name</li>
							<li>Last Name</li>
							<li>Description</li>
							<li>Tags</li>
							</ul>
							</div>
							<form method = "post" action = "changejson.php" class = "individual-textbox-form">
								<input type = "hidden" name = "filename" value = "'.$content["filename"].'">
								<input class = "individual-textbox" type = "text" name = "firstname" value = "'.htmlspecialchars($content["first_name"]).'">
								<input class = "individual-textbox" type = "text" name = "lastname" value = "'.htmlspecialchars($content["last_name"]).'">
								<input class = "individual-textbox" type = "text" name = "description" value = "'.htmlspecialchars($content["description"]).'">
								<input class = "individual-textbox" type = "text" name = "tags" value = "'.htmlspecialchars($content["tags"]).'">
								<input type = "submit" value = "Save">
							</form>
							</div>
							<p class = "timep"> Uploaded: '.date("F j, Y, g:i a", $content['time']).'</p>
							</div>
							';
						} // if
					} // foreach

					//send each arrays into javascript
					echo'<script>';
					echo'var firstname ='.json_encode($firstname).';';
					echo'var tags ='.json_encode($tags).';';
					echo'var lastname ='.json_encode($lastname).';';
					echo'var description ='.json_encode($description).';';
					echo'var filename ='.json_encode($filename).';';
					echo'</script>';
				} // else	
			  ?>
	  </div>      
	</div>
	
	<!-- the light box--> 
	<div id = "lightbox" class = "hidden">
	
	</div>
	
	
  	<div id = "bigImage"  class = "hidden">
  	<!-- download button--> 
	<a id = 'lb_download_url'>
  		<img id = "download-button" src = "download.png" alt = "download" >
  	</a>
	<!-- close button--> 
	<a href = "javascript: unHideTwo('lightbox', 'bigImage', null)">
		<img id = "x" src = "close.png" alt = "close" >
	</a>
	<!-- the image--> 
	<div id = 'imagewrapper'>
	<img id = "imageFile" src = "http://example.org/" alt = "img">
	</div>
	<!-- Back and Next buttons--> 
	<div id = 'lb_navi'>
	<a href = "javascript: goBack()">
		<img id = "left" src = "left_arrow.png" alt = "Back" >
	</a>
	<a href = "javascript: goNext()">
		<img id = "right" src = "right_arrow.png" alt = "Forward" >
	</a>
	</div>
	<!-- Text fields to change the json file--> 
	<div id = "infosection">
		<div id = 'basic_info'></div>
		<div id = 'lb_tools'>
			
			<form method = "post" action = "changejson.php" id = "lb-textbox-form">
				<input type = "hidden" name = "filename" id="lbfilename" value = "">
				<ul id = "lb-textbox-header-ul-left">
	        		<li>First Name</li>
	        		<li>Last Name</li>
	        	</ul>
				<div id = "lb-textbox-left">
				<input class = "lb-individual-textbox" type = "text" name = "firstname" id="lbfirstname" value = "">
				<input class = "lb-individual-textbox" type = "text" name = "lastname" id="lblastname" value = "">
				</div>
				<ul id = "lb-textbox-header-ul-right">
	        		<li>Description</li>
	        		<li>Tags</li>
	        	</ul>
				<div id = "lb-textbox-right">
				<input class = "lb-individual-textbox" type = "text" name = "description" id="lbdescription" value = "">
				<input class = "lb-individual-textbox" type = "text" name = "tags" id="lbtags" value = "">
				</div>
				<input id = "lb-individual-submit" type = "submit" value = "Save">
			</form>
		</div>
	</div>
      
	</div>