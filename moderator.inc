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
		
			files_to_zip = array(
				'0.jpg',
				'1.jpg',
				'2.jpg',
				'3.jpg',
				'4.jpg',
				'5.jpg'
			);
			//if true, good; if false, zip creation failed
			$result = create_zip($files_to_zip,'photos.zip');

			echo '<a href="photos.zip" download="photos.zip">Hello</a>';
        	//echo var_dump($_POST);
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
								<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\',\''.$content["last_name"].'\', \''.$content["description"].'\')">
								<img class = "tile" src = "'.$dir.'thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
								</a>
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
					<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
					<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
					</a>
					';
					
				}
				
				//show private photos
				/*
				if($_SERVER["REQUEST_METHOD"] == "POST"){
					
					foreach ($contents as $content){
						if($content["access"] == "private"){
							echo '
							<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
							<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
							</a>
							';
						}
					}
				}*/
			}
			
			
			/* creates a compressed zip file */
			function create_zip($files = array(),$destination = '',$overwrite = false) {
				//if the zip file already exists and overwrite is false, return false
				if(file_exists($destination) && !$overwrite) { return false; }
				//vars
				$valid_files = array();
				//if files were passed in...
				if(is_array($files)) {
					//cycle through each file
					foreach($files as $file) {
						//make sure the file exists
						if(file_exists($file)) {
							$valid_files[] = $file;
						}
					}
				}
				//if we have good files...
				if(count($valid_files)) {
					//create the archive
					$zip = new ZipArchive();
					if($zip->open($destination,$overwrite ? ZIPARCHIVE::OVERWRITE : ZIPARCHIVE::CREATE) !== true) {
						return false;
					}
					//add the files
					foreach($valid_files as $file) {
						$zip->addFile($file,$file);
					}
					//debug
					//echo 'The zip archive contains ',$zip->numFiles,' files with a status of ',$zip->status;
					
					//close the zip -- done!
					$zip->close();
					
					//check to make sure the file exists
					return file_exists($destination);
				}
				else
				{
					return false;
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