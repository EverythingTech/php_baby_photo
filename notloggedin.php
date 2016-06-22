<?php
	session_start();
	$_SESSION["isEditor"] = false;
	echo '<script type="text/javascript">
           			window.location = "index.php"
      				</script>';
?>