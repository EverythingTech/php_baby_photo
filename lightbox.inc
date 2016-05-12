<h1>Gallery</h1>
	<div id = buttonwrapper>
	<button class = "greenAcross" type = "button" onclick = "goto('import.php');">Upload</button>
	</div>
	<div id = "filterwrapper">
		<h3>Filter</h3>
		<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post" enctype="multipart/form-data">
			<input type="search" id="search" name = "search" placeholder=<?php if(isset($_POST['search']) && $_POST["search"]!= "") echo '"'.$_POST["search"].'"'; else echo "'Keywords Search...'";?> />
		    <input type="radio" value="public" name="access" 
		    <?php if (isset($_POST["access"]) && $_POST["access"]=="public") echo "checked";
		    if(!isset($_POST["access"])) echo "checked";?>>
		    <label>Public</label>
		    <input type="radio" value="private" name="access" 
		    <?php if (isset($_POST["access"]) && $_POST["access"]=="private") echo "checked";?>>
		    <label>All Images</label>
		    <button id = "filterButton" type="submit">Filter</button>
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
				$found = false;
				foreach ($contents as $content) {
					$sourceArray = explode(',', $content["tags"]);
					$dir = "uploadedimages/".$content["access"];
					foreach($sourceArray as $eachSource){
						
						foreach ($searchArray as $eachSearch) {

							if($eachSearch == $eachSource){
								echo '
								<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["access"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
								<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
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

		        $dir = "uploadedimages/public/";

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
				
				foreach ($contents as $content){
					if($content["access"] == "public"){
						echo '
						<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \'public\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
						<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
						</a>
						';
					}
				}
				
				if($_SERVER["REQUEST_METHOD"] == "POST" && $_POST["access"] == "private"){
					$dir = "uploadedimages/private/";
					foreach ($contents as $content){
						if($content["access"] == "private"){
							echo '
							<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \'private\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
							<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
							</a>
							';
						}
					}
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