<?php
use Bluerhinos\phpMQTT;
require("vendor/bluerhinos/phpmqtt/phpMQTT.php");

$host = "test.mosquitto.org";
$port = 1883;
$topic = "iot/kendali/G.231.22.0046";

// Get message from GET parameter or use default
$message = @$_GET['message'];
if (!empty($message)) {
    // Create new MQTT client instance with random client ID
    $mqtt = new phpMQTT($host, $port, "ClientID".rand());

    // Try to connect and publish
    if($mqtt->connect(true, NULL, @$username, @$password)) {
        $mqtt->publish($topic, $message, 0);
        $mqtt->close();
        echo "[$topic] mengirim Pesan: $message<br>";
    } else {
        echo "Fail or Timeout<br>";
    }
}
?>

<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Kontrol Lampu</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #f4f4f4;
            margin: 0;
            padding: 20px;
        }
        h2 {
            color: #333;
            margin-top: 20px;
        }
        .container {
            display: inline-block;
            text-align: left;
            background-color: #fff;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);
            max-width: 800px;
            width: 100%;
        }
        .lamp-control {
            margin-bottom: 20px;
            padding: 15px;
            border: 1px solid #ddd;
            border-radius: 8px;
            background-color: #fafafa;
        }
        .lamp-control h3 {
            margin-top: 0;
            margin-bottom: 10px;
            color: #444;
        }
        .lamp-control button {
            padding: 10px 20px;
            margin: 5px;
            font-size: 16px;
            cursor: pointer;
            border: none;
            border-radius: 5px;
            transition: all 0.3s ease;
        }
        .lamp-control button:hover {
            opacity: 0.8;
        }
        .on {
            background-color: #4CAF50;
            color: white;
        }
        .off {
            background-color: #f44336;
            color: white;
        }
    </style>
</head>
<body>
    <h2>Kendali Lampu via MQTT</h2>
    <div class="container">
        <div class="lamp-control">
            <h3>Lampu 1 (Pin D1)</h3>
            <button class="on" onclick="sendCommand('D1=1')">ON</button>
            <button class="off" onclick="sendCommand('D1=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 2 (Pin D2)</h3>
            <button class="on" onclick="sendCommand('D2=1')">ON</button>
            <button class="off" onclick="sendCommand('D2=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 3 (Pin D3)</h3>
            <button class="on" onclick="sendCommand('D3=1')">ON</button>
            <button class="off" onclick="sendCommand('D3=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 4 (Pin D4)</h3>
            <button class="on" onclick="sendCommand('D4=1')">ON</button>
            <button class="off" onclick="sendCommand('D4=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 5 (Pin D5)</h3>
            <button class="on" onclick="sendCommand('D5=1')">ON</button>
            <button class="off" onclick="sendCommand('D5=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 6 (Pin D6)</h3>
            <button class="on" onclick="sendCommand('D6=1')">ON</button>
            <button class="off" onclick="sendCommand('D6=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 7 (Pin D7)</h3>
            <button class="on" onclick="sendCommand('D7=1')">ON</button>
            <button class="off" onclick="sendCommand('D7=0')">OFF</button>
        </div>
        <div class="lamp-control">
            <h3>Lampu 8 (Pin D8)</h3>
            <button class="on" onclick="sendCommand('D8=1')">ON</button>
            <button class="off" onclick="sendCommand('D8=0')">OFF</button>
        </div>
    </div>

    <script>
        function sendCommand(command) {
            // Buat request ke kirim.php dengan parameter message
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "kirim.php?message=" + command, true);
            xhr.send();
        }
    </script>
</body>
</html>
