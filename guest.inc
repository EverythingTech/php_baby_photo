<h1>Gallery</h1>
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
				$name = array();
				$description = array();
				$filename = array();
				$found = false;
				foreach ($contents as $content) {
					if($content["access"] == "public"){
						$sourceArray = explode(',', $content["tags"]);
						$dir = "uploadedimages/";
						foreach($sourceArray as $eachSource){
							
							foreach ($searchArray as $eachSearch) {

								if($eachSearch == $eachSource){
									array_push($name , $content['last_name']);
									array_push($description, $content['description']);
									array_push($filename, 'uploadedimages/'.$content['filename']);	
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
				}
				//send each arrays into js
				echo'<script>';
				echo'var name ='.json_encode($name).';';
				echo'var description ='.json_encode($description).';';
				echo'var filename ='.json_encode($filename).';';
				echo'</script>';

	        }else{
	        	$name = array();
				$description = array();
				$filename = array();
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
				
				//show all public images
				foreach ($contents as $content){
					if($content["access"] == "public"){
						array_push($name , $content['last_name']);
						array_push($description, $content['description']);
						array_push($filename, 'uploadedimages/'.$content['filename']);	
						echo '
						<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
						<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
						</a>
						';
					}
				}
				//send each arrays into js
				echo'<script>';
				echo'var name ='.json_encode($name).';';
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