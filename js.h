#ifndef JS_H
#define JS_H


const char jsScript[] PROGMEM = R"rawliteral(

function update()
{

fetch("/temperature")

.then(r=>r.json())

.then(data=>{


let h="";


for(let i=0;i<data.count;i++)
{

h+=`

<div class="card">

Sonde ${i+1}

<br>

${data.temperatures[i]} °C

</div>

`;

}


document.getElementById("content").innerHTML=h;


});


}


update();

setInterval(update,2000);


)rawliteral";


#endif
