function movement(but,i,line) {
    const ele = document.getElementById(but.id)
    ele.style.border = '3px ' + line + ' skyblue'
    ele.childNodes[0].style.height = i
}