<?php
	session_start();
	if($_SESSION['isEditor']){
		include 'moderatorheader.inc';
		include 'waiting-for-approval-contents.inc';
		include 'footer.inc';
	}
?>