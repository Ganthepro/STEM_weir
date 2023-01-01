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
            modeEle.innerText = text.split(" ")[1].split(",")[1]
            distanceEle.innerText = text.split(" ")[1].split(",")[2]
            flowEle.innerText = text.split(" ")[1].split(",")[3]
            volumeEle.innerText = text.split(" ")[1].split(",")[4]
            heightEle.innerText = text.split(" ")[1].split(",")[5]
        });
}

setInterval(readtxt,500)
