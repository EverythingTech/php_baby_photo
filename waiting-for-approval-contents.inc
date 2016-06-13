<h1>Waiting For Approval</h1>
<div id="main">
	  <div id="mainwrapper">
	  <a id = "view-gallery-waiting-view" href="index.php">View Gallery</a>
      <a id = "download-all-button" href="approve.php">Approve All</a>
	  <?php
					//sets default directory
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

					//gets json contents
        	$current = file_get_contents($jsonfile);
        	$contents = json_decode($current, true);

        	$firstname = array();
          $tags = array();
          $lastname = array();
          $description = array();
          $filename = array();

        	//show all photos
        	foreach ($contents as $content){
						//show images that are not approved
            if(!$content['isApproved']){
	        		array_push($firstname , $content['first_name']);
	            array_push($tags , $content['tags']);
	            array_push($lastname , $content['last_name']);
	            array_push($description, $content['description']);
	            array_push($filename, 'uploadedimages/'.$content['filename']);

	        		echo '
	        		<div class = "tilewrapper">
	        		<a href = "javascript: unHideTwo(\'lightbox\', \'bigImage\', \''.$content["filename"].'\')">
	        		<img class = "tile" src = "'.$dir.'/thumb/'.$content["filename"].'" alt = "'.$content["filename"].'">
	        		</a>
	        		<form action="approve.php" method="post" class = "individual-approve-form">
	        			<input type = "hidden" name = "fileToApprove" value = "'.$content["filename"].'">
	        			<button class = "individual-approve-button" type="submit">Approve</button>
	        		</form>
	                <form action="delete.php" method="post" class = "individual-deny-form">
	                    <input type = "hidden" name = "fileToDelete" value = "'.$content["filename"].'">
	                    <button class = "individual-deny-button" type="submit">Deny</button>
	                </form>
	        		<a href="'.$dir.$content["filename"].'" download="'.$content["filename"].'" class = "individual-download-wait">Download</a>
	                <p class = "timep"> Uploaded: '.date("F j, Y, g:i a", $content['time']).'</p>
	        		</div>
	        		';
            }// if
        	}//foreach


        	//send each arrays into js
        	echo'<script>';
            echo'var firstname ='.json_encode($firstname).';';
            echo'var tags ='.json_encode($tags).';';
            echo'var lastname ='.json_encode($lastname).';';
            echo'var description ='.json_encode($description).';';
            echo'var filename ='.json_encode($filename).';';
            echo'</script>';
      ?>
	  </div>


	<div id = "lightbox" class = "hidden">

  </div>


    <div id = "bigImage"  class = "hidden">
    <a id = 'lb_download_url'>
        <img id = "download-button" src = "download.png" alt = "download" >
    </a>
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
