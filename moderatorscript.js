//index for delete form
var deleteFormIndex = 0;


//switch visibility of ID
function changeVisibility(divID) {
    var element = document.getElementById(divID);

    if (element) {
        element.className = (element.className == "hidden") ?
            'unhidden' : 'hidden';
    } //if
} //changeVisibility

//show lightbox
function unHideTwo(divID1, divID2, newSrc) {
    currentShowing = "uploadedimages/" + newSrc;
    if (newSrc != null || divID1 != null || divID2 != null) {

        for (var i = 0; i < filename.length; i++) {
            if (filename[i] == currentShowing) {
                document.getElementById("lbfilename").setAttribute("value", ((filename[i]).split('/'))[1]);
                document.getElementById("lbfirstname").setAttribute("value", firstname[i]);
                document.getElementById("lblastname").setAttribute("value", lastname[i]);
                document.getElementById("lbdescription").setAttribute("value", description[i]);
                document.getElementById("lbtags").setAttribute("value", tags[i]);
                document.getElementById("lb_download_url").setAttribute("href", filename[i]);
                document.getElementById("lb_download_url").setAttribute("download", newSrc);
                document.getElementById("imageFile").setAttribute("src", filename[i]);
                document.getElementById("basic_info").innerHTML = "<p class = 'info'>Photographer: " + firstname[i] + " " + lastname[i] + "</p><p class = 'info'>" + "Description: " + description[i] + "</p>";

            }// if
        }//for
    }//if

    changeVisibility(divID1);
    changeVisibility(divID2);
} //unHideTwo

//take user to a webpage
function goto(url) {
    window.location = url;
}//goto

//go to next image in lightbox
function goNext() {
    currentShowing = document.getElementById("imageFile").getAttribute("src");

    for (var i = 0; i < filename.length; i++) {
        if (filename[i] == currentShowing) {
            if ((i + 1) >= filename.length) {
                document.getElementById("lbfilename").setAttribute("value", ((filename[0]).split('/'))[1]);
                document.getElementById("lbfirstname").setAttribute("value", firstname[0]);
                document.getElementById("lblastname").setAttribute("value", lastname[0]);
                document.getElementById("lbdescription").setAttribute("value", description[0]);
                document.getElementById("lbtags").setAttribute("value", tags[0]);

                document.getElementById("lb_download_url").setAttribute("href", filename[0]);
                document.getElementById("lb_download_url").setAttribute("download", ((filename[0]).split('/'))[1]);
                document.getElementById("imageFile").setAttribute("src", filename[0]);
                document.getElementById("basic_info").innerHTML = "<p class='info'>Photographer: " + firstname[0] + " " + lastname[0] + "</p><p class='info'>" + "Description: " + description[0] + "</p>";
            } else {
                document.getElementById("lbfilename").setAttribute("value", ((filename[i + 1]).split('/'))[1]);
                document.getElementById("lbfirstname").setAttribute("value", firstname[i + 1]);
                document.getElementById("lblastname").setAttribute("value", lastname[i + 1]);
                document.getElementById("lbdescription").setAttribute("value", description[i + 1]);
                document.getElementById("lbtags").setAttribute("value", tags[i + 1]);
                document.getElementById("lb_download_url").setAttribute("href", filename[i + 1]);
                document.getElementById("lb_download_url").setAttribute("download", ((filename[i + 1]).split('/'))[1]);
                document.getElementById("imageFile").setAttribute("src", filename[i + 1]);
                document.getElementById("basic_info").innerHTML = "<p class='info'>Photographer: " + firstname[i + 1] + " " + lastname[i + 1] + "</p><p class='info'>" + "Description: " + description[i + 1] + "</p>";
            } // if else
        }//if
    }//for
}//goNext

// go to previous image in lightbox
function goBack() {
    currentShowing = document.getElementById("imageFile").getAttribute("src");
    for (var i = 0; i < filename.length; i++) {
        if (filename[i] == currentShowing) {
            if ((i - 1) < 0) {
                document.getElementById("lbfilename").setAttribute("value", ((filename[filename.length - 1]).split('/'))[1]);
                document.getElementById("lbfirstname").setAttribute("value", firstname[filename.length - 1]);
                document.getElementById("lblastname").setAttribute("value", lastname[filename.length - 1]);
                document.getElementById("lbdescription").setAttribute("value", description[filename.length - 1]);
                document.getElementById("lbtags").setAttribute("value", tags[filename.length - 1]);
                document.getElementById("lb_download_url").setAttribute("href", filename[filename.length - 1]);
                document.getElementById("lb_download_url").setAttribute("download", (filename[filename.length - 1]).split('/')[1]);
                document.getElementById("imageFile").setAttribute("src", filename[filename.length - 1]);
                document.getElementById("basic_info").innerHTML = "<p class='info'>Photographer: " + firstname[filename.length - 1] + " " + lastname[filename.length - 1] + "</p><p class='info'>" + "Description: " + description[filename.length - 1] + "</p>";
            } else {
                document.getElementById("lbfilename").setAttribute("value", ((filename[i - 1]).split('/'))[1]);
                document.getElementById("lbfirstname").setAttribute("value", firstname[i - 1]);
                document.getElementById("lblastname").setAttribute("value", lastname[i - 1]);
                document.getElementById("lbdescription").setAttribute("value", description[i - 1]);
                document.getElementById("lbtags").setAttribute("value", tags[i - 1]);
                document.getElementById("lb_download_url").setAttribute("href", filename[i - 1]);
                document.getElementById("lb_download_url").setAttribute("download", filename[i - 1].split('/')[1]);
                document.getElementById("imageFile").setAttribute("src", filename[i - 1]);
                document.getElementById("basic_info").innerHTML = "<p class='info'>Photographer: " + firstname[i - 1] + " " + lastname[i - 1] + "</p><p class='info'>" + "Description: " + description[i - 1] + "</p>";
            } // if else

        }//if
    } // for
} //goBack

//add filenames of files to delete to html form
function addToDelete(src) {
    var formContents = document.getElementById('delete-selected-form').innerHTML;
    if (document.getElementById(src).style.opacity == '0.4') {
        var id = "remove" + src;
        var child = document.getElementById(id);
        child.parentNode.removeChild(child);

        deleteFormIndex--;
        document.getElementById(src).style.opacity = '1';
    } else {
        var newLine = "<input type = 'hidden' name ='" + deleteFormIndex + "' value = " + src + " id ='remove" + src + "'>";
        deleteFormIndex++;
        formContents += newLine;
        document.getElementById('delete-selected-form').innerHTML = formContents;
        document.getElementById(src).style.opacity = '0.4';
    } // if else

    if (deleteFormIndex == 0) {
        document.getElementById("delete-selected-button").style.opacity = "0.3";
        document.getElementById("delete-selected-button").disabled = true;
    } else {
        document.getElementById("delete-selected-button").style.opacity = "1";
        document.getElementById("delete-selected-button").disabled = false;
    } // if else
} // addToDelete
