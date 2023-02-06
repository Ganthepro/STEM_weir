function movement(but, i, line) {
  const ele = document.getElementById(but.id);
  ele.style.border = "3px " + line + " skyblue";
  ele.childNodes[0].style.height = i;
}

const dateEle = document.getElementById("date");
const timeEle = document.getElementById("time");
const modeEle = document.getElementById("mode");
const distanceEle = document.getElementById("distance");
const flowEle = document.getElementById("flow");
const volumeEle = document.getElementById("volume");
const heightEle = document.getElementById("height");
const host_ip = "10.10.10.8";

async function makeRequest() {
  // ทำดูสถานะ Wifi
  try {
    const response = await fetch("http://" + host_ip + "/update.php", {
      mode: "no-cors",
    });
    console.log(response.status); // 👉️ 200
  } catch (err) {
    console.log(err);
  }
}

setInterval(makeRequest, 500);

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
        text.split(" ")[1].split(",")[5] == ""
      ) {
      } else {
        dateEle.innerText = text.split(" ")[0];
        timeEle.innerText = text.split(" ")[1].split(",")[0];
        if (text.split(" ")[1].split(",")[1] === "1") {
          modeEle.innerText = "Setting Height";
        } else if (text.split(" ")[1].split(",")[1] === "2") {
          modeEle.innerText = "Setting Volume";
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
    });
}

setInterval(readtxt, 500);
