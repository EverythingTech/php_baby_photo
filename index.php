<?php
	session_start();
	$_SESSION['isEditor'] = true;
	date_default_timezone_set("America/Los_Angeles");
	//if logged in
	//show moderator view
	//else
	//show guest view
	if($_SESSION['isEditor']){
		include "moderatorheader.inc";
		include "moderator.inc";
		include "footer.inc";
	}else{
		include "guestheader.inc";		
		include "guest.inc";
		include "footer.inc";
	}

	function sort_by_last($a, $b){
		if(strtolower($a['last_name']) == strtolower($b['last_name'])){
			return 0;
		}//if
		return (strtolower($a['last_name']) < strtolower($b['last_name'])) ? -1:1;
	}
	function sort_by_first($a, $b){
		if(strtolower($a['first_name']) == strtolower($b['first_name'])){
			return 0;
		}//if
		return (strtolower($a['first_name']) < strtolower($b['first_name'])) ? -1:1;
	}
?>