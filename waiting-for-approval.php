<?php
	session_start();
	//set timezone
	date_default_timezone_set("America/Los_Angeles");
	if($_SESSION['isEditor']){
		include 'moderatorheader.inc';
		include 'waiting-for-approval-contents.inc';
		include 'footer.inc';
	}//if
?>