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
				document.getElementById("imageFile").setAttribute("src", filename[0]);
			}
			else{document.getElementById("imageFile").setAttribute("src", filename[i+1]);}
			
		}
	}
}
function goBack(){
	currentShowing = document.getElementById("imageFile").getAttribute("src");
	for(var i = 0; i < filename.length; i++){
		if(filename[i] == currentShowing){
			if((i-1) < 0){
				document.getElementById("imageFile").setAttribute("src", filename[filename.length-1]);				
			}else{
				document.getElementById("imageFile").setAttribute("src", filename[i-1]);
			}

		}
	}
}