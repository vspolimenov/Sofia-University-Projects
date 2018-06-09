<?php
    include "database_connection.php";

    session_start ();
    if (isset($_SESSION["username"]) == false){
        http_response_code(401);
        return;
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST")
        {
            $conferenceName = modify_input ($_POST["conferenceName"]);
            $description = modify_input ($_POST["description"]);
            $place = modify_input ($_POST["place"]);
            $time = modify_input ($_POST["time"]);
			$date = date('Y-m-d', strtotime($_POST['date']));
			$file = $_FILES["file"];
		
            $errors = array ();

            if (empty ($conferenceName) ||
                $conferenceName != $_POST["conferenceName"] ||
                strlen($conferenceName) > 30){
              array_push ($errors, $_POST["file"]);
            }  
			
            if ($description != $_POST["description"] ||
                strlen($description) > 300){
              array_push ($errors, "password empty,  contains forbiden chars, too short or too long");
            }
            if (empty ($place) ||
                $place != $_POST["place"] ||
                strlen($place) > 30){
              array_push ($errors, "place empty, contains forbiden chars, too long or not valid");
            }
            if (empty ($time) ||
                $time != $_POST["time"] || $time <= 0){
              array_push ($errors, "time empty, contains forbiden chars, too long or not valid");
            }
			  if (empty ($file) ){
              array_push ($errors, "File empty!");
            }
			

            if (count ($errors) > 0){
                echo '<ul style="color:red;">';
                foreach ($errors as $error){
                    echo "<li>$error</li>";
                }
                echo '</ul>';
            }
            else{
				print_r($errors);
                if (create_conference ($conferenceName, $description, $place, $time, $date, $file)) {
                    http_response_code(200);
                    return;
                }   
            }
		
        }
    http_response_code(401);
    return;

    function modify_input ($data){
        $data = trim ($data);
        $data = stripslashes ($data);
        $data = htmlspecialchars ($data);
        return $data;
    }

    function create_conference ($conferenceName, $description, $place, $time, $date,$file) {
		upload($conferenceName,$file);
			print_r($file);
        $conn = connect_to_DB_server ();
        if ($conn == null)
            return false;
        $stmt = $conn->prepare ('
            INSERT INTO Conferences (name, description, place, time,date )
            VALUES (:name, :description, :place, :time, :date)');
        
        $stmt->bindParam(':name', $conferenceName);
        $stmt->bindParam(':description', $description);
        $stmt->bindParam(':place', $place);
        $stmt->bindParam(':time', $time);
		$stmt->bindParam(':date', $date);
        try {    
            $stmt->execute();
            return true;
        }catch (PDOException $e) {
            echo ($e->getMessage());
            return false;
        }
    }
	
	function upload($conferenceName, $file) {
		$target_dir = "uploads/";
		$target_file = $target_dir . basename($file["name"]);
		$uploadOk = 1;
		$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
		// Check if image file is a actual image or fake image
		if(isset($_POST["submit"])) {
			$check = getimagesize($file["tmp_name"]);
			if($check !== false) {
				echo "File is an image - " . $check["mime"] . ".";
				$uploadOk = 1;
			} else {
				echo "File is not an image.";
				$uploadOk = 0;
			}
		}
		// Check if file already exists
		if (file_exists($target_file)) {
			echo "Sorry, file already exists.";
			$uploadOk = 0;
		}
		// Check file size
		if ($file["size"] > 1500000) {
			echo "Sorry, your file is too large.";
			$uploadOk = 0;
		}
		// Allow certain file formats
		if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
		&& $imageFileType != "gif" ) {
			echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
			$uploadOk = 0;
		}
		// Check if $uploadOk is set to 0 by an error
		if ($uploadOk == 0) {
			echo "Sorry, your file was not uploaded.";
		// if everything is ok, try to upload file
		} else {
			if (move_uploaded_file($file["tmp_name"], $target_dir .$conferenceName.'.jpg')) {
				echo "The file ". basename( $file["name"]). " has been uploaded.";
			} else {
				echo "Sorry, there was an error uploading your file.";
			}
		}
	}
?>

