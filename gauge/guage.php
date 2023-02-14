<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        #circle {
            position: absolute;
            width: 180px;
            height: 180px;
            top: 70px;
            left: 70px;
            border-radius: 50%;
            border: 2px solid red;
            overflow: hidden;
        }

        #h-cir {
            position: relative;
            width: 180px;
            height: 180px;
            border-radius: 50%;
            /* animation: rotation 2s infinite linear; */
        }

        #black {
            position: absolute;
            width: 100%;
            height: 50%;
            top: 0;
            background-color: black;
        }

        #purple {
            position: absolute;
            width: 100%;
            height: 50%;
            bottom: 0;
            background-color: purple;
        }

        #white-1 {
            position: absolute;
            width: 100%;
            height: 50%;
            bottom: 0;
            z-index: 1;
            background-color: white;
        }

        #white-2 {
            position: absolute;
            width: 70%;
            height: 70%;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            background-color: white;
            border-radius: 50%;
        }
        #p-1 {
            position: absolute;
            left: 5px;
            z-index: 1;
            top: 10px;
        }
        #p-2 {
            position: absolute;
            right: 5px;
            z-index: 1;
            top: 10px;
        }
    </style>
</head>

<body>
    <div id="circle">
        <div id="h-cir">
            <div id="black"></div>
            <div id="purple"></div>
        </div>
        <div id="white-1"></div>
            <p id="p-1">0</p>
            <p id="p-2">300</p>
        <div id="white-2"></div>
    </div>
    <script>
        const ele = document.getElementById("h-cir");
        let height;
        let degree;
        let turn;
        function readtxt() {
            fetch("data.txt")
                .then((response) => response.text())
                .then((text) => {
                    if (
                        text.split(" ")[0] == "" ||
                        text.split(" ")[1].split(",")[0] == "" ||
                        text.split(" ")[1].split(",")[1] == "" ||
                        text.split(" ")[1].split(",")[2] == "" ||
                        text.split(" ")[1].split(",")[3] == "" ||
                        text.split(" ")[1].split(",")[4] == "" ||
                        text.split(" ")[1].split(",")[5] == "" ||
                        text.split(" ")[1].split(",")[6] == ""
                    ) {
                    } else {
                        height = text.split(" ")[1].split(",")[5];
                        degree = (parseInt(height) * 180) / 300;
                        console.log(degree)
                        ele.style.transform = "rotate(" + String(degree) + "deg)";
                    }
                })
            }
            setInterval(readtxt, 500);
    </script>
</body>

</html>