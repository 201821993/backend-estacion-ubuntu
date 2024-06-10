// configuración de mysql y la base de datos 
/*  import mysql from "promise-mysql";  
la línea de arriba importa promise-mysql, el cual es utilizado en ubuntu, aparentemente no funciona para el servidor

import mysql from "mysql2/promise";
la línea de arriba funciona con windows
*/ 
//se espera que esta línea funcione con el servidor
import mysql from "mysql2";

import config from "../config.js";

const connection = mysql.createConnection({
    host:config.host,
    user:'estacion',
    password:config.password,
    database: config.database,
    port :'3306'
},{multipleStatement:true});


const getConnection = () =>{
    return connection;
}
module.exports = {
    getConnection
}