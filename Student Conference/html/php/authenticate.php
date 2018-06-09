<?php
    if ($_SERVER["REQUEST_METHOD"] == "GET"){
        session_start ();
        if (isset($_SESSION["username"]) == true){
            http_response_code(200);
            return;
        }
            
    }
    
    http_response_code(401);
?>