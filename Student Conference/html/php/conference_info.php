<?php
    include "database_connection.php";

    session_start ();
    if (isset($_SESSION["username"]) == false){
        http_response_code(401);
        return;
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST")
        {
            $conference_info = modify_input ($_POST["conference_info"]);
            $id_conference = modify_input ($_POST["id_conference"]);
            $file = $_FILES["file"];

            $id_user = get_user_id ();
            $errors = array ();
            print_r($conference_info);
            if (empty ($conference_info) ||
                $conference_info != $_POST["conference_info"] ||
                strlen($conference_info) >= 30){
              array_push ($errors, "conference_info empty, contains forbiden chars,too short or too long");
            }  

            if (count ($errors) > 0){
                echo '<ul style="color:red;">';
                foreach ($errors as $error){
                    echo "<li>$error</li>";
                }
                echo '</ul>';
            }
            else{
                if (set_conference_info ($id_user, $id_conference, date ("Y-m-d H:i:s"),$conference_info,  $file)) {
                    return;
                }   
            }

        }


    if ($_SERVER["REQUEST_METHOD"] == "GET")
        {
            if(isset($_GET["conference_id"])){
             $conference_id = modify_input ($_GET["conference_id"]);
            $conference_info = get_conference_info ($conference_id);
         
            $conference_info_json = json_encode ($conference_info);
            echo ($conference_info_json);
            return;
            }
        }
    http_response_code(401);
    return;

    function modify_input ($data) {
        $data = htmlspecialchars ($data);
        return $data;
    }

    function get_user_id () {
        $conn = connect_to_DB_server ();
        if ($conn == null)
            return false;
        $stmt = $conn->prepare ('
            SELECT id
            FROM Users
            WHERE username=:username');
        
        $stmt->bindParam(':username', $_SESSION["username"]);
        try {    
            $stmt->execute();
        }catch (PDOException $e) {
            echo ($e->getMessage());
        }

        $rv=$stmt->fetch(PDO::FETCH_ASSOC);
        return $rv['id'];
    }

    function set_conference_info ($id_user, $id_conference, $date,$comment, $file) {
        $conn = connect_to_DB_server ();
        if ($conn == null)
            return false;

        
        $file_id = upload($id_conference,$comment, $file);
        $stmt = $conn->prepare ('
            INSERT INTO ConferenceData (id_user, id_conference, date, comment, file_id)
            VALUES (:id_user, :id_conference, :date, :comment, :file_id)');
        
        $stmt->bindParam(':id_user', $id_user);
        $stmt->bindParam(':id_conference', $id_conference);
        $stmt->bindParam(':date', $date);
        $stmt->bindParam(':comment', $comment);
        $stmt->bindParam(':file_id', $file_id);

        try {    
            $stmt->execute();
            return true;
        }catch (PDOException $e) {
            echo ($e->getMessage());
            return false;
        }
    }
    function get_conference_info ($conference_id) {
        $conn = connect_to_DB_server ();
        if ($conn == null)
            return false;

        $stmt = $conn->prepare ('
            SELECT *
            FROM ConferenceData
            WHERE id_conference=:id_conference
            ORDER BY date DESC');
        
        $stmt->bindParam(':id_conference', $conference_id);

        try {    
            $stmt->execute();
        }catch (PDOException $e) {
            echo ($e->getMessage());
        }

        $rv=$stmt->fetchAll(PDO::FETCH_ASSOC);
        return $rv;
    }
    function upload($id,$comment, $file) {
		$target_dir = "comments/";
		$target_file = $target_dir . basename($file["name"]);
		$uploadOk = 1;
		$fileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
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
		//Allow certain file formats
		if($fileType != "pdf") {
			echo "Sorry, only PDF files are allowed.";
			$uploadOk = 0;
		}
		// Check if $uploadOk is set to 0 by an error
		if ($uploadOk == 0) {
			echo "Sorry, your file was not uploaded.";
		// if everything is ok, try to upload file
		} else {
			if (move_uploaded_file($file["tmp_name"], $target_dir.$id.$comment.'.'.$fileType)) {
                echo "The file ". basename( $file["name"]). " has been uploaded.";
                return 1;
			} else {
                echo "Sorry, there was an error uploading your file.";
                return 0;
			}
		}
	}
?>

