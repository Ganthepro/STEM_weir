const dateEle = document.getElementById("date");
const timeEle = document.getElementById("time");
const modeEle = document.getElementById("mode");
const distanceEle = document.getElementById("distance");
const flowEle = document.getElementById("flow");
const volumeEle = document.getElementById("volume");
const heightEle = document.getElementById("height");
const wifiEle = document.getElementById("status");
let wifiStatus;
const host_ip = window.location.hostname;
let numCheck;
let counter = 0;

function fetching(mode) {
  let url = "http://" + host_ip + "/write.php" + "?wmode=" + mode;
  fetch(url, {
    method: "POST",
    body: JSON.stringify({
      name: "",
      nickName: "",
    }),
    headers: { "Content-Type": "application/json" },
    mode: "no-cors",
  });
}

function movement(but, i, line) {
  const ele = document.getElementById(but.id);
  ele.style.border = "3px " + line + " skyblue";
  ele.childNodes[0].style.height = i;
}

function showWifi() {
  setTimeout(function () {
    wifiEle.style.opacity = "0";
  }, 2000);
  if (wifiEle.innerText != host_ip) {
    wifiEle.innerText = host_ip;
  } else {
    wifiEle.innerText = wifiStatus;
  }
  wifiEle.style.opacity = "1";
}

setInterval(showWifi, 2500);

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
        if (text.split(" ")[1].split(",")[6] == numCheck) {
          counter++;
          if (counter < 10) {
            wifiStatus = "Bad Connection";
            document.getElementById("op-1").style.borderColor = "yellow";
            document.getElementById("status").style.color = "yellow";
          } else if (counter == 10) {
            wifiStatus = "Connection Lost";
            document.getElementById("op-1").style.borderColor = "red";
            document.getElementById("status").style.color = "red";
            dateEle.innerText = "No Data";
            timeEle.innerText = "No Data";
            modeEle.innerText = "No Data";
            distanceEle.innerText = "No Data";
            flowEle.innerText = "No Data";
            volumeEle.innerText = "No Data";
            heightEle.innerText = "No Data";
          }
        } else {
          numCheck = text.split(" ")[1].split(",")[6];
          counter = 0;
          if (wifiEle.innerText != host_ip) {
            wifiEle.innerText = wifiStatus;
          }
          wifiStatus = "Connected";
          document.getElementById("op-1").style.borderColor = "green";
          document.getElementById("status").style.color = "green";
          dateEle.innerText = text.split(" ")[0];
          timeEle.innerText = text.split(" ")[1].split(",")[0];
          if (text.split(" ")[1].split(",")[1] === "1") {
            modeEle.innerText = "Setting Height";
          } else if (text.split(" ")[1].split(",")[1] === "2") {
            modeEle.innerText = "Option";
          } else if (text.split(" ")[1].split(",")[1] === "3") {
            modeEle.innerText = "View Host";
          } else if (text.split(" ")[1].split(",")[1] === "0") {
            modeEle.innerText = "Monitering";
          }
          distanceEle.innerText = text.split(" ")[1].split(",")[2];
          flowEle.innerText = text.split(" ")[1].split(",")[3];
          volumeEle.innerText = text.split(" ")[1].split(",")[4];
          heightEle.innerText = text.split(" ")[1].split(",")[5];
        }
        if (wifiEle.innerText != host_ip) {
          wifiEle.innerText = wifiStatus;
        }
      }
    });
}

setInterval(readtxt, 500);