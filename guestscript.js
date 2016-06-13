 //switch visibility of ID
 function changeVisibility(divID) {
     var element = document.getElementById(divID);

     if (element) {
         element.className = (element.className == "hidden") ?
             'unhidden' : 'hidden';
     } //if
 } //changeVisibility

 //unhide lightbox, show image
 function unHideTwo(divID1, divID2, newSrc) {
   currentShowing = "uploadedimages/" + newSrc;
   if (newSrc != null) {
     for (var i = 0; i < filename.length; i++) {
       if (filename[i] == currentShowing) {
         document.getElementById("imageFile").setAttribute("src", "uploadedimages/" + newSrc);
         document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + firstname[i] + " "+lastname[i]+ "</p><p class = 'info'>" + "Description: " + description[i] + "</p><p class = 'info'>" + "Tags: " + tags[i] + "</p>";
       }
     }

   } // if

     changeVisibility(divID1);
     changeVisibility(divID2);
 } //unHideTwo

 // go to url
 function goto(url) {
     window.location = url;
 }// goto

 // go to next image in lightbox
 function goNext() {
     currentShowing = document.getElementById("imageFile").getAttribute("src");

     for (var i = 0; i < filename.length; i++) {
         if (filename[i] == currentShowing) {
             if ((i + 1) >= filename.length) {
                 document.getElementById("imageFile").setAttribute("src", filename[0]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + firstname[0] + " "+lastname[0]+ "</p><p class = 'info'>" + "Description: " + description[0] + "</p><p class = 'info'>" + "Tags: " + tags[0] + "</p>";
             } else {
                 document.getElementById("imageFile").setAttribute("src", filename[i + 1]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + firstname[i+1] + " "+lastname[i+1]+ "</p><p class = 'info'>" + "Description: " + description[i+1] + "</p><p class = 'info'>" + "Tags: " + tags[i+1] + "</p>";
             } // else

         } // if
     } // for
 } // goNext

 // go to previous image in lightbox
 function goBack() {
     currentShowing = document.getElementById("imageFile").getAttribute("src");
     for (var i = 0; i < filename.length; i++) {
         if (filename[i] == currentShowing) {
             if ((i - 1) < 0) {
                 document.getElementById("imageFile").setAttribute("src", filename[filename.length - 1]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + firstname[filename.length - 1] + " "+lastname[filename.length - 1]+ "</p><p class = 'info'>" + "Description: " + description[filename.length - 1] + "</p><p class = 'info'>" + "Tags: " + tags[filename.length - 1] + "</p>";
             } else {
                 document.getElementById("imageFile").setAttribute("src", filename[i - 1]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + firstname[i-1] + " "+lastname[i-1]+ "</p><p class = 'info'>" + "Description: " + description[i-1] + "</p><p class = 'info'>" + "Tags: " + tags[i-1] + "</p>";
             } // else

         } // if
     } // for
 } // goBack
