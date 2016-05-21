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
			include 'moderator-gallery.inc';
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