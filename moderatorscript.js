var access = "public";
//switch visibility of ID
function changeVisibility(divID){
  var element = document.getElementById(divID);
  
  if(element){
    element.className = (element.className == "hidden")?
	                                         'unhidden' : 'hidden';
  }//if
}//changeVisibility

function unHideTwo(divID1, divID2, newSrc, photographer, description){
	if(newSrc != null || access != null || photographer != null || description != null){
		
		document.getElementById("imageFile").setAttribute("src", "uploadedimages/"+newSrc);
		document.getElementById("imageFile").setAttribute("width", "900px");
		document.getElementById("imageFile").setAttribute("height", "600px");
		document.getElementById("infosection").innerHTML = "<pre>Photographer: " + photographer+"     " + "Description: " + description+"</pre>";
	}

  	changeVisibility(divID1);
  	changeVisibility(divID2);
}//unHideTwo

function goto (url){
	window.location = url;
}

function privateEnable(){
	if (access == "public") access = "private";
	else access = "public";


}