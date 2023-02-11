<!DOCTYPE html>
<html>
<head>
    <title>SMART Meters</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        .head{
            margin:10px auto 30px auto; 
            text-align: left; 
            color: #fefefe;
        }

        body {
            text-align: right;
            font-size: 100%;
            background: #000;
        }
        
        #needle {
            width: 41%;
            right: 50%;
            height: 5px;
            background: #ff0200;
            position: absolute;
            top: 60%;
            transform-origin: 100%;
            transform: rotate(-31deg);
        }

        #numbers {
            width: 140px;
            height: 30px;
            text-align: center;
            background: #191919;
            position: absolute;
            bottom: 10px;
            left: 85px;
            color: #fff;
            font-size: 1.8em;
            line-height: 1.34em; 
            font-family: "Courier New", Courier, monospace;
            padding: 0px 10px 5px;
            border: 1px solid #292929;
        }

        #gauge {     
            position: absolute;    
            background: #000 url(speedometer.png) no-repeat;  
            left: 20px;
            margin-left: 5px;
            width: 334px;       
            height: 260px;  
        }

        #circle {
            width: 79px;
            height: 79px;
            background: url(circle-3.png)no-repeat;
            bottom: 59px;
            left: 127px;
            position: absolute;
        }

        #mi-km {
            bottom: -25px;
            left: 97px;
            text-align: center;
            position: absolute;
            width: 140px;
            height: 30px;
            color: #999;
            font-size: 1.4em;
            font-family: "Courier New", Courier, monospace;
        }

    </style>
</head>
<body>
    <h1 class="head">SMART Weir Meters<br>Web Testing - Examples</h1>          
    <div id="gauge">                              
        <div id="needle"></div>               
        <div id="circle"></div>
        <div id="numbers"></div>                             
        <div id="mi-km"></div>             
    </div>       
    <script>
        const numbers=document.getElementById('numbers');
        const mi_km=document.getElementById('mi-km');
        const elem = document.getElementById("needle"); 
        var xpos=0;
        var sign = 1;
          
        mi_km.innerHTML="Liter";
        function interval(){                            
            if(xpos>243) sign=0;
            if(xpos<1) sign=1;
            if(sign) xpos++;
            else xpos--;          
            elem.style.rotate= xpos + "deg";          
            numbers.innerHTML = xpos;
        }
        setInterval(interval,50);	
    </script>
</body>
</html>