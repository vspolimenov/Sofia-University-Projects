<?php
    include "database_connection.php";

    if ($_SERVER["REQUEST_METHOD"] == "POST")
        {
            $username = modify_input ($_POST["username"]);
            $password = modify_input ($_POST["password"]);
            $email = modify_input ($_POST["email"]);

            $errors = array ();

            if (empty ($username) ||
                $username != $_POST["username"] ||
                strlen ($username) < 5 ||
                strlen($username) > 30){
              array_push ($errors, "username empty, contains forbiden chars,too short or too long");
            }  
            if (empty ($password) ||
                $password != $_POST["password"] ||
                strlen ($password) < 5 ||
                strlen($password) > 30){
              array_push ($errors, "password empty,  contains forbiden chars, too short or too long");
            }
            if (empty ($email) ||
                $email != $_POST["email"] ||
                strlen($email) > 30 ||
                !filter_var($email, FILTER_VALIDATE_EMAIL)){
              array_push ($errors, "email empty, contains forbiden chars, too long or not valid");
            }

            if (count ($errors) > 0){
                echo '<ul style="color:red;">';
                foreach ($errors as $error){
                    echo "<li>$error</li>";
                }
                echo '</ul>';
            }
            else{
                if (register ($username, $password, $email)) {
                    session_start();
                    $_SESSION['username'] = $username;
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

    function register ($username, $password, $email) {
        $conn = connect_to_DB_server ();
        if (conn == null)
            return false;
        $stmt = $conn->prepare ('
            INSERT INTO Users (username, password, email)
            VALUES (:username, :password, :email)');
        
        $stmt->bindParam(':username', $username);
        $stmt->bindParam(':password', sha1 ($password));
        $stmt->bindParam(':email', $email);


        try {    
            $stmt->execute();
            return true;
        }catch (PDOException $e) {
            echo ($e->getMessage());
            return false;
        }
    }
?>

