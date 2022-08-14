<?php

require_once "db_conn.php";

//$response = get_web_page("http://".$HOST_ADDR."/api/getBoardMode.php?board_id=1");

//$resArr = array();
//$resArr = json_decode($response);
//echo "<pre>"; print_r($response); echo "</pre>";

function get_web_page($url)
{

    $options = array(
        CURLOPT_RETURNTRANSFER => true,   // return web page
        CURLOPT_HEADER => false,  // don't return headers
        CURLOPT_FOLLOWLOCATION => true,   // follow redirects
        CURLOPT_MAXREDIRS => 10,     // stop after 10 redirects
        CURLOPT_ENCODING => "",     // handle compressed
        CURLOPT_USERAGENT => "test", // name of client
        CURLOPT_AUTOREFERER => true,   // set referrer on redirect
        CURLOPT_CONNECTTIMEOUT => 120,    // time-out on connect
        CURLOPT_TIMEOUT => 120,    // time-out on response
    );

    $ch = curl_init($url);
    curl_setopt_array($ch, $options);

    $content = curl_exec($ch);

    curl_close($ch);

    return $content;
}

function userNamePassVerify($usrname = NULL, $passwd = NULL, $tbl = NULL, $dbconn = NULL)
{
    $sql = "SELECT username, password  FROM $tbl WHERE username = ?";
    $valid = false;

    if (isset($usrname) and isset($passwd)) {
        if ($stmt = $dbconn->prepare($sql)) {
            /* Bind variables to the prepared statement as parameters */
            $stmt->bind_param("s", $usrname);
            if ($stmt->execute()) {

                // Store result
                $stmt->store_result();
                if ($stmt->num_rows == 1) {
                    /* Bind result variables */
                    // $stmt->bind_result($usrname, $passwd);
                    $valid = true;
                }
            }
            $stmt->close();
        }
    }
    return $valid;
}

function validationBoardID($boardID = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT id_board  FROM $tbl WHERE id_board = ?";
    $valid_ = false;

    if (isset($boardID)) {
        if ($stmt = $dbConn->prepare($sql)) {
            /* Bind variables to the prepared statement as parameters */
            $stmt->bind_param("i", $boardID);
            if ($stmt->execute()) {
                // Store result
                $stmt->store_result();
                if ($stmt->num_rows == 1) {
                    /* Bind result variables */
                    // $stmt->bind_result($usrname, $passwd);
                    $valid_ = true;
                }
            }
            $stmt->close();
        }
    }
    return $valid_;
}

function RFIDFingerValidation($_IDFinger = NULL, $_IDRfid = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT id_fingger, id_rfid  FROM $tbl WHERE (id_fingger = ? AND id_rfid = ?)";
    $valid = false;

    if (isset($_IDFinger) and isset($_IDRfid)) {

        if ($stmt = $dbConn->prepare($sql)) {

            $stmt->bind_param("ii", $_IDFinger, $_IDRfid);
            if ($stmt->execute()) {

                // Store result
                $stmt->store_result();
                if ($stmt->num_rows == 1) {

                    /* Bind result variables */
                    $stmt->bind_result($_IDFinger, $_IDRfid);
                    $valid = true;
                }
            }
            $stmt->close();
        }
    }
    return $valid;
}

function getSaldoUser($_IDFinger = NULL, $_IDRfid = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT saldo  FROM $tbl WHERE (id_fingger = $_IDFinger AND id_rfid = $_IDRfid)";
    $saldo = 0;
    $saldoItem = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        if ($stmt->execute()) {

            $stmt->bind_result($saldo);
            while ($stmt->fetch()) {

                $saldoItem = $saldo;
            }
        }
    }

    return $saldoItem;
}