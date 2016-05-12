<?php

	$isEditor = false;
	if($isEditor){
		include "moderatorheader.inc";
		include "moderator.inc";
		include "footer.inc";
	}else{
		include "guestheader.inc";		
		include "guest.inc";
		include "footer.inc";
	}
?>