const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.cardPump{
    max-width: 400px;
     min-height: 10px;
     color: #000000;
     text-align: center;
}

.cardTempandHum{
     max-width: 400px;
     min-height: 50px;
     display: flex;
     justify-content: space-between;

}

.cardTemp{
    max-width: 400px;
     width: 45%;
     min-height: 50px;
     color: #0000FF;
     text-align: center;
     align-content: left;

}

#valuePump{
	color: #FF0000;
}

#valueTemp{
	color: #FFA500;
}

#valueHum{
	color: #FFA500;
}

.cardHum{
	 width: 45%;
     max-width: 400px;
     min-height: 50px;
     color: #0000FF;
     text-align: center;
     align-content: right;

}

.cardSoil{
    max-width: 400px;
     min-height: 50px;
     color: #00FF00;
     text-align: center;
}


</style>
<body>
<div class="cardPump">
  <h2>Water Pump</h2>
  <h3><span id="valuePump">OFF</span></h3>
</div>

<div class="cardTempandHum">
	<div class="cardTemp">
	  <h2>Temperature°C</h2>
  <h3><span id="valueTemp">36.3</span></h3>
	</div>

	<div class="cardHum">
	  <h2>Humidity °</h2>
  <h3><span id="valueHum">25.4</span></h3>
	</div>
</div>

<div class="cardSoil">
  <h2 style="background: gray;">Soil Moisture Sensor</h2>
  <h3><span id="valueSoil">DRY</span></h3>
</div>

<script>


setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getTemp();
  getHum();
  getSoil();
  getPump();
}, 1000); //2000mSeconds update rate // HERE DELAY

function getTemp() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("valueTemp").innerHTML =
      this.responseText;
      window.AppInventor.setWebViewString("" + this.responseText);  // RESPUESTA A CadenaDeWebView
    }
  };
  xhttp.open("GET", "readTemp", true);
  xhttp.send();
}

function getHum() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("valueHum").innerHTML =
      this.responseText;
      window.AppInventor.setWebViewString("" + this.responseText);  // RESPUESTA A CadenaDeWebView
    }
  };
  xhttp.open("GET", "readHum", true);
  xhttp.send();
}

function getSoil() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("valueSoil").innerHTML =
      this.responseText;
      window.AppInventor.setWebViewString("" + this.responseText);  // RESPUESTA A CadenaDeWebView
    }
  };
  xhttp.open("GET", "readSoil", true);
  xhttp.send();
}

function getPump() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("valuePump").innerHTML =
      this.responseText;
      window.AppInventor.setWebViewString("" + this.responseText);  // RESPUESTA A CadenaDeWebView
    }
  };
  xhttp.open("GET", "readPump", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
