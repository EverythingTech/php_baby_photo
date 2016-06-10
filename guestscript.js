 //switch visibility of ID
 function changeVisibility(divID) {
     var element = document.getElementById(divID);

     if (element) {
         element.className = (element.className == "hidden") ?
             'unhidden' : 'hidden';
     } //if
 } //changeVisibility

 function unHideTwo(divID1, divID2, newSrc, photographer, description) {
     if (newSrc != null || photographer != null || description != null) {
         document.getElementById("imageFile").setAttribute("src", "uploadedimages/" + newSrc);
         document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + photographer + "</p><p class = 'info'>" + "Description: " + description + "</p>";
     }

     changeVisibility(divID1);
     changeVisibility(divID2);
 } //unHideTwo
 function goto(url) {
     window.location = url;
 }

 function goNext() {
     currentShowing = document.getElementById("imageFile").getAttribute("src");

     for (var i = 0; i < filename.length; i++) {
         if (filename[i] == currentShowing) {
             if ((i + 1) >= filename.length) {
                 document.getElementById("imageFile").setAttribute("src", filename[0]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + lastname[0] + "</p><p class = 'info'>" + "Description: " + description[0] + "</p>";
             } else {
                 document.getElementById("imageFile").setAttribute("src", filename[i + 1]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + lastname[i + 1] + "</p><p class = 'info'>" + "Description: " + description[i + 1] + "</p>";
             }

         }
     }
 }

 function goBack() {
     currentShowing = document.getElementById("imageFile").getAttribute("src");
     for (var i = 0; i < filename.length; i++) {
         if (filename[i] == currentShowing) {
             if ((i - 1) < 0) {
                 document.getElementById("imageFile").setAttribute("src", filename[filename.length - 1]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + lastname[filename.length - 1] + "</p><p class = 'info'>" + "Description: " + description[filename.length - 1] + "</p>";
             } else {
                 document.getElementById("imageFile").setAttribute("src", filename[i - 1]);
                 document.getElementById("infosection").innerHTML = "<p class = 'info'>Photographer: " + lastname[i - 1] + "</p><p class = 'info'>" + "Description: " + description[i - 1] + "</p>";
             }

         }
     }
 }
