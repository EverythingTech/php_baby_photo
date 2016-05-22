<h1>Waiting For Approval</h1>
<div id="main">
	  <div id="mainwrapper">
	  <a id = "view-gallery-waiting-view" href="index.php">View Gallery</a>
      <a id = "download-all-button" href="approve.php">Approve All</a>
	  <?php   	
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

        	$name = array();
        	$description = array();
        	$filename = array();

        	//show all photos
        	foreach ($contents as $content){	
                if(!$content['isApproved']){
            		array_push($name , $content['last_name']);
            		array_push($description, $content['description']);
            		array_push($filename, 'uploadedimages/'.$content['filename']);	
            		echo '
            		<div class = "tilewrapper">
            		<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\', \''.$content["last_name"].'\', \''.$content["description"].'\')">
            		<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
            		</a>
            		<form action="approve.php" method="post">
            			<input type = "hidden" name = "fileToApprove" value = "'.$content["filename"].'">
            			<button class = "individual-approve-button" type="submit">Approve</button>
            		</form>
            		<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'">Download</a>

            		</div>
            		';
                }
        	}

        	//send each arrays into js
        	echo'<script>';
        	echo'var name ='.json_encode($name).';';
        	echo'var description ='.json_encode($description).';';
        	echo'var filename ='.json_encode($filename).';';
        	echo'</script>';   
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