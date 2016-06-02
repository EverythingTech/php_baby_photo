var filesToDelete = new Array();
function init(){
}
//switch visibility of ID
function changeVisibility(divID){
  var element = document.getElementById(divID);
  
  if(element){
    element.className = (element.className == "hidden")?
	                                         'unhidden' : 'hidden';
  }//if
}//changeVisibility

function unHideTwo(divID1, divID2, newSrc){
	currentShowing = "uploadedimages/" + newSrc;
	if(newSrc != null || divID1 != null || divID2 != null){	
		
		for(var i = 0; i < filename.length; i++){
			if(filename[i] == currentShowing){
				document.getElementById("lb_download_url").setAttribute("href", filename[i]);	
				document.getElementById("lb_download_url").setAttribute("download", newSrc);	
				document.getElementById("imageFile").setAttribute("src", filename[i]);		
				document.getElementById("basic_info").innerHTML = "<pre id = 'info'>Photographer: " + lastname[i]+"     " + "Description: " + description[i] +"</pre>";
				
			}
		}
	}

  	changeVisibility(divID1);
  	changeVisibility(divID2);
}//unHideTwo

function goto (url){
	window.location = url;
}

function deleteThis(fileName){
    var r = confirm("Are you sure you want to delete this Image?");
    if(r == true){
    	//deletes the file from /uploadedimages
    	//deletes json entry
    	//deletes thumb file
        $.ajax({
          url: 'delete.php',
          data: {'filedir' : "<?php echo dirname(__FILE__) . 'uploadedimages/'?>" + fileName, 'file': fileName},
        }); 
    }
}

function goNext(){
	currentShowing = document.getElementById("imageFile").getAttribute("src");

	for(var i = 0; i < filename.length; i++){
		if(filename[i] == currentShowing){
			if((i+1) >= filename.length){
				document.getElementById("lb_download_url").setAttribute("href", filename[0]);
				document.getElementById("lb_download_url").setAttribute("download", ((filename[0]).split('/'))[1]);		
				document.getElementById("imageFile").setAttribute("src", filename[0]);
				document.getElementById("basic_info").innerHTML = "<pre id = 'info'>Photographer: " + lastname[0]+"     " + "Description: " + description[0]+"</pre>";
			}
			else{
				document.getElementById("lb_download_url").setAttribute("href", filename[i+1]);
				document.getElementById("lb_download_url").setAttribute("download", ((filename[i+1]).split('/'))[1]);	
				document.getElementById("imageFile").setAttribute("src", filename[i+1]);
				document.getElementById("basic_info").innerHTML = "<pre id = 'info'>Photographer: " + lastname[i+1]+"     " + "Description: " + description[i+1]+"</pre>";
			}
			
		}
	}
}

function goBack(){
	currentShowing = document.getElementById("imageFile").getAttribute("src");
	for(var i = 0; i < filename.length; i++){
		if(filename[i] == currentShowing){
			if((i-1) < 0){
				document.getElementById("lb_download_url").setAttribute("href", filename[filename.length-1]);
				document.getElementById("lb_download_url").setAttribute("download", (filename[filename.length-1]).split('/')[1]);
				document.getElementById("imageFile").setAttribute("src", filename[filename.length-1]);	
				document.getElementById("basic_info").innerHTML = "<pre id = 'info'>Photographer: " + lastname[filename.length-1]+"     " + "Description: " + description[filename.length-1]+"</pre>";			
			}else{
				document.getElementById("lb_download_url").setAttribute("href", filename[i-1]);
				document.getElementById("lb_download_url").setAttribute("download", filename[i-1].split('/')[1]);
				document.getElementById("imageFile").setAttribute("src", filename[i-1]);
				document.getElementById("basic_info").innerHTML = "<pre id = 'info'>Photographer: " + lastname[i-1]+"     " + "Description: " + description[i-1]+"</pre>";
			}

		}
	}
}
function addToDelete(src){
	if(document.getElementById(src).style.opacity == '0.4'){
		for(var i = 0; i < filesToDelete.length; i++){
			if(filesToDelete[i] == src){
				filesToDelete.splice(i, 1);
			}
		}
		document.getElementById(src).style.opacity = '1';
	}
	else{
		filesToDelete.push(src);
		document.getElementById(src).style.opacity = '0.4';
	}
}
