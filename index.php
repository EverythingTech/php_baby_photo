<?php
	session_start();
	date_default_timezone_set("America/Los_Angeles");
	//if logged in
	//show moderator view
	//else
	//show guest view
	if(empty($_SESSION['isEditor'])){
		$_SESSION["isEditor"] = false;
	} // if
	if($_SESSION['isEditor']){
		include "moderatorheader.inc";
		include "moderator.inc";
		include "footer.inc";
	}else{
		include "guestheader.inc";
		include "guest.inc";
		include "footer.inc";
	} // else

	//custom seach for last name
	function sort_by_last($a, $b){
		if(strtolower($a['last_name']) == strtolower($b['last_name'])){
			return 0;
		}//if
		return (strtolower($a['last_name']) < strtolower($b['last_name'])) ? -1:1;
	} // sort_by_last

	//custom search for first name
	function sort_by_first($a, $b){
		if(strtolower($a['first_name']) == strtolower($b['first_name'])){
			return 0;
		}//if
		return (strtolower($a['first_name']) < strtolower($b['first_name'])) ? -1:1;
	} // sort_by_first
?>
