import { Component,OnInit } from '@angular/core';
//
import { SocketServerService } from 'src/app/services/socket-server.service';
import { DataFetchManagerService } from 'src/app/services/data-fetch-manager.service';
import Chart from 'chart.js/auto'
@Component({
  selector: 'app-view-data',
  templateUrl: './view-data.component.html',
  styleUrls: ['./view-data.component.css']
})
export class ViewDataComponent implements OnInit{
  anguloRotacion: any = 0.99;
  currentStyles:any;
setCurrentStyles(){
  this.currentStyles={

    'transform': false ?'rotate(0.16turn)':  'rotate(0.69turn)'


  };
}



  markerConfig = {
    "0": { color: '#FFFFFF', size: 8, label: '0', type: 'line'},
    "15": { color: '#FFFFFF', size: 4, type: 'line'},
    "30": { color: '#FFFFFF', size: 8, label: '30', type: 'line'},
    "40": { color: '#FFFFFF', size: 4, type: 'line'},
    "50": { color: '#FFFFFF', size: 4, label: '50', },
    "60": { color: '#FFFFFF', size: 4, type: 'line'},
    "70": { color: '#FFFFFF', size: 8, label: '70', type: 'line'},
    "85": { color: '#FFFFFF', size: 4, type: 'line'},
    "100": { color: '#FFFFFF', size: 8, label: '100', type: 'line'},
}
  respuesta :any;
  temperatureValue :any ;
  altitudeValue :any;
  airQualityValue:any ;
  pressureValue:any;
  ryValue:any;
  weatherInfo:any;
  o3value:any;
  co2value :any;
  pm1 :any;
  pm2_5:any;
  pm10:any;
  windSpeed:any;
  gaugeType :any = "semi";
  gaugeValue = 28.3;
   // aquí se guarda la consulta realizada por la vista sp_view_weatherdata
   weather_dataDB :any;

  gaugeLabel = "Speed";
  gaugeAppendText = "km/hr";


  gauegeThik:any=14;
  size:any = 400;
  data :any = 15;
  arrayPrueba:any = [12, 19, 3, 5, 2, 3];

  dataChartTemperatura = {
    labels: ['1:30', '2:00', '3:00', '4:00', '5:00', '6:00'],
    datasets: [{
      label: 'Temperature',
      data: [10, 19, 23, 24.5, 22, 17, 11],
      fill:"start",
      borderColor: 'rgb(75, 192, 192)',
    }]
  };



constructor( private socket : SocketServerService , private data_fetch_service :  DataFetchManagerService ){

  this.setCurrentStyles();

  this.socket.sendMessage("hola servidor , te mando de regreso un beso");
  this.socket.getMessage().subscribe((msg: any) => {
    console.log("este es el mensaje que manda el servidor",msg);
     // AQUÍ se reciben los datos mandados por el servidor
   });
   this.socket.getMessage().subscribe((message: any) => {
   console.log(message);
  });
//aquí invocamos el servicio y utilizamos sus metodos para recibir los datos desde el back end
  this.socket.getRealData().subscribe((message: any) => {
    console.log(message);
    console.log(message.temperature);
    console.log(message.pressure);
    console.log(message.altitud);
    console.log(message.air_quality);
    console.log(message.UVray);

    this.temperatureValue = message.temperatura;
    this.pressureValue = message.pressure;
    this.altitudeValue = message.altitud;
    this.ryValue = message.UVRay;
    this.pm1 = message.pm10_env ;
  this.pm2_5 = message.pm25;
  this.pm10= message.pm100_env  ;
  this.ryValue =  message.uv;
    this.windSpeed = message.windSpeed;
this.o3value = message.ozono;


   });
}
ngOnInit(): void {


  this.data_fetch_service.obtenerRainDatos().subscribe(respuesta=>{




  });

  this.data_fetch_service.obtenerweatherMeasuremnts().subscribe(respuesta=>{
    console.log(respuesta);
    this.weather_dataDB = respuesta;
  });




  const ctx = document.getElementById('myChart');
  const myChart = new Chart("ctx", {

    type: 'line',
    data: this.dataChartTemperatura,
    options: {
      animations: {
        tension: {
          duration: 2000,
          easing: 'linear',
          from: 1,
          to: 0,
          loop: true
        }
      },
      scales: {
        x: {
          grid: {
            display: false // Oculta la cuadrícula del eje x
          }
        },
        y: { // defining min and max so hiding the dataset does not change scale range
          min: 0,
          max: 50,
          grid: {
            display: false // Oculta la cuadrícula del eje y
          }
        }
      },
      backgroundColor:"#fe6385",

      responsive:true,
      maintainAspectRatio :false,
    },




  });



  const particulas2 = new Chart('particula', {
    type: 'bar',
    data: {
      labels: ['1:00', '2:00', '4:00', '1:00', '2:00', '4:00','4:00'],
      datasets: [
        {
          label: 'pm 1.0',
          data: [30,23,100,12,54,65,45],

          backgroundColor: '#3333ff',
          borderWidth:1
        },
         {
          label: 'pm 2.5',
          data: [30,23,43,43,54,32,45],

          backgroundColor: '#ce929d',
          borderWidth:1
        },
        {
          label: 'pm 100',
          data: [30,23,43,43,54,65,50],

             backgroundColor: '#4c195a',

        }

      ],


    },

    options: {
      responsive:true,
      maintainAspectRatio :false,

      scales: {
        y: {
          beginAtZero: true
        }
      }

    }

  });


}
}
