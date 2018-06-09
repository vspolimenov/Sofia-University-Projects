<?php
    include "database_connection.php";

    session_start ();
    if (isset($_SESSION["username"]) == false){
        http_response_code(401);
        return;
    }

    if ($_SERVER["REQUEST_METHOD"] == "GET")
        {
            $conferences = get_conferences ();
            $conferences_json = json_encode ($conferences);
            echo ($conferences_json);
            return;
        }
    http_response_code(401);
    return;

    function get_conferences () {
        $conn = connect_to_DB_server ();
        if ($conn == null)
            return false;

        $stmt = $conn->prepare ('
            SELECT *
            FROM Conferences');
        
        try {    
            $stmt->execute();
        }catch (PDOException $e) {
            echo ($e->getMessage());
        }

        $rv=$stmt->fetchAll(PDO::FETCH_ASSOC);
        return $rv;
    }
?>