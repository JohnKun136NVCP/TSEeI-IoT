setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("SENSOR_ID").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensor", true);
    xhttp.send();
  },
  100);