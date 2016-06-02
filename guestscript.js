 //switch visibility of ID
function changeVisibility(divID){
  var element = document.getElementById(divID);
  
  if(element){
    element.className = (element.className == "hidden")?
	                                         'unhidden' : 'hidden';
  }//if
}//changeVisibility

function unHideTwo(divID1, divID2, newSrc, photographer, description){
	if(newSrc != null || photographer != null || description != null){
		document.getElementById("imageFile").setAttribute("src", "uploadedimages/"+newSrc);
		document.getElementById("infosection").innerHTML = "<pre id = 'info'>Photographer: " + photographer+"     " + "Description: " + description+"</pre>";
	}

  	changeVisibility(divID1);
  	changeVisibility(divID2);
}//unHideTwo
function goto (url){
	window.location = url;
}
function goNext(){
	currentShowing = document.getElementById("imageFile").getAttribute("src");

	for(var i = 0; i < filename.length; i++){
		if(filename[i] == currentShowing){
			if((i+1) >= filename.length){
				document.getElementById("imageFile").setAttribute("src", filename[0]);
				document.getElementById("infosection").innerHTML = "<pre id = 'info'>Photographer: " + lastname[0]+"     " + "Description: " + description[0]+"</pre>";
			}
			else{
				document.getElementById("imageFile").setAttribute("src", filename[i+1]);
				document.getElementById("infosection").innerHTML = "<pre id = 'info'>Photographer: " + lastname[i+1]+"     " + "Description: " + description[i+1]+"</pre>";
			}
			
		}
	}
}
function goBack(){
	currentShowing = document.getElementById("imageFile").getAttribute("src");
	for(var i = 0; i < filename.length; i++){
		if(filename[i] == currentShowing){
			if((i-1) < 0){
				document.getElementById("imageFile").setAttribute("src", filename[filename.length-1]);	
				document.getElementById("infosection").innerHTML = "<pre id = 'info'>Photographer: " + lastname[filename.length - 1]+"     " + "Description: " + description[filename.length - 1]+"</pre>";			
			}else{
				document.getElementById("imageFile").setAttribute("src", filename[i-1]);
				document.getElementById("infosection").innerHTML = "<pre id = 'info'>Photographer: " + lastname[i-1]+"     " + "Description: " + description[i-1]+"</pre>";
			}

		}
	}
}