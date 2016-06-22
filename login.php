<?php
	session_start();
	$_SESSION["isEditor"] = true;
	echo '<script type="text/javascript">
           			window.location = "index.php"
      				</script>';
?>