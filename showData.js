function movement(but,i,line) {
    const ele = document.getElementById(but.id)
    ele.style.border = '3px ' + line + ' skyblue'
    ele.childNodes[0].style.height = i
}

function readtxt() {
    let dateEle = document.getElementById("date")
    let timeEle = document.getElementById("time")
    let modeEle = document.getElementById("mode")
    let distanceEle = document.getElementById("distance")
    let flowEle = document.getElementById("flow")
    let volumeEle = document.getElementById("volume")
    let heightEle = document.getElementById("height")
    fetch('data.txt')
        .then(response => response.text())
        .then(text => {
            dateEle.innerText = text.split(" ")[0]
            timeEle.innerText = text.split(" ")[1].split(",")[0]
            if (text.split(" ")[1].split(",")[1] === "1") {
                modeEle.innerText = "Setting Height"
            } else if (text.split(" ")[1].split(",")[1] === "2") {
                modeEle.innerText = "Setting Volume"
            } else if (text.split(" ")[1].split(",")[1] === "3") {
                modeEle.innerText = "View Host"
            } else if (text.split(" ")[1].split(",")[1] === "0") {
                modeEle.innerText = "Monitering"
            }
            distanceEle.innerText = text.split(" ")[1].split(",")[2]
            flowEle.innerText = text.split(" ")[1].split(",")[3]
            volumeEle.innerText = text.split(" ")[1].split(",")[4]
            heightEle.innerText = text.split(" ")[1].split(",")[5]
        });
}

setInterval(readtxt,500)
