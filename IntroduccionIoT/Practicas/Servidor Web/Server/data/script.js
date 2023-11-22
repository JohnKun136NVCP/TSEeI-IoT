//Potenciometro
setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("poten_id").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/poten", true);
  xhttp.send();
},
100);
//Fotodiodo
setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("foto_id").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/fotodiodo", true);
  xhttp.send();
},
100);