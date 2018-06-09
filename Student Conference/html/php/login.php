<?php
    include "database_connection.php";


    if ($_SERVER["REQUEST_METHOD"] == "POST")
        {
            $username = modify_input ($_POST["username"]);
            $password = modify_input ($_POST["password"]);

            $errors = array ();

            if (empty ($username) ||
                $username != $_POST["username"]){
              array_push ($errors, "username empty, contains forbiden chars,too short or too long");
            } 

            if (empty ($password) ||
                $password != $_POST["password"]){
              array_push ($errors, "password empty,  contains forbiden chars, too short or too long");
            }
            
            if (count ($errors) > 0){
                echo '<ul style="color:red;">';
                foreach ($errors as $error){
                    echo "<li>$error</li>";
                }
                echo '</ul>';
                http_response_code(401);
                return 0;
            }
            else{
                if (authenticate ($username, $password) == true) {
                    session_start();
                    $_SESSION["username"] = $username;

                    http_response_code(200);
                    return;
                }
                else {
                    http_response_code(401);
                    return;
                }
            }
        }
        else {
            http_response_code(401);
            return;
        }

    function modify_input ($data){
        $data = trim ($data);
        $data = stripslashes ($data);
        $data = htmlspecialchars ($data);
        return $data;
    }

    function authenticate ($username, $password) {
        $conn = connect_to_DB_server ();
        if (conn == null)
            return false;
        $stmt = $conn->prepare ('
            SELECT *
            FROM Users
            WHERE username=:username AND password=:password');
        
        $stmt->bindParam(':username', $username);
        $stmt->bindParam(':password', sha1 ($password));
        try {    
            $stmt->execute();
        }catch (PDOException $e) {
            echo ($e->getMessage());
            return false;
        }

        if ($stmt->rowCount () == 1)
            return true;

        return false;
    }

?>