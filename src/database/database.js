// configuración de mysql y la base de datos 
/*  import mysql from "promise-mysql";  
la línea de arriba importa promise-mysql, el cual es utilizado en ubuntu, aparentemente no funciona para el servidor

import mysql from "mysql2/promise";
la línea de arriba funciona con windows
*/ 
//se espera que esta línea funcione con el servidor
 // estea lińea es la que sugierio chat gpt para el back end con php import mysql from "mysql2";
import mysql from "promise-mysql";  

import config from "../config.js";

const getConnection = () =>{
    return connection;
}
module.exports = {
    getConnection
}

 const connection = mysql.createPool({
    host:config.host,
    user:'root', /* estacion */
    password:config.password,
    database: config.database,
    port :'3306',
    waitForConnections:true,
    connectionLimit:100,
    queueLimit:0,
    keepAliveInitialDelay:100000
},{multipleStatement:true});

 


/* const connection = mysql.createConnection({
    host:config.host,
    user:'root', 
    password:config.password,
    database: config.database,
    port :'3306'
},{multipleStatement:true});

 */