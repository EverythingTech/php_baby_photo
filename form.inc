<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post" enctype="multipart/form-data">
      
  <h1>Image Upload</h1>
  <fieldset>
  <div id = "hiddenupload">
    <input id = "inputButton" type="file" name="fileToUpload">
  </div>
  <button class = "greenAcross" type = "button" onclick = "chooseFile();">Choose File</button>
  <span class = "error"><?php echo $fileUploadErr;?></span>
  </fieldset>
  <fieldset>
    <legend><span class="number">i</span>Image info</legend>
    <label>First Name:</label>
    <input type="text" id="first_name" name="first_name" value = "<?php if(isset($first_name)) echo $first_name;?>">
    <span class = "error"><?php echo $firstNameErr;?></span>
    
    <label>Last Name:</label>
    <input type="text" id="last_name" name="last_name" value = "<?php if(isset($last_name)) echo $last_name;?>">
    <span class = "error"><?php echo $lastNameErr;?></span>
    
    <label>Option of Access:</label>
    <input type="radio" value="public" name="access" <?php if (isset($access) && $access=="public") echo "checked";?>>

    <label class="light" >Public</label><br>
    <input type="radio" value="private" name="access" <?php if (isset($access) && $access=="private") echo "checked";?>>
    <label class="light">Private</label>
    <br>
    <span class = "error"><?php echo $accessErr;?></span>
  </fieldset>
  
  <fieldset>
    <label>Description of the photo</label>
    <textarea id = "description" name="description"><?php if(isset($description))echo $description;?></textarea>
  
  
    <label>Tags</label>
    <textarea id="tags" name="tags"><?php if(isset($tags))echo $tags;?></textarea>
  </fieldset>
  <fieldset>
    <input type="checkbox" id="agreement" value="agree" name="user_agreement"><label class = "light"> I retain the copyright to this image and release it for use on this site.</label><br>
    <span class = "error"><?php echo $user_agreementError;?></span>                
  </fieldset>
  <fieldset id = "resetField">
  <button id = "resetButton" class = "resetPost" type="reset">Reset</button>
  <button class = "resetPost" type="submit">Submit</button>
  </fieldset>
  <fieldset>
    <span class = "success"><?php echo $successMsg;?></span>
  </fieldset>

</form>
      