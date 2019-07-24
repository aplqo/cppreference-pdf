function getT() {
    var n = document.getElementById("t");
    var s = document.createElement("p");
    s.setAttribute("id", "time");
    t = document.createTextNode(time);
    s.appendChild(t);
    n.appendChild(s);
}