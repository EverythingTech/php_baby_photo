<h1>Photo Management System</h1>
	<div id = buttonwrapper>
	<button class = "greenAcross" type = "button" onclick = "goto('import.php');">Upload</button>
	</div>
	<div id = "filterwrapper">
		<h3>Search</h3>
		<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post" enctype="multipart/form-data">
			<input type="search" id="search" name = "search" placeholder=<?php if(isset($_POST['search']) && $_POST["search"]!= "") echo '"'.$_POST["search"].'"'; else echo "'Keywords Search...'";?> />    
		</form>
	</div>
	<div id="main">
	  <div id="mainwrapper">

        <?php 
			echo '<a id = "download-all-button" href="downloadzip.php">Download All Images</a>';
        	
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
				foreach ($contents as $content) {
					
					$sourceArray = explode(',', $content["tags"]);
					$dir = "uploadedimages/";
					foreach($sourceArray as $eachSource){
						
						foreach ($searchArray as $eachSearch) {

							if($eachSearch == $eachSource){
								echo '
								<div class = "tilewrapper">
								<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\',\''.$content["last_name"].'\', \''.$content["description"].'\')">
								<img class = "tile" src = "'.$dir.'thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
								</a>
								<form action="delete.php" method="post">
									<input type = "hidden" name = "fileToDelete" value = "'.$content["filename"].'">
									<button class = "individual-delete-button" type="submit">Delete</button>
								</form>
								<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'">Download</a>

								</div>
								';
								$found = true;
								break;
							}
							if($found) break;
						}
					}
					
				}

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
				//show all photos
				foreach ($contents as $content){		
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

					</div>
					';
					
				}

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
		<img id = "imageFile">
		<div id = "infosection"></div>

	  </div>

      
	</div>