var i = 0;
function get() {
    var t = document.getElementById("time");
    return t.textContent;
}
function add() {
    if (i >= get()) {
        return;
    }
    var node = document.getElementById('a');
    var tr = document.createElement("tr");
    var td1 = document.createElement("td");
    var td2 = document.createElement("td");
    var td3 = document.createElement("td");
    var td4 = document.createElement("td");
    var td5 = document.createElement("td");
    {
        t = document.createTextNode(Math.random());
        td5.appendChild(t);
    }
    {
        t = document.createTextNode(Math.random());
        td4.appendChild(t);
    }
    {
        d = new Date;
        t = document.createTextNode(d);
        td3.appendChild(t);
    }
    {
        d = new Date;
        t = document.createTextNode(d);
        td2.appendChild(t);
    }
    {
        t = document.createTextNode(i);
        td1.appendChild(t);
    }
    tr.appendChild(td1);
    tr.appendChild(td2);
    tr.appendChild(td3);
    tr.appendChild(td4);
    tr.appendChild(td5);
    node.appendChild(tr);
    i++;
}
function run() {
    setInterval(add, 1);
    console.log("Run");
}
run();