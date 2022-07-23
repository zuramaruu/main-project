<!DOCTYPE html>
<html lang="en">
<head>
    <title>FORM</title>
</head>
<style>
    table {
        font-family: arial, sans-serif;
        border-collapse: collapse;
        width: 75%;
    }

    td, th {
        border: 1px solid #dddddd;
        text-align: left;
        padding: 8px;
    }

    tr:nth-child(even) {
        background-color: #dddddd;
    }
</style>
<body>
<div>
    <h2 align="center">STATE LED MONITORING </h2>
</div>
</body>
</html>
<?php
const DB_SERVER = "localhost";
const DB_USER = "root";
const DB_PASSWORD = "";
const DB_DATABASE = "test";

echo "<table border='1'>
<tr>
<th>ID</th>
<th>LED STATE</th>
<th>REG DATE</th>
<th></th>
</tr>";

$api_key_value = "tPmAT5Ab3j7F9";
$_led_state = "";

$mysqli = new mysqli(DB_SERVER, DB_USER, DB_PASSWORD, DB_DATABASE);
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = ($_POST["api_key"]);
    if ($api_key == $api_key_value) {
        $_led_state = $_POST['value_led_s'];
        if (isset($_POST['value_led_s'])) {
            $stmt = $mysqli->prepare("INSERT INTO state (led_state) VALUES (?)");
            $stmt->bind_param('s', $_led_state);
            $stmt->execute();
        }
    }
}

$stmt = $mysqli->prepare("SELECT id, led_state, reg_date FROM state");
$stmt->execute();
$stmt->bind_result($id, $led_state, $reg_date);

while ($stmt->fetch()) {
    echo "<tr>";
    echo "<td>" . $id . "</td>";
    echo "<td>" . $led_state . "</td>";
    echo "<td>" . $reg_date . "</td>";
//    echo "<td>" . "<a href='edit.php?_user_id=" . $id . "'> <b>EDIT</b> </a>" . "</td>";
    echo "<td>" . "<a href='list_user.php?_del_id=" . $id . "'<b>DELETE</b> </a>" . "</td>";
    echo "</tr>";
}
?>
