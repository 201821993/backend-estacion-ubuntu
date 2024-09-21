import { Component } from '@angular/core';
import { SocketServerService } from 'src/app/services/socket-server.service';
import { DataFetchManagerService } from 'src/app/services/data-fetch-manager.service';
import Chart from 'chart.js/auto'
import { HostListener } from '@angular/core';
@Component({
  selector: 'app-dashboard-view',
  templateUrl: './dashboard-view.component.html',
  styleUrls: ['./dashboard-view.component.css']
})
export class DashboardViewComponent {

    /*
      arreglos que van a almacenar de la consulta a la base de datos diferentes valores coom la temperatura, los contaminantes
      */
  temperatura: any[] = []; // almacena la temperatura
  pm1DB :number[] = []; // almacena el contaminante pm 1
  pm_25 :number [] = []; // almacena el contaminante pm 2.5
  pm_10 :number[] =[]; // almacena el contaminante pm10
  horas:any[] =[]; // almacena las horas



// variables almacenan lo que manda socket.io 
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
  directionSocket:any;
  /* Variables para la lluvia */
  tds_tr:any  = 234 ;
  precipitacion_tr:any =1.5;

  
  gaugeType :any = "semi";
  gaugeValue = 28.3;
   // aquí se guarda la consulta realizada por la vista sp_view_weatherdata
   weather_dataDB :any;
  
  gauegeThik:any=14;
  size:any = 400;
  data :any = 15;
  arrayPrueba:any = [12, 19, 3, 5, 2, 3];

  @HostListener('window:resize',['$event'])
    onResize(){
      const screenWidth = window.innerWidth;
      console.log("Este es el jodido ancho de la pantalla",screenWidth);
      //alert("Este es el jodido ancho de la pantalla"+screenWidth);
    }

  


constructor( private socket : SocketServerService , private data_fetch_service :  DataFetchManagerService ){


  // se le manad un mensaaje al servidor con el metodo this.socket.sendMessage
  //this.socket.sendMessage("hola servidor , te mando de regreso un beso");
  this.socket.getMessage().subscribe((msg: any) => {
    console.log("este es el mensaje que manda el servidor",msg);
     // AQUÍ se reciben los datos mandados por el servidor
   });

   this.socket.getMessage().subscribe((message: any) => {
   console.log(message);
  });
//aquí invocamos el servicio y utilizamos sus metodos para recibir los datos desde el back end en tiempo real
  this.socket.getRealData().subscribe((message: any) => {
   /*  console.log(message);
    console.log(message.temperature);
    console.log(message.pressure);
    console.log(message.altitud);
    console.log(message.air_quality);
    console.log(message.UVray); */
      console.log("esto que es ",message);
    this.temperatureValue = message.temperature;
    this.pressureValue = message.pressure;
    this.altitudeValue = message.altitud;
    this.pm1 = message.pm10_env ;
    this.pm2_5 = message.pm25;
    this.pm10= message.pm100_env  ;
    this.ryValue =  message.uv;
    this.windSpeed = message.windSpeed;
    this.o3value = message.ozono;
    this.co2value = message.co2;
    this.directionSocket = message.direction;
    


   });
}
dataChartTemperatura = {
  labels: [this.horas],
  datasets: [{
    
    data: this.temperatura , // [10, 19, 23, 24.5, 22, 17, 11]
    fill:"start",
    borderColor: 'rgb(75, 192, 192)',
  }]
};

ngOnInit(): void {

  /* aquí estan los datos que han sido acumulados */
  this.socket.accumulatedData().subscribe((message:any) => {
    this.temperatureValue = message.temperature;
    console.log("<- temperatureValue--> ",this.temperatureValue);
    this.pressureValue = message.pressure;
    this.altitudeValue = message.altitud;
    this.ryValue = message.uv;
    this.pm1 = message.pm10_env ;
    this.pm2_5 = message.pm25;
    this.pm10= message.pm100_env;
    this.windSpeed = message.windSpeed;
    this.o3value = message.ozone;
    this.co2value = message.co2;
    this.directionSocket = message.direction;
    
  });


  this.data_fetch_service.obtenerweatherMeasuremnts().subscribe(respuesta=>{
    this.weather_dataDB = respuesta;
    console.log("la base de datos, respuetsa ",this.weather_dataDB);
    // Recorre los elementos y añade cada propiedad con su respectivo arreglo
    for (let i = 0; i < this.weather_dataDB.length ; i++) {

        const elemento = this.weather_dataDB[i];
        console.log("este es el chingado elemento ",elemento.pm2_5);
        this.temperatura.push(elemento.temperature);
        this.pm1DB.push(elemento.pm1_0);
        this.pm_25.push(elemento.pm2_5);
        this.pm_10.push(elemento.pm10);
        this.horas.push(elemento.hora.substring(0,2)); // se utiliza substring para extrar solo la hora de la fecha , 

    }
    console.log("estos son los datos de la temperatura",this.temperatura);
    console.log("pm1 ", this.pm1DB );
    console.log(" pm 2_5 ",this.pm_25);
    console.log(" pm 10 ",this.pm_10);
    console.log(" pm 10 ",this.horas);


    const particulas2 = new Chart('particula', {
      type: 'bar',
      data: {
        labels:this.horas, // ['01:00', '02:00', '04:00', '01:00', '02:00', '04:00','04:00']
        datasets: [
          {
            label: 'pm 1.0',
            data: this.pm1DB,

            backgroundColor: '#3333ff',
            borderWidth:1
          },
           {
            label: 'pm 2.5',
            data: this.pm_25,

            backgroundColor: '#ce929d',
            borderWidth:1
          },
          {
            label: 'pm 100',
            data: this.pm_10,

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


  const ctx = document.getElementById('myChart');
  const myChart = new Chart("ctx", {

    type: 'line',
    data: {
      labels:  this.horas, // '1:00','2:00','3:00','4:00','5:00','7:00'
      datasets: [{
        label: 'Temperature',
        data: this.temperatura , // [10, 19, 23, 24.5, 22, 17, 11]
        fill:"start",
        borderColor: '#fe6385',
      }]
    },
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
            display: true // Oculta la cuadrícula del eje y
          }
        }
      },
      plugins:{
        legend:{
          display:false,
        }
      },
      backgroundColor:"#fe6385",

      responsive:true,
      maintainAspectRatio :false,
    },




  });



   });




  this.data_fetch_service.obtenerRainDatos().subscribe(respuesta=>{




  });

  this.data_fetch_service.obtenerweatherMeasuremnts().subscribe(respuesta=>{
    console.log(respuesta);
    this.weather_dataDB = respuesta;
  });




}
ngAfterViewInit():void {
  // Código para el método AfterViewInit

}




}
